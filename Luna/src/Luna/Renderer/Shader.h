#pragma once

#include <lunapch.h>

#include "Luna/Core/Core.h"
#include <glm/glm.hpp>

namespace Luna {

    class Shader
    {
        public:
            virtual ~Shader() {}

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;

            virtual const std::string& GetName() const = 0;

            virtual void SetFloat4(const glm::vec4& value, const std::string& name) = 0;
            virtual void SetFloat3(const glm::vec3& value, const std::string& name) = 0;
            virtual void SetMat4(const glm::mat4& matrix, const std::string& name) = 0;
            virtual void SetInt(const int value, const std::string& name) = 0;
            virtual void SetFloat(const float value, const std::string& name) = 0;

            static Ref<Shader> Create(const std::string& pathToShader);
            static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
    };

    class ShaderLibrary
    {
        public:
            void Add(const Ref<Shader>& shader);
            void Add(const std::string& name, const Ref<Shader>& shader);
            Ref<Shader> Load(const std::string filePath);
            Ref<Shader> Load(const std::string name, const std::string filePath);

            Ref<Shader> Get(const std::string& name);

            bool Exists(const std::string& name) const;
        private:
            std::unordered_map<std::string, Ref<Shader>> m_Shaders;
    };

}
