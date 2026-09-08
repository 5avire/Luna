#pragma once

#include "Luna/Renderer/Framebuffer.h"

namespace Luna {

    class OpenGLFramebuffer : public Framebuffer
    {
        public:
            OpenGLFramebuffer(const FrameBufferSpecification& spec);
            virtual ~OpenGLFramebuffer();

            void Invalidate();
            void SetSpecification(const FrameBufferSpecification& spec) override;

            void Bind() const override;
            void Unbind() const override;
            void Resize(uint32_t width, uint32_t height) override;

            uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
            const uint32_t GetRendererID() const override { return m_RendererID; }
            const FrameBufferSpecification& GetSpecification() const override { return m_FrameBufferSpecification; }
        private:
            uint32_t m_RendererID = 0;
            uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
            FrameBufferSpecification m_FrameBufferSpecification;
    };

}
