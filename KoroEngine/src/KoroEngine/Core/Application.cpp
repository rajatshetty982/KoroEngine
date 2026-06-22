#include "Application.h"

#include <GL/gl.h>

#include "Platform.h"
#include "Window.h"
#include "Log.h"
#include "Input.h"
#include "KoroEngine/Events/ApplicationEvent.h"
#include "KoroEngine/Events/Event.h"
#include "KoroEngine/Events/EventBuffer.h"


namespace Koro {

Application* Application::s_Instance = nullptr;

Application::Application() 
	: m_Window(IWindow::Make())
	, m_ProcessBuffer(std::make_shared<EventBuffer>())
	, m_ReceiveBuffer(std::make_shared<EventBuffer>())
{
	KORO_ASSERT(!s_Instance, "Application already exists!");
	s_Instance = this;

	m_Window->SetEventCallback([this](Event& event) {
		this->OnEvent(event);
	});
}

Application::~Application()
{

}

void Application::Run()
{
	WindowResizeEvent e(1200, 720);
	KORO_ENG_INFO(e);
	long  num = 0;

	glClearColor(0.2,0.1,1,0);

	while (m_Running)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		std::swap(m_ReceiveBuffer, m_ProcessBuffer);
		ProcessBuffer(*m_ProcessBuffer, [this](Event& e)
				{
				this->UpdateEventPipeline(e);
				});


		m_ProcessBuffer->Clear();

		// Stage 3: Logic & Rendering
		for (Layer* layer : m_LayerStack) {
			layer->OnUpdate();
		}

		m_Window->OnUpdate(); 

		auto [x, y] = Input::GetMousePos();
		KORO_ENG_TRACE("{0}, {1}", x, y); 
	}
	return;
}

void Application::OnEvent(Event& e)
{
	// KORO_ENG_TRACE("{0}", e);
	e.PushToBuffer(*m_ReceiveBuffer);
	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
	{
		(*--it)->OnEvent(e);
		if (e.Handled())
			break;
	}
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}

void Application::UpdateEventPipeline(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(
		[this](WindowCloseEvent& event){
			return this->OnWindowClose(event);
		});
}

void Application::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}

void Application::PushOverlay(Layer* overlay)
{
	m_LayerStack.PushOverlay(overlay);
	overlay->OnAttach();
}
} // Koro
