#include <KoroEngine.h>

class Sandbox : public Koro::Application
{
public:
	Sandbox(){}
	~Sandbox(){}
};

Koro::Application* Koro::CreateApplication()
{
	return new Sandbox;
}
