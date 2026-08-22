#include <lunapch.h>
#include "Shader.h"

#include "Renderer.h"
#include "Luna/Log.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Luna {

    Ref<Shader> Shader::Create(const std::string& pathToShader)
    {
        switch (Renderer::GetAPI())
        {
            case Luna::RendererAPI::API::None:    LUNA_CORE_ASSERT(false, "Luna doesn't have a headless build yet!"); break;
            case Luna::RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(pathToShader); break;
        }

        LUNA_CORE_ASSERT(false, "UNKNOWN API");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case Luna::RendererAPI::API::None:    LUNA_CORE_ASSERT(false, "Luna doesn't have a headless build yet!"); break;
            case Luna::RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc); break;
        }

        LUNA_CORE_ASSERT(false, "UNKNOWN API");
        return nullptr;
    }

    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        auto& name = shader->GetName();
        LUNA_CORE_ASSERT(!Exists(name), "Shader already exists");
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
    {
        LUNA_CORE_ASSERT(!Exists(name), "Shader already exists");
        m_Shaders[name] = shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string filePath)
    {
        auto shader = Shader::Create(filePath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string name, const std::string filePath)
    {
        auto shader = Shader::Create(filePath);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name)
    {
        LUNA_CORE_ASSERT(Exists(name), "Shader not found!");
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string& name) const
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }
}
