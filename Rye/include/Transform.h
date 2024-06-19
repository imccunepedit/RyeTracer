#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

class Transform
{
    public:
        Transform()
        {
            CalculateMatrix();
        }
        Transform(glm::vec3 position)
            : position(position)
        {
            CalculateMatrix();
        }
        Transform(float scale)
            : scale(scale)
        {
            CalculateMatrix();
        }
        Transform(glm::vec3 position, float scale)
            : position(position), scale(glm::vec3(scale))
        {
            CalculateMatrix();
        }
        Transform(glm::vec3 position, glm::vec3 scale)
            : position(position), scale(scale)
        {
            CalculateMatrix();
        }
        Transform(glm::vec3 position, float scale, glm::vec3 rotation)
            : position(position), scale(glm::vec3(scale)), rotation(rotation)
        {
            CalculateMatrix();
        }
        Transform(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
            : position(position), scale(scale), rotation(rotation)
        {
            CalculateMatrix();
        }

    private:
        void CalculateMatrix()
        {
            matrix = glm::translate(glm::mat4(1), position);

            matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1,0,0));
            matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0,1,0));
            matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0,0,1));

            matrix = glm::scale(matrix, scale);

            inverseMatrix = glm::inverse(matrix);
        }

    public:
        glm::mat4 matrix = glm::mat4(1);
        glm::mat4 inverseMatrix = glm::mat4(1);
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);
};

#endif /* TRANSFORM_H_ */
