#pragma once

#include "Luna/Core.h"
#include "Luna/Events/Event.h"
#include "Luna/Core/Timestep.h"

namespace Luna {

    class Layer
    {
        public:
            Layer(const std::string& name = "Layer");
            virtual ~Layer();

            virtual void OnAttach() {}
            virtual void OnDetach() {}
            virtual void OnUpdate(Timestep ts) {}
            virtual void OnImGuiRender() {}
            virtual void OnEvent(Event& event) {}

            inline const std::string& GetName() const { return m_DebugName; }
        protected:
            std::string m_DebugName;
    };
}
