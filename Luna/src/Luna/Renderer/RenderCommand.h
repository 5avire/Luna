#pragma once

#include "RendererAPI.h"

namespace Luna {

    class RenderCommand
    {
        public:
            inline static void Init()
            {
                s_RendererAPI->Init();
            }

            inline static void SetViewport(int x, int y, int width, int height)
            {
                s_RendererAPI->SetViewport(x, y, width, height);
            }

            inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0)
            {
                s_RendererAPI->DrawIndexed(vertexArray, indexCount);
            }

            inline static void SetClearColor(const glm::vec4& color)
            {
                s_RendererAPI->SetClearColor(color);
            }

            inline static void Clear()
            {
                s_RendererAPI->Clear();
            }
        private:
            static Scope<RendererAPI> s_RendererAPI;
    };

}
