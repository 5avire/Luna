#include "GlobalWindow.h"
#include "Luna/Log.h"

namespace Luna {

    static bool s_GLFWInitialized = false;

    Window* Window::Create(const WindowProps& props)
    {
        return new GlobalWindow(props);
    }

    GlobalWindow::GlobalWindow(const WindowProps& props)
    {
        Init(props);
    }

    GlobalWindow::~GlobalWindow()
    {
        Shutdown();
    }

    void GlobalWindow::Init(const WindowProps& props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        LUNA_CORE_INFO("Creating Window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (!s_GLFWInitialized)
        {
            int success = glfwInit();
            LUNA_CORE_ASSERT(success, "Could not initialize GLFW");

            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);
    }

    void GlobalWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void GlobalWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void GlobalWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    bool GlobalWindow::IsVSync() const
    {
        return m_Data.VSync;
    }
}
