#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace Rye {
    class Shader
    {
        public:
            Shader(const char* shaderPath);

            void Load();
            void Use();

            void SetInt(const std::string &name, int &value) const;
            void SetFloat(const std::string &name, float &value) const;
            void SetVec4(const std::string &name, glm::vec4 value) const;
            void SetMat4(const std::string &name, glm::mat4 value) const;
        public:
            uint ID;

        private:
            const char* m_shaderPath;
    };
}

#endif /* SHADER_H_ */
