#pragma once

#include "koropch.h"

#include "Platform.h"
#include "Window.h"
#include "LayerStack.h"
#include "Layer.h"
#include "KoroEngine/Events/EventBuffer.h"
#include "KoroEngine/Events/ApplicationEvent.h"

namespace Koro {

class KORO_API Application
{
public:
	Application();
	virtual ~Application();

	void Run();
	void OnEvent(Event&);
	void UpdateEventPipeline(Event& e);

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* overlay);

private:
	bool OnWindowClose(WindowCloseEvent& e);

	bool m_Running = true;
	std::unique_ptr<IWindow> m_Window;

	std::shared_ptr<EventBuffer> m_ReceiveBuffer;
	std::shared_ptr<EventBuffer> m_ProcessBuffer;

	LayerStack m_LayerStack;
}; // Application

Application* CreateApplication();

} // Koro
