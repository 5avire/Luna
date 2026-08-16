#pragma once
#include <lunapch.h>

#include "Luna/Core.h"
#include "Luna/Events/Event.h"


namespace Luna {

    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string& title = "Luna Engine",
                    unsigned int width = 1280,
                    unsigned int height = 720
                    )
            : Title(title), Width(width), Height(height)
        {
        }
    };

    // Interface representing a desktop system based Window
    class Window
    {
        public:
            using EventCallBackFn = std::function<void(Event&)>;

            virtual ~Window() {}

            virtual void OnUpdate() = 0;

            virtual unsigned int GetWidth() const = 0;
            virtual unsigned int GetHeight() const = 0;

            // Attributes
            virtual void SetEventCallback(const EventCallBackFn& callback) = 0;
            virtual void SetVSync(bool enabled) = 0;
            virtual bool IsVSync() const = 0;

            virtual void* GetNativeWindow() const = 0;

            static Window* Create(const WindowProps& props = WindowProps());
    };
}
