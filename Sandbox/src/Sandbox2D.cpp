#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


Sandbox2D::Sandbox2D()
    : m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
    LUNA_PROFILE_FUNCTION();

    Luna::Renderer2D::Init();
    m_Texture = Luna::Texture2D::Create("Assets/Texture/LunaLogo.png");
    m_CheckeredTexture = Luna::Texture2D::Create("Assets/Texture/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
    LUNA_PROFILE_FUNCTION();

    Luna::Renderer2D::Shutdown();
}

void Sandbox2D::OnUpdate(Luna::Timestep ts)
{
    LUNA_PROFILE_FUNCTION();

    // -- Update --
    m_FrameTime = ts;
    m_CameraController.OnUpdate(ts);

    // -- Render --
    {
        LUNA_PROFILE_SCOPE("Renderer Prep");
        Luna::RenderCommand::SetClearColor({0.15f, 0.15f, 0.15f, 1.00f});
        Luna::RenderCommand::Clear();
    }

    {
        LUNA_PROFILE_SCOPE("Renderer Draw");
        Luna::Renderer2D::BeginScene(m_CameraController.GetCamera());

        Luna::Renderer2D::DrawRotatedQuad(m_SquarePos, m_SquareScale, glm::radians(m_Rotation), m_QuadColor);
        Luna::Renderer2D::DrawRotatedQuad({-1.0f, 0.0f}, {0.5f, 0.8f}, glm::radians(0.0f), {0.8f, 0.3f, 0.2f, 1.0f});
        Luna::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {100.0f, 100.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, m_CheckeredTexture);

        Luna::Renderer2D::EndScene();
    }
}

void Sandbox2D::OnImGuiRender()
{
    LUNA_PROFILE_FUNCTION();

    ImGui::Begin("Luna-Engine");
    ImGui::Text("Sandbox2D Test");
    ImGui::SeparatorText("Info");
    ImGui::Text("Frame time: %f s\n", m_FrameTime);
    ImGui::Text("FPS: %f", (1.0f / m_FrameTime));
    ImGui::SeparatorText("Settings");
    ImGui::SliderFloat("Square Rotation", &m_Rotation, -180.0f, 180.0f);
    ImGui::SliderFloat2("Square Pos", glm::value_ptr(m_SquarePos), -10.0f, 10.0f);
    ImGui::SliderFloat2("Square Scale", glm::value_ptr(m_SquareScale), 0.05f, 5.0f);
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_QuadColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Luna::Event& event)
{
    m_CameraController.OnEvent(event);
}
