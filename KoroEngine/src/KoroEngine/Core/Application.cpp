#include "Application.h"

#include "KoroEngine/Core/Window.h"
#include "KoroEngine/Events/ApplicationEvent.h"
#include "KoroEngine/Core/Log.h"
#include "KoroEngine/Events/Event.h"
#include "KoroEngine/Events/EventBuffer.h"

#include <GL/gl.h>

namespace Koro {

Application::Application() 
	: m_Window(IWindow::Make())
	, m_ProcessBuffer(std::make_shared<EventBuffer>())
	, m_ReceiveBuffer(std::make_shared<EventBuffer>())
{
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
	glClear(GL_COLOR_BUFFER_BIT);

	while (m_Running)
	{
		std::swap(m_ReceiveBuffer, m_ProcessBuffer);

		ProcessBuffer(*m_ProcessBuffer, [this](Event&e)
					  {
					  this->UpdateEventPipeline(e);
					  });


		m_ProcessBuffer->Clear();

		// Stage 3: Logic & Rendering
		// for (Layer* layer : m_LayerStack) {
		// 	layer->OnUpdate();
		// }

		m_Window->OnUpdate(); 
	}
	return;
}

void Application::OnEvent(Event& e)
{
	KORO_ENG_TRACE("{0}", e);
	e.PushToBuffer(*m_ReceiveBuffer);
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
} // Koro
