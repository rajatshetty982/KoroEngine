#pragma once

#include "koropch.h"
#include "KoroEngine/Core/Input.h"
#include <cmath>

namespace Koro {

class LinuxInput : public Input
{
	protected:
	virtual bool IsKeyPressedImpl(int keycode) const override;

	virtual bool IsMouseButtonPressedImpl(int keycode)const override;
	virtual std::pair<double, double> GetMousePosImpl() const override;
	virtual double GetMouseXImpl() const override;
	virtual double GetMouseYImpl() const override;
};

}
