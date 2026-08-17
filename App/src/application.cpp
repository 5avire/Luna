#include <Luna.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>

class ExampleLayer : public Luna::Layer
{
    public:
        ExampleLayer()
            : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
        {
            m_VertexArray.reset(Luna::VertexArray::Create());

            float vertices[3 * 7] = {
                -0.5f, -0.5f, +0.0f, -0.0f, -0.0f, +0.5f, +1.0f,
                +0.5f, -0.5f, +0.0f, +1.0f, -0.0f, +0.5f, +1.0f,
                +0.0f, +0.5f, +0.0f, +0.5f, +1.0f, +0.5f, +1.0f
            };

            std::shared_ptr<Luna::VertexBuffer> vertexBuffer;
            vertexBuffer.reset(Luna::VertexBuffer::Create(vertices, sizeof(vertices)));

            Luna::BufferLayout layout = {
                { Luna::ShaderDataType::Float3, "a_Pos" },
                { Luna::ShaderDataType::Float4, "a_Color" }
            };
            vertexBuffer->SetLayout(layout);
            m_VertexArray->AddVertexBuffer(vertexBuffer);

            uint32_t indices[3] = { 0, 1, 2 };

            std::shared_ptr<Luna::IndexBuffer> indexBuffer;
            indexBuffer.reset(Luna::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
            m_VertexArray->SetIndexBuffer(indexBuffer);

            m_SqVertexArray.reset(Luna::VertexArray::Create());

            float sqVertices[4 * 3] = {
                -0.6f, -0.6f, +0.0f,
                +0.6f, -0.6f, +0.0f,
                +0.6f, +0.6f, +0.0f,
                -0.6f, +0.6f, +0.0f
            };
            std::shared_ptr<Luna::VertexBuffer> squareVB(Luna::VertexBuffer::Create(sqVertices, sizeof(sqVertices)));

            Luna::BufferLayout sqLayout = {
                { Luna::ShaderDataType::Float3, "a_Pos" },
            };
            squareVB->SetLayout(sqLayout);
            m_SqVertexArray->AddVertexBuffer(squareVB);

            uint32_t sqIndices[6] = { 0, 1, 2, 2, 3, 0 };
            std::shared_ptr<Luna::IndexBuffer> squareIB(Luna::IndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t)));
            m_SqVertexArray->SetIndexBuffer(squareIB);

            std::string vertexShader = R"( 
                #version 460 core

                layout (location = 0) in vec3 a_Pos;
                layout (location = 1) in vec4 a_Color;
                out vec4 v_Color;

                uniform mat4 u_ViewProjection;

                void main()
                {
                   v_Color = a_Color;
                   gl_Position = u_ViewProjection * vec4(a_Pos, 1.0f);
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

            m_Shader.reset(Luna::Shader::Create(vertexShader, fragmentShader));

            std::string sqVertexShader = R"( 
                #version 460 core

                layout (location = 0) in vec3 a_Pos;

                uniform mat4 u_ViewProjection;

                void main()
                {
                   gl_Position = u_ViewProjection * vec4(a_Pos, 1.0f);
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

            m_ShaderSq.reset(Luna::Shader::Create(sqVertexShader, sqFragmentShader));
        }

        void OnUpdate() override
        {
            Luna::RenderCommand::SetClearColor({0.15f, 0.15f, 0.15f, 1.00f});
            Luna::RenderCommand::Clear();

            CameraMovement();

            m_Camera.SetPosition(m_CameraPos);
            m_Camera.SetRotation(m_CameraRotation);

            Luna::Renderer::BeginScene(m_Camera);

            Luna::Renderer::Submit(m_ShaderSq, m_SqVertexArray);

            Luna::Renderer::Submit(m_Shader, m_VertexArray);

            Luna::Renderer::EndScene();

        }

        void OnImGuiRender() override
        {
            ImGui::Begin("Luna-Engine");
            ImGui::Text("Welcome to Luna Engine!!");
            ImGui::End();
        }

        void OnEvent(Luna::Event& event) override
        {
        }
    private:
        bool CameraMovement()
        {
            if (Luna::Input::IsKeyPressed(LunaKey_S))
                m_CameraPos.y += 0.4f * 0.016f;
            if (Luna::Input::IsKeyPressed(LunaKey_W))
                m_CameraPos.y -= 0.4f * 0.016f;

            if (Luna::Input::IsKeyPressed(LunaKey_A))
                m_CameraPos.x += 0.4f * 0.016f;
            if (Luna::Input::IsKeyPressed(LunaKey_D))
                m_CameraPos.x -= 0.4f * 0.016f;

            if (Luna::Input::IsKeyPressed(LunaKey_E))
                m_CameraRotation += 15.0f * 0.016f;
            if (Luna::Input::IsKeyPressed(LunaKey_Q))
                m_CameraRotation -= 15.0f * 0.016f;

            return true;
        }
    private:
        Luna::CameraOrtho m_Camera;
        glm::vec3 m_CameraPos = glm::vec3(0.0f);
        float m_CameraRotation = 0.0f;

        std::shared_ptr<Luna::Shader> m_Shader;
        std::shared_ptr<Luna::VertexArray> m_VertexArray;

        std::shared_ptr<Luna::Shader> m_ShaderSq;
        std::shared_ptr<Luna::VertexArray> m_SqVertexArray;
};

class Sandbox : public Luna::Application
{
    public:
        Sandbox()
        {
            PushLayer(new ExampleLayer());
        }

        ~Sandbox()
        {
        }
};

Luna::Application* Luna::CreateApplication()
{
    return new Sandbox();
}
