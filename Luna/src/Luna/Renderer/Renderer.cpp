#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Luna {

    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::Init()
    {
        RenderCommand::Init(); 
    }

    void Renderer::BeginScene(CameraOrtho& camera)
    {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMat();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const Ref<Shader> shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform)
    {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(m_SceneData->ViewProjectionMatrix, "u_ViewProjection");
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(transform, "u_ModelPosition");
        RenderCommand::DrawIndexed(vertexArray);
    }

}
