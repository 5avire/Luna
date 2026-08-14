#include "Shader.h"

#include "Renderer.h"
#include "Luna/Log.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Luna {

    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case Luna::RenderAPI::None:    LUNA_CORE_ASSERT(false, "Luna doesn't have a headless build yet!"); break;
            case Luna::RenderAPI::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc); break;
        }

        LUNA_CORE_ASSERT(false, "UNKNOWN API");
        return nullptr;
    }

}
