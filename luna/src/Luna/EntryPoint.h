#pragma once

#include "Application.h"

#include "Log.h"

extern Luna::Application* Luna::CreateApplication();

int main(int argc, char** argv)
{
    Luna::Log::Init();

    auto app = Luna::CreateApplication();
    app->Run();
    delete app;
}
