#include "OpenGLContext.h"

#include "Luna/Core/Log.h"

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
        LUNA_PROFILE_FUNCTION();

        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        LUNA_CORE_ASSERT(status, "Failed to load glad!");

        LUNA_CORE_INFO("OpenGL:");
        LUNA_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        LUNA_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        LUNA_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

#ifdef LUNA_ENABLE_ASSERTS
        int versionMajor, versionMinor;
        glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
        glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

        LUNA_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 6), "Luna requires at least OpenGL version 4.6!");
#endif
    }

    void OpenGLContext::SwapBuffers()
    {
        LUNA_PROFILE_FUNCTION();

        glfwSwapBuffers(m_WindowHandle);
    }
}
