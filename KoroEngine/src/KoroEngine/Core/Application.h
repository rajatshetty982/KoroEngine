#pragma once

#include "koropch.h"

#include "Platform.h"
#include "KoroEngine/Events/ApplicationEvent.h"
#include "Window.h"
#include "KoroEngine/Events/EventBuffer.h"

namespace Koro {

class KORO_API Application
{
public:
	Application();
	virtual ~Application();

public:
	void Run();
	void OnEvent(Event&);

	bool OnWindowClose(WindowCloseEvent& e);
	void UpdateEventPipeline(Event& e);

private:
	bool m_Running = true;

	std::unique_ptr<IWindow> m_Window;

	std::shared_ptr<EventBuffer> m_ReceiveBuffer;
	std::shared_ptr<EventBuffer> m_ProcessBuffer;
}; // Application

Application* CreateApplication();

} // Koro
