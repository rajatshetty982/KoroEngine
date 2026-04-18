#pragma once

#include "Platform.h"

namespace Koro {

class KORO_API Application
{
public:
	Application();
	virtual ~Application();

public:
	void Run();
}; // Application

Application* CreateApplication();

} // Koro
