#include "Application.h"

#include "Luna/Log.h"
#include "Luna/Input.h"

#include <glad/glad.h>

#include <string>
#include <cstdint>

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

        m_VertexArray.reset(VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, +0.0f, -0.0f, -0.0f, +0.5f, +1.0f,
            +0.5f, -0.5f, +0.0f, +1.0f, -0.0f, +0.5f, +1.0f,
            +0.0f, +0.5f, +0.0f, +0.5f, +1.0f, +0.5f, +1.0f
        };


        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Pos" },
            { ShaderDataType::Float4, "a_Color" }
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };

        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SqVertexArray.reset(VertexArray::Create());

        float sqVertices[4 * 3] = {
            -0.6f, -0.6f, +0.0f,
            +0.6f, -0.6f, +0.0f,
            +0.6f, +0.6f, +0.0f,
            -0.6f, +0.6f, +0.0f
        };
        std::shared_ptr<VertexBuffer> squareVB(VertexBuffer::Create(sqVertices, sizeof(sqVertices)));

        BufferLayout sqLayout = {
            { ShaderDataType::Float3, "a_Pos" },
        };
        squareVB->SetLayout(sqLayout);
        m_SqVertexArray->AddVertexBuffer(squareVB);

        uint32_t sqIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<IndexBuffer> squareIB(IndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t)));
        m_SqVertexArray->SetIndexBuffer(squareIB);

        std::string vertexShader = R"( 
            #version 460 core

            layout (location = 0) in vec3 a_Pos;
            layout (location = 1) in vec4 a_Color;
            out vec4 v_Color;

            void main()
            {
               gl_Position = vec4(a_Pos, 1.0f);
               v_Color = a_Color;
            }
        )";

        std::string fragmentShader = R"( 
            #version 460 core

            layout (location = 0) out vec4 color;
            in vec4 v_Color;

            void main()
            {
               color = v_Color;
            }
        )";

        m_Shader.reset(Shader::Create(vertexShader, fragmentShader));

        std::string sqVertexShader = R"( 
            #version 460 core

            layout (location = 0) in vec3 a_Pos;

            void main()
            {
               gl_Position = vec4(a_Pos, 1.0f);
            }
        )";

        std::string sqFragmentShader = R"( 
            #version 460 core

            layout (location = 0) out vec4 color;

            void main()
            {
               color = vec4(0.2f, 0.8f, 1.0f, 1.0f);
            }
        )";

        m_ShaderSq.reset(Shader::Create(sqVertexShader, sqFragmentShader));
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
            glClearColor(0.15f, 0.15f, 0.15f, 1.00f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_ShaderSq->Bind();
            m_SqVertexArray->Bind();
            glDrawElements(GL_TRIANGLES, m_SqVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

            m_Shader->Bind();
            m_VertexArray->Bind();
            glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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
