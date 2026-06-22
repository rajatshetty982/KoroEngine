#pragma once

#include "koropch.h"
#include "Platform.h"

namespace Koro {

class KORO_API Input
{
public:
	static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

static bool IsMouseButtonPressed(int keycode) { return s_Instance->IsMouseButtonPressedImpl(keycode); }
static std::pair<double, double> GetMousePos() { return s_Instance->GetMousePosImpl(); }
static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

protected:
virtual bool IsKeyPressedImpl(int keycode) const = 0;
virtual bool IsMouseButtonPressedImpl(int keycode) const = 0;
virtual std::pair<double, double> GetMousePosImpl() const = 0;
virtual double GetMouseXImpl() const = 0;
virtual double GetMouseYImpl() const = 0;

private:
static Input* s_Instance;
	};

}
