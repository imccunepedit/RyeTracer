#include "Camera.h"

#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"

#include "Utils.h"

using namespace Rye;

void Camera::Resize(int w, int h)
{
    if ((w == film.width && h == film.height) || w*h <= 1 )
        return;

    Rye::log("resize");
    film.Resize(w, h);
    m_aspectRatio = (float)w/h;

    m_projection = glm::perspective(glm::radians(vFoV), m_aspectRatio, 0.1f, 100.0f);
    CalculatePerspectiveMatrix();
    CalculateRays();
}

void Camera::Initialize()
{
    CalculateViewMatrix();
    CalculatePerspectiveMatrix();
    CalculateBasisVectors();
}

void Camera::OnUpdate(float deltaTime)
{
    if (m_vFoV != vFoV)
    {
        m_vFoV = vFoV;
        CalculatePerspectiveMatrix();
        film.needsReset = true;
    }

    if (m_input && !(ImGui::IsMouseDown(ImGuiMouseButton_Right)))
    {
            film.needsReset = true;
            m_input = false;
    }

    Translate(deltaTime);
    Rotate(deltaTime);
}

glm::vec4 Camera::GetRayDirection(int index)
{
    return m_rayDirections[index];
}

void Camera::CalculateViewMatrix()
{
    m_view = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position+m_forward), glm::vec3(0,0,1));
    m_inverseView = glm::inverse(m_view);
}

void Camera::CalculatePerspectiveMatrix()
{
    m_projection = glm::perspective(glm::radians(m_vFoV), m_aspectRatio, 0.1f, 100.0f);
    m_inverseProjection = glm::inverse(m_projection);
}

void Camera::CalculateBasisVectors()
{
    m_right = m_inverseView * glm::vec4(1,0,0,0);
    m_up = m_inverseView * glm::vec4(0,1,0,0);
}

void Camera::CalculateRays()
{
    rayCount = film.width * film.height;

    int w = film.width;

    m_rayDirections.resize(rayCount);

    for (int j = 0; j < film.height; j++)
    {
        for (int i=0; i < w; i++)
        {
            glm::vec2 rayScreenTarget = glm::vec2(i/(float)w,
                                                  j/(float)film.height);

            rayScreenTarget = rayScreenTarget*2.0f - 1.0f;

            glm::vec4 rayWorldTarget = m_inverseProjection * glm::vec4(rayScreenTarget, 1, 1);
            glm::vec4 rayWorldDirection = m_inverseView * glm::vec4(glm::normalize(glm::vec3(rayWorldTarget)),0);

            m_rayDirections[i+ j*w] = rayWorldDirection;
        }
    }
}

void Camera::Translate(float deltaTime)
{
    if (!(ImGui::IsMouseDown(ImGuiMouseButton_Right)))
    {
        return;
    }

    m_input = true;


    glm::vec4 translation = glm::vec4(0);

    if (ImGui::IsKeyDown(ImGuiKey_W))
    {
        translation += m_forward*m_speed*deltaTime;
    }
    if (ImGui::IsKeyDown(ImGuiKey_S))
    {
        translation += -m_forward*m_speed*deltaTime;
    }
    if (ImGui::IsKeyDown(ImGuiKey_D))
    {
        translation += m_right*m_speed*deltaTime;
    }
    if (ImGui::IsKeyDown(ImGuiKey_A))
    {
        translation += -m_right*m_speed*deltaTime;
    }
    if (ImGui::IsKeyDown(ImGuiKey_E))
    {
        translation += m_up*m_speed*deltaTime;
    }
    if (ImGui::IsKeyDown(ImGuiKey_Q))
    {
        translation += -m_up*m_speed*deltaTime;
    }

    if (glm::dot(translation, translation) > 0.0001)
    {
        m_position += translation;

        CalculateViewMatrix();
        film.needsReset = true;
    }

}

void Camera::Rotate(float deltaTime)
{
    m_lastMousePosition = m_mousePosition;
    m_mousePosition = glm::vec2(ImGui::GetMousePos().x, ImGui::GetMousePos().y);

    if (!(ImGui::IsMouseDown(ImGuiMouseButton_Right)))
    {
        return;
    }

    m_input = true;
    glm::vec2 mouse_delta = m_mousePosition - m_lastMousePosition;

    if (glm::dot(mouse_delta, mouse_delta) > 0.001f)
    {
        glm::mat4 rotate = glm::rotate(glm::mat4(1), -mouse_delta.y*m_sensitivity*deltaTime, glm::vec3(m_right));
        rotate = glm::rotate(rotate, -mouse_delta.x*m_sensitivity*deltaTime, glm::vec3(0,0,1));

        m_forward = rotate*m_forward;

        CalculateViewMatrix();
        CalculateBasisVectors();
        CalculateRays();

        film.needsReset = true;
    }

}


void Camera::DebugWindow()
{
    ImGui::Begin("Camera Debug", NULL, ImGuiWindowFlags_NoCollapse);
    ImGui::Text("vertical fov:  % .2f", m_vFoV);
    ImGui::Text("position:      % .2f, % .2f, % .2f", m_position.x, m_position.y, m_position.z);
    ImGui::Text("forward:       % .2f, % .2f, % .2f", m_forward.x, m_forward.y, m_forward.z);
    ImGui::Text("up:            % .2f, % .2f, % .2f", m_up.x, m_up.y, m_up.z);
    ImGui::Text("right:         % .2f, % .2f, % .2f", m_right.x, m_right.y, m_right.z);
    ImGui::End();
}

void Camera::DrawControls()
{
    ImGui::Text("Samples: %d", film.Samples());
    ImGui::DragFloat("Vertical fov", &vFoV, 0.1f, 1.0f, 100.0f);
    ImGui::DragFloat("Speed", &m_speed, 0.1f);
    ImGui::DragFloat("Sensitivity", &m_sensitivity, 0.1f);
    if (ImGui::Button("Reset Accumulator")) {
        film.needsReset = true;
    }
}
