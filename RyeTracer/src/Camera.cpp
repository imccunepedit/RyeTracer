#include "Camera.h"

#include <iostream>

#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"

using namespace Barley;

void Camera::Resize(const int& w, const int& h)
{
    if (w == film.Width() and h == film.Height())
        return;

    std::cout << "resize" << std::endl;
    film.Resize(w, h);
    m_aspectRatio = (float)w/h;
}

void Camera::OnUpdate(const float& deltaTime)
{
    Translate(deltaTime);
    Rotate(deltaTime);
}

glm::vec4 Camera::GetRayDirection(const int& i, const int& j)
{
    glm::vec2 rayScreenTarget = glm::vec2(i/(float)film.Width(),
                                          j/(float)film.Height()) * 2.0f - 1.0f;

    glm::vec4 rayWorldTarget = m_inverseProjection * glm::vec4(rayScreenTarget, 1, 1);

    return glm::normalize(m_inverseView * rayWorldTarget);

}

void Camera::CalculateMatrices()
{
    m_view = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position+m_forward), glm::vec3(m_up));
    m_projection = glm::perspective(glm::radians(vFoV), m_aspectRatio, 0.1f, 100.0f);

    CalculateInverseMatrices();
}

void Camera::CalculateInverseMatrices()
{
    m_inverseView = glm::inverse(m_view);
    m_inverseProjection = glm::inverse(m_projection);
}

void Camera::CalculateBasisVectors()
{
    m_right = m_view * glm::vec4(1,0,0,0);
    m_up = m_view * glm::vec4(0,0,1,0);
}

void Camera::Translate(const float& deltaTime)
{

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
        film.ResetAccumulator();
        CalculateMatrices();
    }

}

void Camera::Rotate(const float& deltaTime)
{
    m_lastMousePosition = m_mousePosition;

    // glfwGetCursorPos(window, &m_mousePosition.x, &m_mousePosition.y);

    glm::vec2 mouse_delta = m_mousePosition - m_lastMousePosition;

    // if (!(ImGui::IsMouseDown(ImGuiMouseButton_Right)))
    // {
        // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        // return;
    // }

    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // if (glfwRawMouseMotionSupported())
        // glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);


    if (glm::dot(mouse_delta, mouse_delta) > 0.0f)
    {
        m_view = glm::rotate(m_view, mouse_delta.y*m_sensitivity.y*deltaTime, glm::vec3(m_right));
        m_view = glm::rotate(m_view, mouse_delta.x*m_sensitivity.x*deltaTime, glm::vec3(0,0,1));

        film.ResetAccumulator();
        CalculateInverseMatrices();
        m_forward = m_view*glm::vec4(0,1,0,0);
    }

}


void Camera::DebugWindow()
{
    ImGui::Begin("Camera Debug", NULL, ImGuiWindowFlags_NoCollapse);
    // ImGui::Text("Viewport size:   % f, % f", viewport_width, viewport_height);
    ImGui::Text("vertical fov:  % f", vFoV);
    ImGui::End();
}

void Camera::DrawControls()
{
    ImGui::DragFloat("Vertical fov", &vFoV, 0.1f, 1.0f, 100.0f);
    ImGui::DragFloat("Speed", &m_speed, 0.1f);
    ImGui::DragFloat2("Sensitivity", glm::value_ptr(m_sensitivity), 0.1f);
}




// {

//     // generate a seed for our hash generator, should be different for each pixel and shouldn't be any perceptible shift across frames ( only the case if the accumulator is reset every frame and the camera isn't moving)
//     uint32_t seed = x + x * viewport_pixel_width + samples + (out_image->texture) * viewport_pixel_width * viewport_pixel_height;

//     // generate an offset so we cover more of our pixels area with rays
//     glm::vec2 ray_screen_target = glm::vec2((x + raytracing::random_float(seed))/viewport_pixel_width,
//                                             (y + raytracing::random_float(seed))/viewport_pixel_height) * 2.0f - 1.0f;

//     Ray ray;
//     ray.seed = seed;
//     ray.origin = m_position;

//     glm::vec4 ray_world_target = inv_projection * glm::vec4(ray_screen_target, 1, 1);
//     ray.direction = glm::normalize(glm::vec3(inv_view * ray_world_target));


//     // glm::vec3 color = trace_ray(ray, scene, max_depth);
//     accumulation_data[x + y *viewport_pixel_width] += trace_ray(ray, scene, max_depth);

//     glm::vec3 color = accumulation_data[x+y*viewport_pixel_width] / (float)samples;
//     image_data[x + y*viewport_pixel_width] = process_color(color);
// }
