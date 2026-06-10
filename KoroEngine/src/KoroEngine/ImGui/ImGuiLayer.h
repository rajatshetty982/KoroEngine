#pragma once

#include "KoroEngine/Core/Layer.h"

namespace Koro {

class ImGuiLayer : public Layer
{
public:
	ImGuiLayer();
	~ImGuiLayer();

	void OnUpdate();
	void OnEvent(Event&);

	virtual void OnAttach();
	virtual void OnDetach();
private:

};

}
