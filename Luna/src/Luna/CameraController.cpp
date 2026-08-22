#include <lunapch.h>
#include "CameraController.h"

#include "Luna/Core.h"
#include "Luna/Input.h"
#include "Luna/KeyCodes.h"
#include "Luna/MouseButtonCodes.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Luna {

    CameraOrthoController::CameraOrthoController(float aspectRatio, bool enableRotation)
        : m_AspectRatio(aspectRatio), m_Rotation(enableRotation), m_CameraRotationSpeed(90.0f),
        m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
    {
    }

    void CameraOrthoController::OnUpdate(Timestep ts)
    {
        m_CameraSpeed = m_ZoomLevel;
        if (Input::IsKeyPressed(LunaKey_W))
            m_Pos += glm::vec3(0.0f, m_CameraSpeed * ts, 0.0f); 
        if (Luna::Input::IsKeyPressed(LunaKey_S))
            m_Pos -= glm::vec3(0.0f, m_CameraSpeed * ts, 0.0f); 

        if (Luna::Input::IsKeyPressed(LunaKey_A))
            m_Pos -= glm::vec3(m_CameraSpeed * ts, 0.0f, 0.0f); 
        if (Luna::Input::IsKeyPressed(LunaKey_D))
            m_Pos += glm::vec3(m_CameraSpeed * ts, 0.0f, 0.0f); 

        if (m_Rotation)
        {
            if (Luna::Input::IsKeyPressed(LunaKey_Q))
                m_RotationZ += m_CameraRotationSpeed * ts;
            else if (Luna::Input::IsKeyPressed(LunaKey_E))
                m_RotationZ -= m_CameraRotationSpeed * ts;

            m_Camera.SetRotation(m_RotationZ);
        }
        m_Camera.SetPosition(m_Pos);
    }

    void CameraOrthoController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(LUNA_BIND_EVENT_FN(CameraOrthoController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(LUNA_BIND_EVENT_FN(CameraOrthoController::OnWindowResized));
    }

    bool CameraOrthoController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        m_ZoomLevel -= e.GetYOffset() / 4;
        if (m_ZoomLevel <= 0.1f)
            m_ZoomLevel = 0.05f;
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

        return false;
    }
    
    bool CameraOrthoController::OnWindowResized(WindowResizeEvent& e)
    {
        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

}
