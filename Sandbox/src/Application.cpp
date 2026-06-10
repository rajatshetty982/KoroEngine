#include <KoroEngine.h>

class ExampleLayer : public Koro::Layer
{
public:
	ExampleLayer()
	: Layer("examplelayer") {}

	void OnUpdate() override
	{
		// KORO_INFO("exLayer::Update");
	}

	void OnEvent(Koro::Event& e) override
	{
		KORO_TRACE("{0}", e);
	}
};

class Sandbox : public Koro::Application
{
public:
	Sandbox(){
		PushLayer(new ExampleLayer());
	}
	~Sandbox(){}
};

Koro::Application* Koro::CreateApplication()
{
	return new Sandbox;
}


