#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>


class indexVertex {
public:
    unsigned int array, buffer, index;

    indexVertex() {
        glGenVertexArrays(1, &array);
        glGenBuffers(1, &buffer);
        glGenBuffers(1, &index);
    }
};

void bindIndexMesh(indexVertex vertex, float points[],int pSize, unsigned int index[], int iSize) {

    glBindVertexArray(vertex.array);

    glBindBuffer(GL_ARRAY_BUFFER, vertex.buffer);
    glBufferData(GL_ARRAY_BUFFER, pSize, &points[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex.index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, &index[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
