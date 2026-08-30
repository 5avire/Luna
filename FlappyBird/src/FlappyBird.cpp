#include "FlappyBird.h"

#include <random>

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>

std::random_device rd;
std::mt19937 gen(rd());

FlappyBird::FlappyBird()
    : m_CameraController(m_AspectRatio, m_ZoomLevel)
{
}

void FlappyBird::OnAttach()
{
    LUNA_PROFILE_FUNCTION();

    Luna::Renderer2D::Init();
    m_Bird = Luna::Texture2D::Create("Assets/Texture/Bird.png");
    m_Pipe = Luna::Texture2D::Create("Assets/Texture/Pipe.png");
    m_Base = Luna::Texture2D::Create("Assets/Texture/Base.png");
    m_Background = Luna::Texture2D::Create("Assets/Texture/Background.png");
}

void FlappyBird::OnDetach()
{
    LUNA_PROFILE_FUNCTION();

    Luna::Renderer2D::Shutdown();
}

void FlappyBird::OnUpdate(Luna::Timestep ts)
{
    LUNA_PROFILE_FUNCTION();

    // -- Update --
    m_FrameTime = ts;

    // -- Render --
    Luna::RenderCommand::SetClearColor({0.1f, 0.1f, 0.5f, 1.00f});
    Luna::RenderCommand::Clear();

    Luna::Renderer2D::BeginScene(m_CameraController.GetCamera());

    // Background
    Luna::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {4.0f, 2.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, m_Background, 1.0f);

    if (m_Start)
    {
        static float counter = 0;
        counter += ts;

        if (counter > 1.5f / m_ScrollSpeed)
        {
            std::uniform_real_distribution<float> randGen(-0.5f, 0.5f);
            float yOffset = randGen(gen);

            m_PipePos.push_back(
                glm::vec2(m_ZoomLevel * m_AspectRatio + 0.2f, yOffset)
            );

            counter = 0;
            if (m_ScrollSpeed != 3.0f)
            {
                m_ScrollSpeed = 1.001f * m_ScrollSpeed;
                if (m_ScrollSpeed >= 3.0f)
                    m_ScrollSpeed = 3.0f;
            }
        }

        m_BirdYOffset -= 10.0f * ts * m_SpeedFactor * m_FrameTime;
        m_SpeedFactor += 1.0f * ts;

        LerpBirdToExpectedPos();

        // Colission
        // With top and bottom
        if (m_BirdCurrYOffset >= (0.95f - 0.25f + 0.12f / 2.0f) || m_BirdCurrYOffset <= (-0.95f + 0.25f - 0.12f / 2.0f))
            Luna::Application::Get().Close();

        // Pipe
        for (int index = 0; index < m_PipePos.size();)
        {
            float& pipePos = m_PipePos[index].x;
            float& yOffset = m_PipePos[index].y;

            const float gapY = 0.3f;

            Luna::Renderer2D::DrawRotatedQuad({pipePos, -1.0f - gapY + yOffset}, {0.25f, 2.0f}, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f}, m_Pipe, 1.0f);
            Luna::Renderer2D::DrawRotatedQuad({pipePos, +1.0f + gapY + yOffset}, {0.25f, 2.0f}, -3.14159f, {1.0f, 1.0f, 1.0f, 1.0f}, m_Pipe, 1.0);

            pipePos -= m_ScrollSpeed * ts;

            if (pipePos <= -(m_AspectRatio * m_ZoomLevel + 0.2f))
                m_PipePos.erase(m_PipePos.begin() + index);
            else
                index++;

            // Colission with pipes
            if (((pipePos + 0.25/2.0f) > -(0.12f/2.0f)) && ((pipePos - 0.25/2.0f) < +(0.12f/2.0f)))
            {
                if (!(m_BirdCurrYOffset <= (yOffset + gapY - 0.12f/2.0f) && m_BirdCurrYOffset >= (yOffset - gapY + 0.12f/2.0f)))
                    Luna::Application::Get().Close();
            }
        }
    }

    // Top & Bottom Base
    Luna::Renderer2D::DrawRotatedQuad({0.0f, -0.95f, +0.2f}, {4.0f, 0.25f}, 0.0f, {1.0f, 1.0f, 1.0f, 1.0f}, m_Base, 1.0f);
    Luna::Renderer2D::DrawRotatedQuad({0.0f, +0.95f, +0.2f}, {4.0f, 0.25f}, -3.14159f, {1.0f, 1.0f, 1.0f, 1.0f}, m_Base, 1.0f);

    Luna::Renderer2D::DrawRotatedQuad(
            {0.0f, m_BirdCurrYOffset, +0.1f},
            {0.12f, 0.12f},
            (((1.3f - m_SpeedFactor) /5.0f) <= -3.14159 / 2 ? -3.14159/2 : ((1.3f - m_SpeedFactor)/5.0f)),
            m_Bird
    );

    Luna::Renderer2D::EndScene();

}

void FlappyBird::OnImGuiRender()
{
}

void FlappyBird::OnEvent(Luna::Event& event)
{
    Luna::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Luna::KeyPressedEvent>(LUNA_BIND_EVENT_FN(FlappyBird::OnKeyPressed));
    dispatcher.Dispatch<Luna::MouseButtonPressedEvent>(LUNA_BIND_EVENT_FN(FlappyBird::OnMouseButtonPressed));
}

bool FlappyBird::OnKeyPressed(Luna::KeyPressedEvent& event)
{
    if (event.GetKeyCode() == LunaKey_Space)
    {
        if (!m_Start)
            m_Start = true;

        m_BirdYOffset += 12.0f * m_FrameTime * (m_SpeedFactor > 1.5f ? 1.5f : m_SpeedFactor);
        m_SpeedFactor = 1.0f;
    }
    return false;
}

bool FlappyBird::OnMouseButtonPressed(Luna::MouseButtonPressedEvent& event)
{
    if (event.GetMouseButton() == LunaMouseButton_1)
    {
        if (!m_Start)
            m_Start = true;

        m_BirdYOffset += 12.0f * m_FrameTime * (m_SpeedFactor > 1.5f ? 1.5f : m_SpeedFactor);
        m_SpeedFactor = 1.0f;
    }
    return false;
}

void FlappyBird::LerpBirdToExpectedPos()
{
    float t = 0.95f;
    m_BirdCurrYOffset = (1 - t) * m_BirdYOffset + t * m_BirdCurrYOffset;
}
