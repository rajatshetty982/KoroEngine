#include "GlfwLinuxWindow.h"

#include "koropch.h"

#include "KoroEngine/Core/Log.h"
#include "KoroEngine/Core/Platform.h"
#include "KoroEngine/Events/KeyEvent.h"
#include "KoroEngine/Events/MouseEvent.h"
#include "KoroEngine/Events/ApplicationEvent.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Koro
{
static void GLFWErrorCallback(int err, const char* description)
{
	KORO_ENG_ERROR("GLFW error ({0}): {1}", err, description);
}

IWindow* IWindow::Make(const WindowData& data)
{
	return new LinuxWindow(data);
}

LinuxWindow::LinuxWindow(const WindowData& data)
{
	Init(data);
}

void LinuxWindow::Init(const WindowData& data)
{

	m_Data.Title = data.Title;
	m_Data.Width = data.Width;
	m_Data.Height = data.Height;
	KORO_ENG_INFO("creating window {0}, ({1}, {2})", data.Title, data.Width, data.Height);

	if (!s_GLFWInitialised)
	{
		int initialised = glfwInit();
		KORO_ENG_ASSERT(initialised, "Failed to initialise GLFW!");
		glfwSetErrorCallback(GLFWErrorCallback);
		s_GLFWInitialised = true;
	}


	m_Window = glfwCreateWindow((int)data.Width, (int)data.Height, data.Title.c_str(), nullptr, nullptr);

	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, &m_Data);
	SetVSync(true);
	int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	KORO_ENG_ASSERT(success, "Failed to initialize Glad!");

	// set glfw callbacks
	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* win){
		LinuxWindowData& winData = *(LinuxWindowData*) glfwGetWindowUserPointer(win);
		WindowCloseEvent ev;
		winData.EventCallback(ev);
	});

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* win, int width, int height){
		LinuxWindowData& winData = *(LinuxWindowData*) glfwGetWindowUserPointer(win);
		winData.Height = height;
		winData.Width = width;
		WindowResizeEvent event(width, height);
		winData.EventCallback(event);
	});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* win,int key, int scancode, int action, int mods){
		LinuxWindowData& winData = *(LinuxWindowData*) glfwGetWindowUserPointer(win);
		switch(action)
		{
			// *  @param[in] action `GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`.  Future
			case GLFW_PRESS:
				{
					KeyPressEvent ev(key,0);
					winData.EventCallback(ev);
					break;
				}
			case GLFW_RELEASE:
				{
					KeyReleaseEvent ev(key);
					winData.EventCallback(ev);
					break;
				}
			case GLFW_REPEAT:
				{
					KeyPressEvent ev(key,1);
					winData.EventCallback(ev);
					break;
				}
		}
	});

	glfwSetCharCallback(m_Window, [](GLFWwindow* win, unsigned int codepoint){
		LinuxWindowData& winData = *(LinuxWindowData*) glfwGetWindowUserPointer(win);
		KeyTypeEvent ev(codepoint);
		winData.EventCallback(ev);
	});

	glfwSetMouseButtonCallback( m_Window,  [](GLFWwindow* win, int button, int action, int mods){
		LinuxWindowData& winData = *(LinuxWindowData*) glfwGetWindowUserPointer(win);
		switch (action)
		{

			case GLFW_PRESS:
				{
					MouseButtonPressEvent ev(button);

					winData.EventCallback(ev);
					break;
				}
			case GLFW_RELEASE:
				MouseButtonReleaseEvent ev(button);
				winData.EventCallback(ev);
		}
	});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* win, double xoffset, double yoffset){
		LinuxWindowData& winData = *(LinuxWindowData*) glfwGetWindowUserPointer(win);
		MouseScrollEvent ev(xoffset, yoffset);
		winData.EventCallback(ev);
	});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* win, double xpos, double ypos){

		LinuxWindowData& winData = *(LinuxWindowData*) glfwGetWindowUserPointer(win);
		MouseMoveEvent ev(xpos, ypos);
		winData.EventCallback(ev);
	});
}

void LinuxWindow::OnUpdate()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

void LinuxWindow::SetVSync(bool enable)
{
	if (enable)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	m_Data.IsVSyncEnabled = enable;
}

bool LinuxWindow::IsVSync() const
{
	return m_Data.IsVSyncEnabled;
}


LinuxWindow::~LinuxWindow()
{
	Shutdown();
}

void LinuxWindow::Shutdown()
{
	// glfwShowWindow(m_Window);
}

}


