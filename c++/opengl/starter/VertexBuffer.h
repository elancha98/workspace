//
// Created by ernesto on 13/04/18.
//

#ifndef STARTER_VERTEXBUFFER_H
#define STARTER_VERTEXBUFFER_H


class VertexBuffer {
private:
    GLuint id;

public:
    VertexBuffer();
    ~VertexBuffer();

    void setData(float vertices[], int l);
    // TODO: set data type

    void bindBuffer() {glBindBuffer(GL_ARRAY_BUFFER, id);};
    void unbindBuffer() {glBindBuffer(GL_ARRAY_BUFFER, 0);};
};


#endif //STARTER_VERTEXBUFFER_H
