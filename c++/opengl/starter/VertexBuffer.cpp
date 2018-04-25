//
// Created by ernesto on 13/04/18.
//

#include <GL/glew.h>
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &id);
}

void VertexBuffer::setData(float vertices[], int l) {
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * l, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &id);
}
