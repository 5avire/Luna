#pragma once

namespace Luna {

    enum class RenderAPI
    {
        None = 0, OpenGL = 1
    };

    class Renderer
    {
        public:
            inline static RenderAPI GetAPI() { return m_RenderAPI; }
        private:
            static RenderAPI m_RenderAPI;
    };
}
