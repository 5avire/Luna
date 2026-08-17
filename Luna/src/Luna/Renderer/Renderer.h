#pragma once
#include <lunapch.h>

#include "Camera.h"
#include "Shader.h"
#include "RenderCommand.h"

namespace Luna {

    class Renderer
    {
        public:
            static void BeginScene(CameraOrtho& camera); // TODO: Take all params
            static void EndScene();

            static void Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray);

            inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
        private:
            struct SceneData
            {
                glm::mat4 ViewProjectionMatrix;
            };

            static SceneData* m_SceneData;
    };
}
