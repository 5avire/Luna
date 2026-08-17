#pragma once

#include <lunapch.h>

#include <glm/glm.hpp>

namespace Luna {

    class Shader
    {
        public:
            virtual ~Shader() {}

            virtual void Bind() const = 0;
            virtual void Unbind() const = 0;

            virtual void UploadUniformMat4(const glm::mat4& matrix, const std::string& name) = 0;

            static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
        private:
            uint32_t m_ShaderID;
    };

}
