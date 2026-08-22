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

            static Ref<Shader> Create(const std::string& pathToShader);
            static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
        private:
            uint32_t m_ShaderID;
    };

}
