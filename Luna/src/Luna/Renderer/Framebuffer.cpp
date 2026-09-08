#include <lunapch.h>
#include "Framebuffer.h"

#include "Luna/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Luna {

    Ref<Framebuffer> Framebuffer::Create(const FrameBufferSpecification& spec)
    {
        switch (Renderer::GetAPI())
        {
            case Luna::RendererAPI::API::None:    LUNA_CORE_ASSERT(false, "Luna doesn't have a headless build yet!"); break;
            case Luna::RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec); break;
        }

        LUNA_CORE_ASSERT(false, "UNKNOWN API");
        return nullptr;
    }
}
