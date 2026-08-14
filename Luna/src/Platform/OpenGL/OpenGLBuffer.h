#pragma once

#include "Luna/Renderer/Buffer.h"

namespace Luna {

    class OpenGLVertexBuffer : public VertexBuffer
    {
        public:
            OpenGLVertexBuffer(float* vertices, uint32_t size);
            virtual ~OpenGLVertexBuffer() {}

            virtual void SetData() override {};

            virtual void Bind() const override;
            virtual void Unbind() const override;
        private:
            uint32_t m_RendererID;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
        public:
            OpenGLIndexBuffer(uint32_t* vertices, uint32_t count);
            virtual ~OpenGLIndexBuffer() {}

            virtual void SetData() override {};

            virtual void Bind() const override;
            virtual void Unbind() const override;
            virtual uint32_t GetCount() const override;
        private:
            uint32_t m_RendererID, m_Count;
    };

}
