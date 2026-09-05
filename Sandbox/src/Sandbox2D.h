#pragma once

#include <Luna.h>

class Sandbox2D : public Luna::Layer
{
    public:
        Sandbox2D();
        virtual ~Sandbox2D() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate(Luna::Timestep ts) override;
        virtual void OnImGuiRender() override;
        virtual void OnEvent(Luna::Event& event) override;
    private:
        Luna::Ref<Luna::Shader> m_Shader;
        Luna::Ref<Luna::VertexArray> m_VertexArray;
        Luna::CameraOrthoController m_CameraController;

        Luna::Ref<Luna::Texture2D> m_Texture;
        Luna::Ref<Luna::Texture2D> m_CheckeredTexture;


        glm::vec4 m_QuadColor = { 0.2f, 0.3f, 0.8f, 1.0f };
        glm::vec2 m_QuadPos = { 0.0f, 0.0f };
        glm::vec2 m_QuadSize = { 1.0f, 1.0f };
        float m_Rotation = 0.0f;

        float m_FrameTime = 0.0f;
};
