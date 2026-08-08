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
        }

        void OnEvent(Luna::Event& event) override
        {
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
