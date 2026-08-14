#include "Application.h"

#include "Luna/Log.h"
#include "Luna/Input.h"

#include <glad/glad.h>

#include <string>
#include <cstdint>

namespace Luna {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:     return GL_FLOAT;
            case ShaderDataType::Float2:    return GL_FLOAT;
            case ShaderDataType::Float3:    return GL_FLOAT;
            case ShaderDataType::Float4:    return GL_FLOAT;
            case ShaderDataType::Mat3:      return GL_FLOAT;
            case ShaderDataType::Mat4:      return GL_FLOAT;
            case ShaderDataType::Int:       return GL_INT;
            case ShaderDataType::Int2:      return GL_INT;
            case ShaderDataType::Int3:      return GL_INT;
            case ShaderDataType::Int4:      return GL_INT;
            case ShaderDataType::Bool:      return GL_BOOL;
            case ShaderDataType::None:      return GL_NONE;
        }

        LUNA_CORE_ASSERT(false, "Unknown ShaderDataType");
        return 0;
    }

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

        float vertices[3 * 7] = {
            -0.5f, -0.5f, +0.0f, -0.0f, -0.0f, +0.5f, +1.0f,
            +0.5f, -0.5f, +0.0f, +1.0f, -0.0f, +0.5f, +1.0f,
            +0.0f, +0.5f, +0.0f, +0.5f, +1.0f, +0.5f, +1.0f
        };
        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        {
            BufferLayout layout = {
                { ShaderDataType::Float3, "a_Pos" },
                { ShaderDataType::Float4, "a_Color" }
            };
            m_VertexBuffer->SetLayout(layout);
        }

        uint32_t index = 0;
        for (const auto& element : m_VertexBuffer->GetLayout())
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                    index,
                    element.GetComponentCount(),
                    ShaderDataTypeToOpenGLBaseType(element.Type),
                    element.Normalized ? GL_TRUE : GL_FALSE,
                    m_VertexBuffer->GetLayout().GetStride(),
                    (const void*)(uintptr_t)element.Offset
            );
            index++;
        }

        uint32_t indices[3] = { 0, 1, 2 };
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

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
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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
