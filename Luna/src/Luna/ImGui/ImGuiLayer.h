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

            virtual void OnAttach() override;
            virtual void OnDetach() override;
            virtual void OnImGuiRender() override;

            void Begin();
            void End();
        private:
            float m_Time = 0.0f;
    };
}
