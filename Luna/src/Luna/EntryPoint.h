#pragma once

#include "Application.h"

#include "Log.h"

extern Luna::Application* Luna::CreateApplication();

int main(int argc, char** argv)
{
    Luna::Log::Init();

    LUNA_CORE_TRACE("Starting...");

    auto app = Luna::CreateApplication();
    app->Run();
    delete app;

    LUNA_CORE_TRACE("Terminating...");
}
