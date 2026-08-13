#include "OpenGLContext.h"

#include "Luna/Log.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Luna
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        LUNA_CORE_ASSERT(windowHandle, "WindowHandle doesn't exist!");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        LUNA_CORE_ASSERT(status, "Failed to load glad!");

        LUNA_CORE_INFO("OpenGL:");
        LUNA_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        LUNA_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        LUNA_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}
