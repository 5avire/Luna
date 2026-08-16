#pragma once

#include "RenderCommand.h"

namespace Luna {

    class Renderer
    {
        public:
            static void BeginScene(); // TODO: Take all params
            static void EndScene();

            static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

            inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };
}
