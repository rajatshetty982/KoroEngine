#include "Application.h"

#include "KoroEngine/Events/ApplicationEvent.h"
#include "KoroEngine/Core/Log.h"

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
	while (1);
	return;
}

} // Koro
