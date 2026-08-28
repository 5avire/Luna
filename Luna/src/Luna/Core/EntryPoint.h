#pragma once

#include "Luna/Core/Log.h"
#include "Luna/Core/Application.h"

extern Luna::Application* Luna::CreateApplication();

int main(int argc, char** argv)
{
    Luna::Log::Init();

    LUNA_CORE_INFO("Starting...");

    LUNA_PROFILE_BEGIN_SESSION("Startup", "LunaProfile-Startup.json");
    auto app = Luna::CreateApplication();
    LUNA_PROFILE_END_SESSION();
    LUNA_CORE_ASSERT(app, "App creation failed");

    LUNA_PROFILE_BEGIN_SESSION("Runtime", "LunaProfile-Runtime.json");
    app->Run();
    LUNA_PROFILE_END_SESSION();

    LUNA_PROFILE_BEGIN_SESSION("Shutdown", "LunaProfile-Shutdown.json");
    delete app;
    LUNA_PROFILE_END_SESSION();

    LUNA_CORE_INFO("Terminating...");
}
