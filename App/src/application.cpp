#include <Luna.h>
#include <Platform/OpenGL/OpenGLShader.h>

#include <imgui/imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
                -0.5f, -0.5f, +0.0f,
                +0.5f, -0.5f, +0.0f,
                +0.5f, +0.5f, +0.0f,
                -0.5f, +0.5f, +0.0f
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
                uniform mat4 u_ModelPosition;

                void main()
                {
                   v_Color = a_Color;
                   gl_Position = u_ViewProjection * u_ModelPosition * vec4(a_Pos, 1.0f);
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
                uniform mat4 u_ModelPosition;

                void main()
                {
                   gl_Position = u_ViewProjection * u_ModelPosition * vec4(a_Pos, 1.0f);
                }
            )";

            std::string sqFragmentShader = R"( 
                #version 460 core

                layout (location = 0) out vec4 color;

                uniform vec3 u_Color;

                void main()
                {
                   color = vec4(u_Color, 1.0);
                }
            )";

            m_ShaderSq.reset(Luna::Shader::Create(sqVertexShader, sqFragmentShader));
        }

        void OnUpdate(Luna::Timestep ts) override
        {
            Luna::RenderCommand::SetClearColor({0.15f, 0.15f, 0.15f, 1.00f});
            Luna::RenderCommand::Clear();

            TriangleMovement(ts);
            lerpCameraToTriangle();

            m_Camera.SetPosition(glm::vec3(m_CameraPos[3]));

            Luna::Renderer::BeginScene(m_Camera);

            glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

            m_ShaderSq->Bind();

            for (int x = 0; x < 20; x++)
            {
                for (int y = 0; y < 20; y++)
                {
                    glm::vec3 pos(y * 0.11f, x * 0.11f, 0.0f);
                    glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

                    std::dynamic_pointer_cast<Luna::OpenGLShader>(m_ShaderSq)->UploadUniformFloat3(m_SquareColor, "u_Color");

                    Luna::Renderer::Submit(m_ShaderSq, m_SqVertexArray, transform);
                }
            }

            Luna::Renderer::Submit(m_Shader, m_VertexArray, m_TrianglePos);

            Luna::Renderer::EndScene();
        }

        void OnImGuiRender() override
        {
            ImGui::Begin("Luna-Engine");
            ImGui::Text("Welcome to Luna Engine!!");
            ImGui::Separator();
            ImGui::Text("Settings: ");
            ImGui::ColorEdit3("Squares Color", glm::value_ptr(m_SquareColor));
            ImGui::End();
        }

        void OnEvent(Luna::Event& event) override
        {
        }
    private:
        bool TriangleMovement(Luna::Timestep ts)
        {
            if (Luna::Input::IsKeyPressed(LunaKey_Up))
                m_TrianglePos = glm::translate(m_TrianglePos, glm::vec3(0.0f, 2.0f * ts, 0.0f));
            else if (Luna::Input::IsKeyPressed(LunaKey_Down))
                m_TrianglePos = glm::translate(m_TrianglePos, glm::vec3(0.0f, -2.0f * ts, 0.0f));

            if (Luna::Input::IsKeyPressed(LunaKey_Right))
                m_TrianglePos = glm::translate(m_TrianglePos, glm::vec3(2.0f * ts, 0.0f, 0.0f));
            else if (Luna::Input::IsKeyPressed(LunaKey_Left))
                m_TrianglePos = glm::translate(m_TrianglePos, glm::vec3(-2.0f * ts, 0.0f, 0.0f));

            return false;
        }

        void lerpCameraToTriangle()
        {
            m_CameraPos = (0.90f * m_CameraPos) + (0.10f * m_TrianglePos);
        }
    private:
        Luna::CameraOrtho m_Camera;
        glm::mat4 m_CameraPos = glm::mat4(1.0f);
        float m_CameraRotation = 0.0f;

        std::shared_ptr<Luna::Shader> m_Shader;
        std::shared_ptr<Luna::VertexArray> m_VertexArray;

        std::shared_ptr<Luna::Shader> m_ShaderSq;
        std::shared_ptr<Luna::VertexArray> m_SqVertexArray;

        float m_CameraSpeed = 2.0f;
        float m_CameraRotationSpeed = 90.0f;

        glm::vec3 m_SquareColor = {0.2, 0.3, 0.8};
        glm::mat4 m_TrianglePos = glm::mat4(1.0f);
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
