#pragma once

#ifdef KORO_PLATFORM_LINUX

extern Koro::Application* Koro::CreateApplication();

int main(int argc, char** argv)
{

	Koro::Log::Init();
	Koro::Log::GetCoreLogger()->warn("Initialised Engine!");
	Koro::Log::GetClientLogger()->critical("Initialised client app!");


	auto app = Koro::CreateApplication();
	app->Run();
	delete app;
}

#elif defined(KORO_PLATFORM_WINDOWS)

// NOTE: more windows specific logic to be added here later, rn its just a copy of linux implementaion
int main(int argc, char** argv)
{
	auto app = Koro::CreateApplication();
	app->Run();
	delete app;
}

#endif
