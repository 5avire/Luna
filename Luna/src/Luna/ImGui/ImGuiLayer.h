#pragma once

#include "Luna/Layer.h"

#include "Luna/Events/Event.h"
#include "Luna/Events/KeyEvent.h"
#include "Luna/Events/MouseEvent.h"
#include "Luna/Events/ApplicationEvent.h"

namespace Luna {

    class ImGuiLayer : public Layer
    {
        public:
            ImGuiLayer();
            ~ImGuiLayer();

            void OnAttach();
            void OnDetach();
            void OnUpdate();
            void OnEvent(Event& event);
        private:
            bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
            bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
            bool OnMouseScrolledEvent(MouseScrolledEvent& e);
            bool OnMouseMovedEvent(MouseMovedEvent& e);
            bool OnKeyPressedEvent(KeyPressedEvent& e);
            bool OnKeyReleasedEvent(KeyReleasedEvent& e);
            bool OnKeyTypedEvent(KeyTypedEvent& e);
            bool OnWindowResizeEvent(WindowResizeEvent& e);
        private:
            float m_Time = 0.0f;
    };
}
