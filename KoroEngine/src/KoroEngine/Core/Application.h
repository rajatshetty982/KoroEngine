#pragma once

#include "Platform.h"
#include "KoroEngine/Events/Event.h"
#include <memory>

namespace Koro {

class KORO_API Application
{
public:
	Application();
	virtual ~Application();

public:
	void Run();
	void OnEvent(Event&);

private:
	bool m_Running = true;
	std::shared_ptr<EventBuffer> m_ReceiveBuffer;
	std::shared_ptr<EventBuffer> m_ProcessBuffer;
}; // Application

Application* CreateApplication();

} // Koro
