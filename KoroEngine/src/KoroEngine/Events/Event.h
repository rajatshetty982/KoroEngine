#pragma once

#include "koropch.h"
#include "KoroEngine/Core/Platform.h"
#include "KoroEngine/Core/Core.h"
#include "KoroEngine/Events/EventType.h"
#include "KoroEngine/Events/EventBuffer.h"

#include <spdlog/fmt/ostr.h>
// Events are blocking rn, it should be buffered and then dequed later by something (Pass or event bus)

namespace Koro {

class EventBuffer;

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
	virtual EventType GetEventType() const override { return GetStaticType(); }\
	virtual const char* GetName() const override { return #type; }\
	virtual void PushToBuffer(EventBuffer& buffer) const override { buffer.PushDerivedEvent(*this); }


class KORO_API Event
{
	friend class EventDispactcher;

public:
	virtual ~Event() = default;
	virtual void PushToBuffer(EventBuffer& eventBuffer) const = 0;

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

		return m_Event.m_Handled;
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


