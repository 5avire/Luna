#include <lunapch.h>
#include "Luna/Renderer/Renderer2D.h"

#include "Luna/Renderer/RenderCommand.h"

#include "Luna/Renderer/Shader.h"
#include "Luna/Renderer/VertexArray.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Luna {

    struct Renderer2DData
    {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> ColorShader;
    };

    static Renderer2DData* s_Renderer2DState;

    void Renderer2D::Init()
    {
        s_Renderer2DState = new Renderer2DData();
        s_Renderer2DState->QuadVertexArray = VertexArray::Create();

        float sqVertices[3 * 4] = {
            -0.5f, -0.5f, +0.0f,
            +0.5f, -0.5f, +0.0f,
            +0.5f, +0.5f, +0.0f,
            -0.5f, +0.5f, +0.0f
        };
        Ref<VertexBuffer> squareVB(VertexBuffer::Create(sqVertices, sizeof(sqVertices)));

        BufferLayout sqLayout = {
            { ShaderDataType::Float3, "a_Pos" },
        };
        squareVB->SetLayout(sqLayout);
        s_Renderer2DState->QuadVertexArray->AddVertexBuffer(squareVB);

        uint32_t sqIndices[6] = { 0, 1, 2, 2, 3, 0 };
        Ref<IndexBuffer> squareIB(IndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t)));
        s_Renderer2DState->QuadVertexArray->SetIndexBuffer(squareIB);

        s_Renderer2DState->ColorShader = Shader::Create("Assets/Shader/ColorShader.glsl");
    }

    void Renderer2D::Shutdown()
    {
        delete s_Renderer2DState;
    }

    void Renderer2D::OnWindowResize(int width, int height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer2D::BeginScene(const CameraOrtho& camera)
    {
        s_Renderer2DState->ColorShader->Bind();
        s_Renderer2DState->ColorShader->SetMat4(camera.GetViewProjectionMat(), "u_ViewProjection");
    }

    void Renderer2D::EndScene()
    {
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({position.x, position.y, 0.0f}, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        s_Renderer2DState->ColorShader->Bind();
        s_Renderer2DState->ColorShader->SetFloat4(color, "u_Color");
        s_Renderer2DState->ColorShader->SetMat4(
                glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size, 1.0f}),
                "u_ModelPosition"
        );
        RenderCommand::DrawIndexed(s_Renderer2DState->QuadVertexArray);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec4& color)
    {
        DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, color);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const float rotation, const glm::vec4& color)
    {
        s_Renderer2DState->ColorShader->Bind();
        s_Renderer2DState->ColorShader->SetFloat4(color, "u_Color");
        s_Renderer2DState->ColorShader->SetMat4(
                glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), {size, 1.0f}),
                "u_ModelPosition"
        );
        RenderCommand::DrawIndexed(s_Renderer2DState->QuadVertexArray);
    }

}
