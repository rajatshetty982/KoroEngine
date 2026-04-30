#pragma once

#include "KoroEngine/Core/Platform.h"
#include "KoroEngine/Core/Core.h"
#include <functional>

#include <spdlog/fmt/ostr.h>
// Events are blocking rn, it should be buffered and then dequed later by something (Pass or event bus)

namespace Koro {

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
	virtual EventType GetEventType() const override { return GetStaticType(); }\
	virtual const char* GetName() const override { return #type; }

enum class EventType
{
	NoEvent = 0,
	// mouse events

	MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll,

	// app events
	WindowFocus, WindowLostFocus, WindowResize, WindowClose,

	// other ap side events
	ATick, AUpdate, ARender,

	// keyboard events
	KeyPress, KeyRelease,
};

enum EventCategory
{
	EventCategoryMouse = (1),
	EventCategoryApp = (1 << 1),
	EventCategoryKeyboard = (1 << 2),
	EventCategoryMouseButton = (1 << 3),
	EventCategoryInput = (1 << 4),
};

class KORO_API Event
{
	friend class EventDispactcher;

public:
	virtual EventType GetEventType() const = 0;
	virtual int GetCategoryFlags() const = 0;
	virtual const char* GetName() const = 0;
	virtual std::string ToString() const { return GetName(); };
	inline bool IsInCategory(EventCategory category)
	{
		return category & GetCategoryFlags();
	}


protected:
	bool m_Handled = false;
};

class EventDispactcher
{
	template<typename T>
	using EventFn = std::function<bool(T&)>;

public:
	EventDispactcher(Event& e)
	: m_Event(e) {}

	template<typename T>
	// bool Dispatch(EventFn<T> func)
	bool Dispatch(std::function<bool(T&)> func)
	{
		if (m_Event.GetEventType() == T::GetStaticType())
		{
			m_Event.m_Handled = func(*(T*)&m_Event);
		}
	}

private:
	Event& m_Event;
};

// to directly log custom objects type in logger
inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
	return os << e.ToString();
}

} // Koro

// This tells fmt: "For Koro::Event and anything that inherits from it, 
template <typename T>
struct fmt::formatter<T, std::enable_if_t<std::is_base_of_v<Koro::Event, T>, char>> : ostream_formatter {};


