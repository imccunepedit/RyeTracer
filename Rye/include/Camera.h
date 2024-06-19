#ifndef CAMERA_H_
#define CAMERA_H_

#include <cstdint>
#include <vector>

#include <GLFW/glfw3.h>

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "Film.h"


namespace Rye {
    class Camera {
        public:
            void Initialize();
            void Resize(const int& w, const int& h);

            glm::vec4 GetRayOrigin() { return m_position; }
            glm::vec4 GetRayDirection(const int& index);

            void OnUpdate(const float& deltaTime);
            void DebugWindow();
            void DrawControls();

            bool Inputting() { return m_input; }

        private:
            void CalculateBasisVectors();
            void CalculateViewMatrix();
            void CalculatePerspectiveMatrix();
            void CalculateRays();

            void Translate(const float& deltaTime);
            void Rotate(const float& deltaTime);

        public:
            Film film;
            float vFoV = 45;
            int rayCount = 1;

        private:
            float m_vFoV = 0;
            float m_aspectRatio = 1;

            std::vector<glm::vec4> m_rayDirections;

            glm::vec4 m_position = glm::vec4(0,-10,5,1);

            glm::mat4 m_projection = glm::mat4(1);
            glm::mat4 m_inverseProjection = glm::mat4(1);
            glm::mat4 m_view = glm::mat4(1);
            glm::mat4 m_inverseView = glm::mat4(1);

            glm::vec4 m_forward = glm::vec4(0,1,0,0);
            glm::vec4 m_up = glm::vec4(0,0,1,0);
            glm::vec4 m_right = glm::vec4(1,0,0,0);

            bool m_input = false;

            float m_speed = 4;
            float m_sensitivity = 0.1f;

            glm::vec2 m_mousePosition;
            glm::vec2 m_lastMousePosition;

    };
}


#endif // CAMERA_H_
