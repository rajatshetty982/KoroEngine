#pragma once

#include "GLFW/glfw3.h"
#include "KoroEngine/Core/Layer.h"
#include "KoroEngine/Core/Platform.h"
#include "KoroEngine/Events/Event.h"
#include "KoroEngine/Events/ApplicationEvent.h"
#include "KoroEngine/Events/MouseEvent.h"
#include "KoroEngine/Events/KeyEvent.h"

namespace Koro {

class KORO_API ImGuiLayer : public Layer
{
public:
	ImGuiLayer();
	~ImGuiLayer();

	void OnUpdate();
	void OnEvent(Event&);

	virtual void OnAttach();
	virtual void OnDetach();

private:
	bool OnKeyPressedEvent(KeyPressEvent& e);
	bool OnKeyReleaseEvent(KeyReleaseEvent& e);
	bool OnMouseButtonPressEvent(MouseButtonPressEvent& e);
	bool OnMouseButtonReleaseEvent(MouseButtonReleaseEvent& e);
	bool OnMouseScrollEvent(MouseScrollEvent& e);
	bool OnMouseMoveEvent(MouseMoveEvent& e);
	bool OnWindowResizeEvent(WindowResizeEvent& e);
	bool OnKeyTypedEvent(KeyTypeEvent& e);
	bool OnMouseScrolledEvent(MouseScrollEvent& e);
private:
	float m_Time = 0.0f;
	GLFWwindow* m_WindowHandle = nullptr;
};

}
