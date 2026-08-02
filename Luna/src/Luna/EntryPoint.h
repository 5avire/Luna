#pragma once

#include "Luna/Log.h"
#include "Luna/Application.h"

extern Luna::Application* Luna::CreateApplication();

int main(int argc, char** argv)
{
    Luna::Log::Init();

    LUNA_CORE_INFO("Starting...");

    auto app = Luna::CreateApplication();
    app->Run();
    delete app;

    LUNA_CORE_INFO("Terminating...");
}
