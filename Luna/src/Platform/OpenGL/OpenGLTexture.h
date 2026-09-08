#pragma once
#include <lunapch.h>

#include "Luna/Renderer/Texture.h"

#include <glad/glad.h>

namespace Luna {

    class OpenGLTexture2D : public Texture2D
    {
        public:
            OpenGLTexture2D(const std::string& path);
            OpenGLTexture2D(uint32_t width, uint32_t height);
            virtual ~OpenGLTexture2D();

            virtual void SetData(void* data, uint32_t size) override;

            virtual uint32_t GetWidth() const override { return m_Width; }
            virtual uint32_t GetHeight() const override { return m_Height; }

            virtual void Bind(uint32_t slot = 0) const override;
            virtual const uint32_t GetRendererID() const override;

            virtual bool operator=(const Texture& other) const override;
        private:
            uint32_t m_RendererID;
            std::string m_Path;
            uint32_t m_Width, m_Height;

            GLenum m_InternalFormat, m_DataFormat;
    };

}
