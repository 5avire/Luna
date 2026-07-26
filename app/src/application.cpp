#include <Luna.h>

#include <iostream>

class Sandbox : public Luna::Application
{
    public:
        Sandbox()
        {
            int counter = 0;
            std::cout << counter++ << std::endl;
        }

        ~Sandbox()
        {

        }
};

Luna::Application* Luna::CreateApplication()
{
    return new Sandbox();
}
