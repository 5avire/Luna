#include <lunapch.h>

#include <glad/glad.h>
#include "OpenGLFramebuffer.h"

namespace Luna {

    OpenGLFramebuffer::OpenGLFramebuffer(const FrameBufferSpecification& spec)
        : m_FrameBufferSpecification(spec)
    {
        Invalidate();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        glDeleteFramebuffers(1, &m_RendererID);
        glDeleteTextures(1, &m_ColorAttachment);
        glDeleteTextures(1, &m_DepthAttachment);
    }

    void OpenGLFramebuffer::Invalidate()
    {
        if (m_RendererID)
        {
            glDeleteFramebuffers(1, &m_RendererID);
            glDeleteTextures(1, &m_ColorAttachment);
            glDeleteTextures(1, &m_DepthAttachment);
        }

        glCreateFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
        glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA8,
                m_FrameBufferSpecification.Width,
                m_FrameBufferSpecification.Height,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                nullptr
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);
        
        glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
        glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
        glTexStorage2D(
                GL_TEXTURE_2D,
                1,
                GL_DEPTH24_STENCIL8,
                m_FrameBufferSpecification.Width,
                m_FrameBufferSpecification.Height
        );
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

        LUNA_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::SetSpecification(const FrameBufferSpecification& spec)
    {
        m_FrameBufferSpecification = spec;
        Invalidate();
    }

    void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
    {
        m_FrameBufferSpecification.Width = width;
        m_FrameBufferSpecification.Height = height;
        Invalidate();
    }

    void OpenGLFramebuffer::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glViewport(0, 0, m_FrameBufferSpecification.Width, m_FrameBufferSpecification.Height);
    }

    void OpenGLFramebuffer::Unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

}
