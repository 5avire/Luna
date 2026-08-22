#include <Luna.h>

// -------------- Temporary -------------------
#include <Platform/OpenGL/OpenGLShader.h>
// --------------------------------------------

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
            m_SqVertexArray = Luna::VertexArray::Create();

            float sqVertices[4 * 7] = {
                -0.5f, -0.5f, +0.0f, 0.0f, 0.0f,
                +0.5f, -0.5f, +0.0f, 1.0f, 0.0f,
                +0.5f, +0.5f, +0.0f, 1.0f, 1.0f,
                -0.5f, +0.5f, +0.0f, 0.0f, 1.0f
            };
            Luna::Ref<Luna::VertexBuffer> squareVB(Luna::VertexBuffer::Create(sqVertices, sizeof(sqVertices)));

            Luna::BufferLayout sqLayout = {
                { Luna::ShaderDataType::Float3, "a_Pos" },
                { Luna::ShaderDataType::Float2, "a_TexCoord" }
            };
            squareVB->SetLayout(sqLayout);
            m_SqVertexArray->AddVertexBuffer(squareVB);

            uint32_t sqIndices[6] = { 0, 1, 2, 2, 3, 0 };
            Luna::Ref<Luna::IndexBuffer> squareIB(Luna::IndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t)));
            m_SqVertexArray->SetIndexBuffer(squareIB);

            m_TextureShader = Luna::Shader::Create("Assets/Shader/TextureShader.glsl");

            m_ColorShader = Luna::Shader::Create("Assets/Shader/ColorShader.glsl");

            m_Texture = Luna::Texture2D::Create("Assets/Texture/Checkerboard.png");
            m_TransparentTexture = Luna::Texture2D::Create("Assets/Texture/AwesomeFace.png");

            std::dynamic_pointer_cast<Luna::OpenGLShader>(m_TextureShader)->Bind();
            std::dynamic_pointer_cast<Luna::OpenGLShader>(m_TextureShader)->UploadUniformInt(0, "u_Texture");
        }

        void OnUpdate(Luna::Timestep ts) override
        {
            m_FrameTime = ts;

            Luna::RenderCommand::SetClearColor({0.15f, 0.15f, 0.15f, 1.00f});
            Luna::RenderCommand::Clear();

            PlayerMovement(ts);
            lerpCameraToPlayer();

            m_Camera.SetPosition(glm::vec3(m_CameraPos[3]));

            Luna::Renderer::BeginScene(m_Camera);

            glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

            m_ColorShader->Bind();

            for (int x = 0; x < 20; x++)
            {
                for (int y = 0; y < 20; y++)
                {
                    glm::vec3 pos(y * 0.11f, x * 0.11f, 0.0f);
                    glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

                    std::dynamic_pointer_cast<Luna::OpenGLShader>(m_ColorShader)->Bind();
                    std::dynamic_pointer_cast<Luna::OpenGLShader>(m_ColorShader)->UploadUniformFloat3(m_SquareColor, "u_Color");

                    Luna::Renderer::Submit(m_ColorShader, m_SqVertexArray, transform);
                }
            }

            m_Texture->Bind();
            Luna::Renderer::Submit(m_TextureShader, m_SqVertexArray, m_PlayerPos);

            m_TransparentTexture->Bind();
            Luna::Renderer::Submit(m_TextureShader, m_SqVertexArray, m_PlayerPos);

            Luna::Renderer::EndScene();
        }

        void OnImGuiRender() override
        {
            ImGui::Begin("Luna-Engine");
            ImGui::Text("Welcome to Luna Engine!!");
            ImGui::Separator();
            ImGui::Text("Frame time: %f s\n", m_FrameTime);
            ImGui::Text("FPS: %f", (1.0f / m_FrameTime));
            ImGui::Separator();
            ImGui::Text("Settings: ");
            ImGui::ColorEdit3("Squares Color", glm::value_ptr(m_SquareColor));
            ImGui::End();
        }

        void OnEvent(Luna::Event& event) override
        {
        }
    private:
        bool PlayerMovement(Luna::Timestep ts)
        {
            if (Luna::Input::IsKeyPressed(LunaKey_Up))
                m_PlayerPos = glm::translate(m_PlayerPos, glm::vec3(0.0f, 2.0f * ts, 0.0f));
            else if (Luna::Input::IsKeyPressed(LunaKey_Down))
                m_PlayerPos = glm::translate(m_PlayerPos, glm::vec3(0.0f, -2.0f * ts, 0.0f));

            if (Luna::Input::IsKeyPressed(LunaKey_Right))
                m_PlayerPos = glm::translate(m_PlayerPos, glm::vec3(2.0f * ts, 0.0f, 0.0f));
            else if (Luna::Input::IsKeyPressed(LunaKey_Left))
                m_PlayerPos = glm::translate(m_PlayerPos, glm::vec3(-2.0f * ts, 0.0f, 0.0f));

            return false;
        }

        void lerpCameraToPlayer()
        {
            m_CameraPos = (0.90f * m_CameraPos) + (0.10f * m_PlayerPos);
        }
    private:
        Luna::Ref<Luna::Shader> m_TextureShader;
        Luna::Ref<Luna::Shader> m_ColorShader;

        Luna::Ref<Luna::VertexArray> m_SqVertexArray;

        Luna::Ref<Luna::Texture> m_Texture, m_TransparentTexture;

        Luna::CameraOrtho m_Camera;
        glm::mat4 m_CameraPos = glm::mat4(1.0f);
        float m_CameraRotation = 0.0f;

        float m_CameraSpeed = 2.0f;
        float m_CameraRotationSpeed = 90.0f;

        glm::vec3 m_SquareColor = {0.2, 0.3, 0.8};
        glm::mat4 m_PlayerPos = glm::mat4(1.0f);

        float m_FrameTime;
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
