#pragma once
#include <lunapch.h>

#include "Luna/Renderer/Camera.h"
#include "Luna/Renderer/Texture.h"

namespace Luna {

    class Renderer2D
    {
        public:
            static void Init();
            static void Shutdown();
            static void OnWindowResize(int width, int height);

            static void BeginScene(const CameraOrtho& camera);
            static void EndScene();

            // Primitives, rotation should come in as radians
            static void DrawQuad(const glm::vec2& position,const glm::vec2& size, const Ref<Texture2D>& texture);
            static void DrawQuad(const glm::vec3& position,const glm::vec2& size, const Ref<Texture2D>& texture);
            static void DrawQuad(const glm::vec2& position,const glm::vec2& size, const glm::vec4& color = glm::vec4(1.0f), const Ref<Texture2D>& texture = nullptr);
            static void DrawQuad(const glm::vec3& position,const glm::vec2& size, const glm::vec4& color = glm::vec4(1.0f), const Ref<Texture2D>& texture = nullptr);

            static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const float rotation, const Ref<Texture2D>& texture = nullptr);
            static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const float rotation, const Ref<Texture2D>& texture = nullptr);
            static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const float rotation, const glm::vec4& color, const Ref<Texture2D>& texture = nullptr);
            static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const float rotation, const glm::vec4& color, const Ref<Texture2D>& texture = nullptr);
    };

}
