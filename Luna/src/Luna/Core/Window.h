#pragma once
#include <lunapch.h>

#include "Luna/Core/Core.h"
#include "Luna/Events/Event.h"


namespace Luna {

    struct WindowProps
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        WindowProps(const std::string& title = "Luna Engine",
                    uint32_t width = 1280,
                    uint32_t height = 720
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

            virtual uint32_t GetWidth() const = 0;
            virtual uint32_t GetHeight() const = 0;
            virtual float GetTime() const = 0;

            // Attributes
            virtual void SetEventCallback(const EventCallBackFn& callback) = 0;
            virtual void SetVSync(bool enabled) = 0;
            virtual bool IsVSync() const = 0;

            virtual void* GetNativeWindow() const = 0;

            static Scope<Window> Create(const WindowProps& props = WindowProps());
    };
}
