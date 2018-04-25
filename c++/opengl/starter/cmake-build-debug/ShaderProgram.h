//
// Created by ernesto on 13/04/18.
//

#ifndef STARTER_SHADERPROGRAM_H
#define STARTER_SHADERPROGRAM_H


#include <string>
#include <GL/glew.h>

class ShaderProgram {

public:
    ShaderProgram(const std::string &vertexShader, const std::string &fragmentShader);
    ~ShaderProgram();

    void use() {glUseProgram(id);};

private:
    GLuint id;
    GLuint vs, fs;

    static GLuint compileShader(GLenum type, const std::string &src);
};


#endif //STARTER_SHADERPROGRAM_H
