#ifndef SHADER_H_
#define SHADER_H_

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


namespace Rye {
    class Shader
    {
        public:
            Shader(const char* shaderPath);

            void Use();

            uint ID;
    };
}

#endif /* SHADER_H_ */
