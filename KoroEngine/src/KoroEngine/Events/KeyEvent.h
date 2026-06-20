#pragma once

#include "koropch.h"

#include "KoroEngine/Core/Platform.h"
#include "Event.h"

namespace Koro {

class KORO_API KeyEvent : public Event
{

public:
	inline int GetKeyCode() const { return m_KeyCode; }
	EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

protected:
	KeyEvent(int KeyCode)
	: m_KeyCode(KeyCode) {}

	int m_KeyCode;
};

class KORO_API KeyPressEvent : public KeyEvent
{
public:
	KeyPressEvent(int keycode, int repeatCount)
	: KeyEvent(keycode)
	, m_RepeatCount(repeatCount) {}

	inline int GetRepeatCount() { return m_RepeatCount; }
	inline bool IsRepeat() { return m_RepeatCount > 0; }

	std::string ToString()
	{
		std::stringstream ss;
		ss << "KeyPressEvent: " << m_KeyCode << ", repeat count: " << m_RepeatCount;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyPress)

private:
	int m_RepeatCount = 0;
};

class KORO_API KeyReleaseEvent : public KeyEvent
{
public:
	KeyReleaseEvent(int keycode)
	: KeyEvent(keycode) {}

	std::string ToString()
	{
		std::stringstream ss;
		ss << "KeyReleaseEvent: " << m_KeyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyRelease)

};

class KORO_API KeyTypeEvent : public KeyEvent
{
public:
	KeyTypeEvent(int keycode)
	: KeyEvent(keycode) {}

	std::string ToString()
	{
		std::stringstream ss;
		ss << "KeyTypeEvent: " << m_KeyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyType)

};

} // Koro
