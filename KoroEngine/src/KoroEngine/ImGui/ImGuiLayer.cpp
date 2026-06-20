#include "ImGuiLayer.h"
#include "koropch.h"

#include "KoroEngine/Core/Log.h"
#include "KoroEngine/Core/Application.h"
#include "KoroEngine/Events/KeyEvent.h"
#include "KoroEngine/Events/MouseEvent.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


namespace Koro {

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
{
}

ImGuiLayer::~ImGuiLayer()
{

}

void ImGuiLayer::OnAttach()
{
	IMGUI_CHECKVERSION();
	ImGuiContext* context = ImGui::CreateContext();
	ImGui::SetCurrentContext(context);
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	m_WindowHandle = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	if (!ImGui_ImplGlfw_InitForOpenGL(m_WindowHandle, false)) {
		KORO_ENG_ERROR("ImGui GLFW backend failed to initialize!");
	} else {
		KORO_ENG_INFO("ImGui GLFW backend initialized.");
	}

	if (!ImGui_ImplOpenGL3_Init("#version 410")) {
		KORO_ENG_ERROR("ImGui OpenGL3 backend failed to initialize!");
	} else {
		KORO_ENG_INFO("ImGui OpenGL3 backend initialized.");
	}

}

void ImGuiLayer::OnDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiLayer::OnUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::LogText("Ola");

	ImGuiIO& io = ImGui::GetIO();
	Application& app = Application::Get();
	io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

	float time = (float)glfwGetTime();
	io.DeltaTime = m_Time > 0.00 ? (time - m_Time) : (1.0f / 60.0f);
	m_Time = time;

	static bool show = true;
	ImGui::ShowDemoWindow(&show);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<KeyPressEvent>(KORO_EVENT_FN_BIND(&ImGuiLayer::OnKeyPressedEvent));
	dispatcher.Dispatch<KeyReleaseEvent>(KORO_EVENT_FN_BIND(&ImGuiLayer::OnKeyReleaseEvent));
	dispatcher.Dispatch<KeyTypeEvent>(KORO_EVENT_FN_BIND(&ImGuiLayer::OnKeyTypedEvent));
	dispatcher.Dispatch<MouseButtonPressEvent>(KORO_EVENT_FN_BIND(&ImGuiLayer::OnMouseButtonPressEvent));
	dispatcher.Dispatch<MouseButtonReleaseEvent>(KORO_EVENT_FN_BIND(&ImGuiLayer::OnMouseButtonReleaseEvent));
	dispatcher.Dispatch<MouseScrollEvent>(KORO_EVENT_FN_BIND(&ImGuiLayer::OnMouseScrollEvent));
	dispatcher.Dispatch<MouseMoveEvent>(KORO_EVENT_FN_BIND(&ImGuiLayer::OnMouseMoveEvent));
	dispatcher.Dispatch<WindowResizeEvent>(KORO_EVENT_FN_BIND(&ImGuiLayer::OnWindowResizeEvent));
}

bool ImGuiLayer::OnKeyPressedEvent(KeyPressEvent& e)
{
	int action = e.IsRepeat() ? GLFW_REPEAT : GLFW_PRESS;
	ImGui_ImplGlfw_KeyCallback(m_WindowHandle, e.GetKeyCode(), 0, action, 0);
	return false;
}

bool ImGuiLayer::OnKeyReleaseEvent(KeyReleaseEvent& e)
{
	ImGui_ImplGlfw_KeyCallback(m_WindowHandle, e.GetKeyCode(), 0, GLFW_RELEASE, 0);
	return false;
}

bool ImGuiLayer::OnKeyTypedEvent(KeyTypeEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	unsigned int keycode = e.GetKeyCode();
	if (keycode > 0 && keycode < 0x10000)
		ImGui_ImplGlfw_CharCallback(m_WindowHandle, keycode);

	return false;
}

bool ImGuiLayer::OnMouseButtonPressEvent(MouseButtonPressEvent& e)
{
	// int action = e.IsRepeat() ? GLFW_REPEAT : GLFW_PRESS;
	ImGui_ImplGlfw_MouseButtonCallback(m_WindowHandle, e.GetMouseButton(), GLFW_PRESS, 0);
	return false;
}

bool ImGuiLayer::OnMouseButtonReleaseEvent(MouseButtonReleaseEvent& e)
{

	ImGui_ImplGlfw_MouseButtonCallback(m_WindowHandle, e.GetMouseButton(), GLFW_RELEASE, 0);
	return false;
}

bool ImGuiLayer::OnMouseScrollEvent(MouseScrollEvent& e)
{
	ImGui_ImplGlfw_ScrollCallback(m_WindowHandle, e.GetXOffset(), e.GetYOffset());
	return false;
}

bool ImGuiLayer::OnMouseMoveEvent(MouseMoveEvent& e)
{
	ImGui_ImplGlfw_CursorPosCallback(m_WindowHandle, e.GetX(), e.GetY());
	return false;
}

bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
{
	return false;
}



}
