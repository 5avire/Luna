#include <lunapch.h>
#include "Texture.h"

#include "Luna/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Luna {

    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
            case Luna::RendererAPI::API::None:    LUNA_CORE_ASSERT(false, "Luna doesn't have a headless build yet!"); break;
            case Luna::RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path); break;
        }

        LUNA_CORE_ASSERT(false, "UNKNOWN API");
        return nullptr;
    }

}
