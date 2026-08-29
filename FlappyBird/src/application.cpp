#include <Luna.h>
#include <LunaEntryPoint.h>

#include <imgui/imgui.h>

#include "FlappyBird.h"

class Sandbox : public Luna::Application
{
    public:
        Sandbox()
        {
            PushLayer(new FlappyBird());
        }

        ~Sandbox()
        {
        }
};

Luna::Application* Luna::CreateApplication()
{
    return new Sandbox();
}
