#include "LinuxInput.h"

#include "GLFW/glfw3.h"
#include "KoroEngine/Core/Application.h"
#include "KoroEngine/Core/Input.h"
#include <utility>

namespace Koro {

Input* Input::s_Instance = new LinuxInput();

bool LinuxInput::IsKeyPressedImpl(int keycode) const
{
	auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	int state = glfwGetKey(window, keycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool LinuxInput::IsMouseButtonPressedImpl(int keycode)const
{

	auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	int state = glfwGetKey(window, keycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

std::pair<double, double> LinuxInput::GetMousePosImpl() const 
{
	auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
	double xPos;
	double yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	return {xPos, yPos};
}

double LinuxInput::GetMouseXImpl() const 
{
	return GetMousePosImpl().first;
}

double LinuxInput::GetMouseYImpl() const 
{
	return GetMousePosImpl().second;
}

}
