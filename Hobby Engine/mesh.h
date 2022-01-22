#pragma once
#include <memory>

class indexVertex {
public:
    unsigned int array, buffer, index;

    indexVertex() {
        glGenVertexArrays(1, &array);
        glGenBuffers(1, &buffer);
        glGenBuffers(1, &index);
    }
};

struct vector {
	float x;
	float y;

	vector(float X, float Y) {
		x = X;
		y = Y;
	}
};

struct mesh {
public:
	indexVertex vertex;
	float* vertices;
	unsigned int* indexes;
	int verticesSize;
	int indexesSize;

	void freeArrays() {
		free(vertices);
		free(indexes);
	}

	mesh(indexVertex meshVertex, float meshVertices[], int meshVerticesSize, unsigned int meshIndexes[], int meshIndexesSize) {
		vertex = vertex;
		vertices = (float*)malloc(meshVerticesSize);
		indexes = (unsigned int*)malloc(meshIndexesSize);
		verticesSize = meshVerticesSize / sizeof(float);
		indexesSize = meshIndexesSize / sizeof(unsigned int);
		
		for (int i = 0; i < verticesSize; i++) {
			vertices[i] = meshVertices[i];
		}
		for (int i = 0; i < indexesSize; i++) {
			indexes[i] = meshIndexes[i];
		}
	}
	~mesh() {
	}

};

void bindIndexMesh(mesh mesh) {

    glBindVertexArray(mesh.vertex.array);

    glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex.buffer);
    glBufferData(GL_ARRAY_BUFFER, mesh.verticesSize * sizeof(float), &mesh.vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vertex.index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indexesSize * sizeof(unsigned int), &mesh.indexes[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void moveMesh(mesh mesh, vector move) {
    for (int i = 0; i < mesh.verticesSize / 2; i++) {
		mesh.vertices[i * 2] += move.x;
		mesh.vertices[i * 2 + 1] += move.y;
	}

	glBindBuffer(GL_ARRAY_BUFFER, mesh.vertex.buffer);
	glBufferData(GL_ARRAY_BUFFER, mesh.verticesSize * sizeof(float), &mesh.vertices[0], GL_STATIC_DRAW);

	glBindVertexArray(mesh.vertex.array);
}
