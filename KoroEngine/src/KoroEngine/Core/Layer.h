#pragma once

#include "Platform.h"
#include "KoroEngine/Events/Event.h"

namespace Koro {
enum class LayerId
{
	Default = 0,

};

class KORO_API Layer
{
public:

	// Layer(const LayerId name = LayerId::Layer1);
	Layer(const std::string& name = "Layer");
	~Layer();

	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate() {}
	virtual void OnImGuiRender() {}

	virtual void OnEvent(Event&) {}

	inline const std::string& GetName() const { return m_DebugId; }

protected:
	std::string m_DebugId;
};

}
