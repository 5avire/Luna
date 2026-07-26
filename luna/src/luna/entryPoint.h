#pragma once

#include "application.h"

extern Luna::Application* Luna::CreateApplication();

int main(int argc, char** argv)
{
    auto app = Luna::CreateApplication();
    app->Run();
    delete app;
}
