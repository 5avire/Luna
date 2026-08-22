#pragma once

#include "Luna/Renderer/RendererAPI.h"

namespace Luna {

    class OpenGLRendererAPI : public RendererAPI
    {
        public:
            virtual void Init() override;
            virtual void SetViewport(int x, int y, int width, int height) override;

            virtual void SetClearColor(const glm::vec4& color) override;
            virtual void Clear() override;

            virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
    };

}
