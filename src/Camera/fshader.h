#ifndef FSHADER_H
#define FSHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class fShader{
public:
    // program ID
    unsigned int ID;

    // constructor reads and builds the shader
    fShader(const char* vertexPath, const char* fragmentPath);

    // use or activate the shader
    void use();

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 m) const;
};

#endif