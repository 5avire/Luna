#pragma once
#include <lunapch.h>

#include "Luna/Renderer/Shader.h"

namespace Luna {

    class OpenGLShader : public Shader
    {
        public:
            OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
            ~OpenGLShader();

            virtual void Bind() const override;
            virtual void Unbind() const override;

            virtual void UploadUniformMat4(const glm::mat4& matrix, const std::string& name) override;
        private:
            uint32_t m_RendererID;
    };

}
