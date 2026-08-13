#pragma once

#include "Core.h"

#include "Luna/Window.h"
#include "Luna/LayerStack.h"
#include "Luna/Events/Event.h"
#include "Luna/Events/ApplicationEvent.h"

#include "Luna/ImGui/ImGuiLayer.h"

#include <memory>

#include "Luna/Renderer/Shader.h"

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

            std::unique_ptr<Window> m_Window;
            ImGuiLayer* m_ImGuiLayer;
            bool m_Running = true;
            LayerStack m_LayerStack;

            unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
            std::unique_ptr<Shader> m_Shader;
        private:
            static Application* s_Instance;
    };

    // To be defined by user
    Application* CreateApplication();
}
