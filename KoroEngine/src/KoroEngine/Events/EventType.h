#pragma once

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
