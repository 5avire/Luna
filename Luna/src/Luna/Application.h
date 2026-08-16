#pragma once

#include "Core.h"

#include "Luna/Window.h"
#include "Luna/LayerStack.h"
#include "Luna/Events/Event.h"
#include "Luna/Events/ApplicationEvent.h"

#include "Luna/ImGui/ImGuiLayer.h"

#include <memory>

#include "Luna/Renderer/Shader.h"
#include "Luna/Renderer/Buffer.h"
#include "Luna/Renderer/VertexArray.h"

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

            std::shared_ptr<Shader> m_Shader;
            std::shared_ptr<VertexArray> m_VertexArray;

            std::shared_ptr<Shader> m_ShaderSq;
            std::shared_ptr<VertexArray> m_SqVertexArray;
        private:
            static Application* s_Instance;
    };

    // To be defined by user
    Application* CreateApplication();
}
