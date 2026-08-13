#include "Luna/ImGui/ImGuiLayer.h"
#include <Luna.h>
#include <imgui/imgui.h>

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

        void OnImGuiRender() override
        {
            ImGui::Begin("Test");
            ImGui::Text("Hello ImGui");
            ImGui::End();
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
