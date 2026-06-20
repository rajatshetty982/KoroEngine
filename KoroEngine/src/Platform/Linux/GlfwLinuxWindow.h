#pragma once

#include "KoroEngine/Core/Window.h"

struct GLFWwindow;

namespace Koro 
{

static bool s_GLFWInitialised = false;

class LinuxWindow : public IWindow
{
public:
	LinuxWindow(const WindowData& data);
	virtual ~LinuxWindow();

	void OnUpdate() override;

	inline uint32_t GetWidth() const override { return m_Data.Width; }
	inline uint32_t GetHeight() const override { return m_Data.Height; }

	virtual void* GetNativeWindow() const override { return m_Window; }

	inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
	void SetVSync(bool enabled) override;
	bool IsVSync() const override;

private:
	virtual void Init(const WindowData& data);
	virtual void Shutdown();

	struct LinuxWindowData
	{
		std::string Title;
		uint32_t Width, Height;
		EventCallbackFn EventCallback;
		bool IsVSyncEnabled;
	};

	LinuxWindowData m_Data;
	GLFWwindow* m_Window;

};

}
