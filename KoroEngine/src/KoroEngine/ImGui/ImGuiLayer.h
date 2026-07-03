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

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnImGuiRender() override;

	void Begin();
	void End();

private:
	float m_Time = 0.0f;
	GLFWwindow* m_WindowHandle = nullptr;



// 	void OnEvent(Event&);
//
// private:
// 	bool OnKeyPressedEvent(KeyPressEvent& e);
// 	bool OnKeyReleaseEvent(KeyReleaseEvent& e);
// 	bool OnMouseButtonPressEvent(MouseButtonPressEvent& e);
// 	bool OnMouseButtonReleaseEvent(MouseButtonReleaseEvent& e);
// 	bool OnMouseScrollEvent(MouseScrollEvent& e);
// 	bool OnMouseMoveEvent(MouseMoveEvent& e);
// 	bool OnWindowResizeEvent(WindowResizeEvent& e);
// 	bool OnKeyTypedEvent(KeyTypeEvent& e);
// 	bool OnMouseScrolledEvent(MouseScrollEvent& e);
};

}
