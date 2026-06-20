#pragma once

#include "koropch.h"

#include "Event.h"
#include <cmath>

namespace Koro
{

class KORO_API MouseMoveEvent : public Event
{
public: 
	MouseMoveEvent(float x, float y)
	: m_MouseX(x), m_MouseY(y) {}

	inline float GetX() const { return m_MouseX; }
	inline float GetY() const { return m_MouseY; }
	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseMoveEvent: " << m_MouseX << ", " << m_MouseY;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseMove)
	EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

private:
	float m_MouseX, m_MouseY;
};

class KORO_API MouseScrollEvent : public Event
{
public: 
	MouseScrollEvent(double offsetX, double offsetY)
	: m_OffsetX(offsetX), m_OffsetY(offsetY) {}

	inline float GetXOffset() const { return m_OffsetX; }
	inline float GetYOffset() const { return m_OffsetY; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseMoveEvent: " << m_OffsetX << ", " << m_OffsetY;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseScroll)
	EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)


private:
	double m_OffsetX, m_OffsetY;

};


class KORO_API MouseButtonEvent : public Event
{
public:
	inline int GetMouseButton() const { return m_Button; }
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

protected:
	MouseButtonEvent(int button) : m_Button(button) {}

	int m_Button;
};

class KORO_API MouseButtonPressEvent : public MouseButtonEvent
{
public:
	MouseButtonPressEvent(int button) : MouseButtonEvent(button) {}
	EVENT_CLASS_TYPE(MouseButtonPress)
	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressEvent: " << m_Button;
		return ss.str();
	}
};


class KORO_API MouseButtonReleaseEvent : public MouseButtonEvent
{
public:
	MouseButtonReleaseEvent(int button) : MouseButtonEvent(button) {}
	EVENT_CLASS_TYPE(MouseButtonRelease)


	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleaseEvent: " << m_Button;
		return ss.str();
	}

};


}
