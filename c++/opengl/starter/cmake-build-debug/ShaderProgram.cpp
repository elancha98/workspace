//
// Created by ernesto on 13/04/18.
//

#include <iostream>
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::string &vertexShader, const std::string &fragmentShader) {
    id = glCreateProgram();
    vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(id, vs);
    glAttachShader(id, fs);

    glLinkProgram(id);
    glValidateProgram(id);

    glDeleteShader(vs);
    glDeleteShader(fs);
}

GLuint ShaderProgram::compileShader(GLenum type, const std::string &src) {
    GLuint sid = glCreateShader(type);
    const char* source = src.c_str();
    glShaderSource(sid, 1, &source, nullptr);
    glCompileShader(sid);

    GLint result;
    glGetShaderiv(sid, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        GLint lenght;
        glGetShaderiv(sid, GL_INFO_LOG_LENGTH, &lenght);
        char err[lenght];
        glGetShaderInfoLog(sid, lenght, &lenght, err);
        std::cerr << "Failed to compile shader" << std::endl;
        std::cerr << err << std::endl;

        glDeleteShader(sid);
        return 0;
    }

    return sid;
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(id);
}
