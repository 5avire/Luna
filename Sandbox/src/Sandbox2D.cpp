#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

// -------------- Temporary -------------------
#include <Platform/OpenGL/OpenGLShader.h>
// --------------------------------------------

Sandbox2D::Sandbox2D()
    : m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
    m_VertexArray = Luna::VertexArray::Create();

    float sqVertices[4 * 3] = {
        -0.5f, -0.5f, +0.0f,
        +0.5f, -0.5f, +0.0f,
        +0.5f, +0.5f, +0.0f,
        -0.5f, +0.5f, +0.0f
    };
    Luna::Ref<Luna::VertexBuffer> squareVB(Luna::VertexBuffer::Create(sqVertices, sizeof(sqVertices)));

    Luna::BufferLayout sqLayout = {
        { Luna::ShaderDataType::Float3, "a_Pos" },
    };
    squareVB->SetLayout(sqLayout);
    m_VertexArray->AddVertexBuffer(squareVB);

    uint32_t sqIndices[6] = { 0, 1, 2, 2, 3, 0 };
    Luna::Ref<Luna::IndexBuffer> squareIB(Luna::IndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t)));
    m_VertexArray->SetIndexBuffer(squareIB);

    m_Shader = Luna::Shader::Create("Assets/Shader/ColorShader.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Luna::Timestep ts)
{
    // -- Update --
    m_FrameTime = ts;
    m_CameraController.OnUpdate(ts);

    // -- Render --
    Luna::RenderCommand::SetClearColor({0.15f, 0.15f, 0.15f, 1.00f});
    Luna::RenderCommand::Clear();

    Luna::Renderer::BeginScene(m_CameraController.GetCamera());

    m_Shader->Bind();
    std::dynamic_pointer_cast<Luna::OpenGLShader>(m_Shader)->UploadUniformFloat4(m_SquareColor, "u_Color");

    Luna::Renderer::Submit(m_Shader, m_VertexArray);

    Luna::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Luna-Engine");
    ImGui::Text("Sandbox2D Test");
    ImGui::SeparatorText("Info");
    ImGui::Text("Frame time: %f s\n", m_FrameTime);
    ImGui::Text("FPS: %f", (1.0f / m_FrameTime));
    ImGui::SeparatorText("Settings");
    ImGui::ColorEdit4("Squares Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Luna::Event& event)
{
    m_CameraController.OnEvent(event);
}
