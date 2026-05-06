#pragma once

#include "koropch.h"
#include "Event.h"

namespace Koro {

class KORO_API WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() {}
	EVENT_CLASS_CATEGORY(EventCategoryApp)
		EVENT_CLASS_TYPE(WindowFocus)

	};


class KORO_API WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent() {}
	EVENT_CLASS_CATEGORY(EventCategoryApp)
		EVENT_CLASS_TYPE(WindowLostFocus)

	};


class KORO_API WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(unsigned int width, unsigned int height)
	: m_Width(width), m_Height(height) {}

	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: Width: " << m_Width << ", Height: " << m_Height;
		return ss.str();

	}

	EVENT_CLASS_TYPE(WindowResize)
	EVENT_CLASS_CATEGORY(EventCategoryApp)
private:
	unsigned int m_Width, m_Height;
};


class KORO_API WindowCloseEvent : public Event
	{
		public:
		WindowCloseEvent() {}
	EVENT_CLASS_CATEGORY(EventCategoryApp)
		EVENT_CLASS_TYPE(WindowClose)
	};


class KORO_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}
	EVENT_CLASS_CATEGORY(EventCategoryApp)
		EVENT_CLASS_TYPE(ATick)

	};

class KORO_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}
	EVENT_CLASS_CATEGORY(EventCategoryApp)
		EVENT_CLASS_TYPE(AUpdate)

	};

class KORO_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}
	EVENT_CLASS_CATEGORY(EventCategoryApp)
		EVENT_CLASS_TYPE(ARender)

	};
}




