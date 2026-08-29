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
        Ref<Shader> ColorTextureShader;
        Ref<Texture2D> WhiteTexture;
    };

    static Renderer2DData* s_Renderer2DState;

    void Renderer2D::Init()
    {
        LUNA_PROFILE_FUNCTION();

        s_Renderer2DState = new Renderer2DData();
        s_Renderer2DState->QuadVertexArray = VertexArray::Create();

        float sqVertices[4 * 5] = {
            -0.5f, -0.5f, +0.0f, 0.0f, 0.0f,
            +0.5f, -0.5f, +0.0f, 1.0f, 0.0f,
            +0.5f, +0.5f, +0.0f, 1.0f, 1.0f,
            -0.5f, +0.5f, +0.0f, 0.0f, 1.0f
        };
        Ref<VertexBuffer> squareVB(VertexBuffer::Create(sqVertices, sizeof(sqVertices)));

        BufferLayout sqLayout = {
            { ShaderDataType::Float3, "a_Pos" },
            { ShaderDataType::Float2, "a_TexCoord" },
        };
        squareVB->SetLayout(sqLayout);
        s_Renderer2DState->QuadVertexArray->AddVertexBuffer(squareVB);

        uint32_t sqIndices[6] = { 0, 1, 2, 2, 3, 0 };
        Ref<IndexBuffer> squareIB(IndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t)));
        s_Renderer2DState->QuadVertexArray->SetIndexBuffer(squareIB);

        s_Renderer2DState->WhiteTexture = Texture2D::Create(1, 1);
        uint32_t texData = 0xffffffff;
        s_Renderer2DState->WhiteTexture->SetData(&texData, sizeof(texData));

        s_Renderer2DState->ColorTextureShader = Shader::Create("Assets/Shader/ColorTextureShader.glsl");

        s_Renderer2DState->ColorTextureShader->SetInt(0, "u_Texture");
    }

    void Renderer2D::Shutdown()
    {
        LUNA_PROFILE_FUNCTION();

        delete s_Renderer2DState;
    }

    void Renderer2D::OnWindowResize(int width, int height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer2D::BeginScene(const CameraOrtho& camera)
    {
        LUNA_PROFILE_FUNCTION();

        s_Renderer2DState->ColorTextureShader->Bind();
        s_Renderer2DState->ColorTextureShader->SetMat4(camera.GetViewProjectionMat(), "u_ViewProjection");
    }

    void Renderer2D::EndScene()
    {
        LUNA_PROFILE_FUNCTION();
    }

    void Renderer2D::DrawQuad(const glm::vec2& position,const glm::vec2& size, const Ref<Texture2D>& texture, const float tilingFactor)
    {
        DrawQuad({position.x, position.y, 0.0f}, size, glm::vec4(1.0f), texture, tilingFactor);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position,const glm::vec2& size, const Ref<Texture2D>& texture, const float tilingFactor)
    {
        DrawQuad(position, size, {1.0f, 1.0f, 1.0f, 1.0f}, texture, tilingFactor);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position,const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture, const float tilingFactor)
    {
        DrawQuad({position.x, position.y, 0.0f}, size, color, texture, tilingFactor);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position,const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture, const float tilingFactor)
    {
        LUNA_PROFILE_FUNCTION();

        const Ref<Texture2D>& tex = texture ? texture : s_Renderer2DState->WhiteTexture;

        tex->Bind();
        s_Renderer2DState->ColorTextureShader->Bind();
        s_Renderer2DState->ColorTextureShader->SetFloat4(color, "u_Color");
        s_Renderer2DState->ColorTextureShader->SetFloat(tilingFactor, "u_TilingFactor");
        s_Renderer2DState->ColorTextureShader->SetMat4(
                glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size, 1.0f}),
                "u_ModelPosition"
        );
        RenderCommand::DrawIndexed(s_Renderer2DState->QuadVertexArray);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const float rotation, const Ref<Texture2D>& texture, const float tilingFactor)
    {
        DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, {1.0f, 1.0f, 1.0f, 1.0f}, texture, tilingFactor);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const float rotation, const Ref<Texture2D>& texture, const float tilingFactor)
    {
        DrawRotatedQuad(position, size, rotation, {1.0f, 1.0f, 1.0f, 1.0f}, texture, tilingFactor);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec4& color, const Ref<Texture2D>& texture, const float tilingFactor)
    {
        DrawRotatedQuad({position.x, position.y, 0.0f}, size, rotation, color, texture, tilingFactor);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const float rotation, const glm::vec4& color, const Ref<Texture2D>& texture, const float tilingFactor)
    {
        LUNA_PROFILE_FUNCTION();

        const Ref<Texture2D>& tex = texture ? texture : s_Renderer2DState->WhiteTexture;

        tex->Bind();
        s_Renderer2DState->ColorTextureShader->Bind();
        s_Renderer2DState->ColorTextureShader->SetFloat4(color, "u_Color");
        s_Renderer2DState->ColorTextureShader->SetFloat(tilingFactor, "u_TilingFactor");
        s_Renderer2DState->ColorTextureShader->SetMat4(
                glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), {size, 1.0f}),
                "u_ModelPosition"
        );
        RenderCommand::DrawIndexed(s_Renderer2DState->QuadVertexArray);
    }

}
