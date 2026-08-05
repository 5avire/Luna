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
            if (event.GetEventType() == Luna::EventType::KeyPressed)
            {
                Luna::KeyPressedEvent& e = (Luna::KeyPressedEvent&)event;
                LUNA_INFO("Pressed: {0}", (char)e.GetKeyCode());
            }

            if (Luna::Input::IsMouseButtonPressed(LunaMouseButton_Left))
                LUNA_INFO("Clicked left mouse button");
        }
};

class Sandbox : public Luna::Application
{
    public:
        Sandbox()
        {
            PushLayer(new ExampleLayer());
            PushOverlay(new Luna::ImGuiLayer());
        }

        ~Sandbox()
        {
        }
};

Luna::Application* Luna::CreateApplication()
{
    return new Sandbox();
}
