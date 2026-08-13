#include "Application.h"

#include "Luna/Log.h"
#include "Luna/Input.h"

#include <glad/glad.h>

#include <string>
#include "Luna/Renderer/Shader.h"

namespace Luna {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        LUNA_CORE_ASSERT(!s_Instance, "Application already exists");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        glGenBuffers(1, &m_VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
            +0.5f, -0.5f, 0.0f,
            +0.0f, +0.5f, 0.0f
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 3, vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

        glGenBuffers(1, &m_IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

        unsigned int indices[3] = { 0, 1, 2 };
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3, indices, GL_STATIC_DRAW);

        std::string vertexShader = R"( 
            #version 460 core

            layout (location = 0) in vec3 a_Pos;
            out vec3 v_Pos;

            void main()
            {
               gl_Position = vec4(a_Pos, 1.0f);
               v_Pos = a_Pos;
            }
        )";

        std::string fragmentShader = R"( 
            #version 460 core

            layout (location = 0) out vec4 color;
            in vec3 v_Pos;

            void main()
            {
               color = vec4(v_Pos + 0.5, 1.0);
            }
        )";

        m_Shader.reset(new Shader(vertexShader, fragmentShader));
    }

    Application::~Application()
    {
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.IsHandled())
                break;
        }
    }

    void Application::Run()
    {
        while(m_Running)
        {
            glClearColor(0.115f, 0.115f, 0.115f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            // Normal Layers Updates
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            // ImGui Rendering
            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent e)
    {
        m_Running = false;
        return true;
    };
}
