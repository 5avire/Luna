#include "GlobalInput.h"

#include <GLFW/glfw3.h>

#include "Luna/Application.h"

namespace Luna {

    Input* Input::s_Instance = new GlobalInput();

    bool GlobalInput::IsKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool GlobalInput::IsMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> GlobalInput::GetMousePosImpl()
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return { (float)xpos, (float)ypos };
    }

    float GlobalInput::GetMouseXImpl()
    {
        auto[x, y] = GetMousePosImpl();
        return x;
    }

    float GlobalInput::GetMouseYImpl()
    {
        auto[x, y] = GetMousePosImpl();
        return y;
    }

}
