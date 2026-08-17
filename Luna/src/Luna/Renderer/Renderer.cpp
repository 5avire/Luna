#include "Renderer.h"

namespace Luna {

    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::BeginScene(CameraOrtho& camera)
    {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMat();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray)
    {
        shader->Bind();
        shader->UploadUniformMat4(m_SceneData->ViewProjectionMatrix, "u_ViewProjection");
        RenderCommand::DrawIndexed(vertexArray);
    }

}
