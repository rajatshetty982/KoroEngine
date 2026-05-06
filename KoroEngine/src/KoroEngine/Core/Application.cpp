#include "Application.h"

#include "koropch.h"

#include "KoroEngine/Events/ApplicationEvent.h"
#include "KoroEngine/Core/Log.h"
#include "KoroEngine/Events/EventBuffer.h"
#include <sstream>

namespace Koro {

Application::Application()
{

}

Application::~Application()
{

}

void Application::Run()
{
	WindowResizeEvent e(1200, 720);
	KORO_ENG_INFO(e);
	long  num = 0;
	while (1)
	{
		printf("Run: %ld\n", ++num);
		// Stage 2: Swap and Process
		// std::swap(m_ReceiveBuffer, m_ProcessBuffer);
		// Koro::ProcessBuffer(*m_ProcessBuffer);
		// m_ProcessBuffer->Clear();

		// Stage 3: Logic & Rendering
		// for (Layer* layer : m_LayerStack) {
		// 	layer->OnUpdate();
		// }

		// m_Window->OnUpdate(); 

	}
	return;
}

void Application::OnEvent(Event& e)
{
	e.PushToBuffer(*m_ReceiveBuffer);
}

} // Koro
