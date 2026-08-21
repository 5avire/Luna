#include <lunapch.h>
#include "Shader.h"

#include "Renderer.h"
#include "Luna/Log.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Luna {

    Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case Luna::RendererAPI::API::None:    LUNA_CORE_ASSERT(false, "Luna doesn't have a headless build yet!"); break;
            case Luna::RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc); break;
        }

        LUNA_CORE_ASSERT(false, "UNKNOWN API");
        return nullptr;
    }

}
