#pragma once

#include <lunapch.h>

#include "Luna/Core.h"
#include <glm/glm.hpp>

namespace Luna {

    class Shader
    {
        public:
            virtual ~Shader() {}

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;

            virtual const std::string& GetName() const = 0;

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
