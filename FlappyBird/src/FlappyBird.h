#pragma once

#include <Luna.h>

class FlappyBird : public Luna::Layer
{
    public:
        FlappyBird();
        virtual ~FlappyBird() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate(Luna::Timestep ts) override;
        virtual void OnImGuiRender() override;
        virtual void OnEvent(Luna::Event& event) override;
    private:
        bool OnKeyPressed(Luna::KeyPressedEvent& event);
        bool OnMouseButtonPressed(Luna::MouseButtonPressedEvent& event);

        void LerpBirdToExpectedPos();
    private:
        float m_AspectRatio = 1280.0f / 720.0f;
        float m_ZoomLevel = 1.0f;

        Luna::Ref<Luna::Shader> m_Shader;
        Luna::Ref<Luna::VertexArray> m_VertexArray;
        Luna::CameraOrthoController m_CameraController;

        Luna::Ref<Luna::Texture2D> m_Bird;
        Luna::Ref<Luna::Texture2D> m_Pipe;
        Luna::Ref<Luna::Texture2D> m_Base;
        Luna::Ref<Luna::Texture2D> m_Background;

        std::vector<glm::vec2> m_PipePos;
        float m_SpeedFactor = 1.0f;

        float m_BirdCurrYOffset = 0.0f;
        float m_BirdYOffset = 0.0f;

        float m_ScrollSpeed = 0.5f;

        float m_FrameTime = 0.0f;
};
