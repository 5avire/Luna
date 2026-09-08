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
    m_LunaLogo = Luna::Texture2D::Create("Assets/Texture/LunaLogo.png");
    m_Texture = Luna::Texture2D::Create("Assets/Texture/RPGpack_sheet.png");
    m_CheckeredTexture = Luna::Texture2D::Create("Assets/Texture/Checkerboard.png");

    m_StairLTR = Luna::SubTexture2D::CreateFromCoords(m_Texture, {7, 6}, {64, 64});
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

    Luna::Renderer2D::ResetStats();
    // -- Render --
    {
        LUNA_PROFILE_SCOPE("Renderer Prep");

        Luna::RenderCommand::SetClearColor({0.15f, 0.15f, 0.15f, 1.00f});
        Luna::RenderCommand::Clear();
    }

    {
        LUNA_PROFILE_SCOPE("Renderer Draw");

        Luna::Renderer2D::BeginScene(m_CameraController.GetCamera());

        Luna::Renderer2D::DrawRotatedQuad(m_QuadPos, m_QuadSize, m_Rotation, m_QuadColor);
        Luna::Renderer2D::DrawRotatedQuad({-1.0f, 0.0f}, {1.5f, 1.5f}, glm::radians(0.0f), m_LunaLogo);
        Luna::Renderer2D::DrawQuad({0.0f, 0.0f, -1.0f}, {25.0f, 25.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, m_CheckeredTexture, 10.0f);
        Luna::Renderer2D::DrawQuad({-1.0f, -1.0f}, {0.5f, 0.5f}, {0.8f, 0.3f, 0.2f, 1.0f});

        Luna::Renderer2D::DrawQuad({3.0f, 0.0f, 0.1f}, {1.5f, 1.5f}, m_StairLTR);

        Luna::Renderer2D::EndScene();


        Luna::Renderer2D::BeginScene(m_CameraController.GetCamera());
        for (float y = -5.0f; y < 5.0f; y += 0.5f)
        {
            for (float x = -5.0f; x < 5.0f; x += 0.5f)
            {
                glm::vec4 color = {(x + 5.0f)/ 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f};
                Luna::Renderer2D::DrawQuad({x, y}, {0.45f, 0.45f}, color);
            }
        }
        Luna::Renderer2D::EndScene();
    }
}

void Sandbox2D::OnImGuiRender()
{
    LUNA_PROFILE_FUNCTION();
    Luna::Renderer2D::Statistics stats = Luna::Renderer2D::GetStats();

    if (showRendererStat)
    {
        ImGui::Begin("Luna-Engine");
        ImGui::Text("Sandbox2D Test");
        ImGui::SeparatorText("Info");
        ImGui::Text("Frame time: %f s\n", m_FrameTime);
        ImGui::Text("FPS: %f", (1.0f / m_FrameTime));
        ImGui::Text("Draw call: %u", stats.DrawCalls);
        ImGui::Text("Quad count: %u", stats.QuadCount);
        ImGui::Text("Vertex count: %u", stats.GetTotalVertexCount());
        ImGui::Text("Index count: %u", stats.GetTotalIndexCount());
        ImGui::End();
    }
}

void Sandbox2D::OnEvent(Luna::Event& event)
{
    m_CameraController.OnEvent(event);

    Luna::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Luna::KeyPressedEvent>(LUNA_BIND_EVENT_FN(Sandbox2D::OnKeyPressed));
}

bool Sandbox2D::OnKeyPressed(Luna::KeyPressedEvent& e)
{
    if (e.GetKeyCode() == LunaKey_Tab)
    {
        showRendererStat = !showRendererStat;
    }
    return false;
}
