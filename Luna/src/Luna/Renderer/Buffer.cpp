#include "Buffer.h"

#include "Luna/Log.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Luna {

    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetAPI())
        {
            case Luna::RendererAPI::API::None:    LUNA_CORE_ASSERT(false, "Luna doesn't have a headless build yet!"); break;
            case Luna::RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexBuffer>(vertices, size); break;
        }

        LUNA_CORE_ASSERT(false, "UNKNOWN API");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* vertices, uint32_t count)
    {
        switch (Renderer::GetAPI())
        {
            case Luna::RendererAPI::API::None:    LUNA_CORE_ASSERT(false, "Luna doesn't have a headless build yet!"); break;
            case Luna::RendererAPI::API::OpenGL:  return std::make_shared<OpenGLIndexBuffer>(vertices, count); break;
        }

        LUNA_CORE_ASSERT(false, "UNKNOWN API");
        return nullptr;
    }

}
