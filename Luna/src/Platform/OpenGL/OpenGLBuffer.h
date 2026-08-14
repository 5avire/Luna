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

            virtual const BufferLayout& GetLayout() const override { return m_Layout; }
            virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
        private:
            uint32_t m_RendererID;
            BufferLayout m_Layout;
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
            uint32_t m_RendererID;
            uint32_t m_Count;
    };

}
