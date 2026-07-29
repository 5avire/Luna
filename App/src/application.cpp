#include <Luna.h>

class ExampleLayer : public Luna::Layer
{
    public:
        ExampleLayer()
            : Layer("Example")
        {
        }


        void OnUpdate() override
        {
            LUNA_INFO("ExampleLayer::Update");
        }

        void OnEvent(Luna::Event& event) override
        {
            LUNA_TRACE("{0}", event);
        }
};

class Sandbox : public Luna::Application
{
    public:
        Sandbox()
        {
            PushLayer(new ExampleLayer());
        }

        ~Sandbox()
        {
        }
};

Luna::Application* Luna::CreateApplication()
{
    return new Sandbox();
}
