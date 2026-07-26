#include "Application.h"

#include "Luna/Events/ApplicationEvent.h"
#include "Luna/Log.h"

namespace Luna {

    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        WindowResizeEvent e(1280, 720);
        LUNA_TRACE(e.ToString());

        LUNA_CORE_CRITICAL("Not subscribed to cherno");

        while(true);
    }
}
