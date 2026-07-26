#include "Application.h"

#include "Luna/Events/ApplicationEvent.h"
#include "Luna/Log.h"

namespace Luna {

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while(m_Running)
        {
            m_Window->OnUpdate();
        }
    }
}
