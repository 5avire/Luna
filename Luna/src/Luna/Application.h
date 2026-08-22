#pragma once
#include <lunapch.h>

#include "Core.h"

#include "Luna/Window.h"
#include "Luna/LayerStack.h"
#include "Luna/Events/Event.h"
#include "Luna/Events/ApplicationEvent.h"

#include "Luna/ImGui/ImGuiLayer.h"

namespace Luna {

    class Application
    {
        public:
            Application();
            virtual ~Application();

            void Run();

            void OnEvent(Event& e);

            void PushLayer(Layer* layer);
            void PushOverlay(Layer* layer);

            inline static Application& Get() { return *s_Instance; }
            inline Window& GetWindow() { return *m_Window; }
        private:
            bool OnWindowClose(WindowCloseEvent e);
            bool OnWindowResize(WindowResizeEvent e);
        private:
            Scope<Window> m_Window;
            ImGuiLayer* m_ImGuiLayer;
            bool m_Running = true;
            bool m_Minimized = false;
            LayerStack m_LayerStack;
            float m_LastFrameTime;
        private:
            static Application* s_Instance;
    };

    // To be defined by user
    Application* CreateApplication();
}
