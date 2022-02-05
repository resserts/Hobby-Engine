#pragma once
#include <memory>

#include "vector.h"

class indexVertex {
public:
    unsigned int array, buffer, index;

    indexVertex() {
        glGenVertexArrays(1, &array);
        glGenBuffers(1, &buffer);
        glGenBuffers(1, &index);
    }
};

struct mesh {
public:
	vector position;
	indexVertex vertex;
	float* vertices;
	unsigned int* indexes;
	int verticesSize;
	int indexesSize;

	void freeArrays() {
		free(vertices);
		free(indexes);
	}

	mesh(float meshVertices[], int meshVerticesSize, unsigned int meshIndexes[], int meshIndexesSize) {
		vertices = (float*)malloc(meshVerticesSize);
		indexes = (unsigned int*)malloc(meshIndexesSize);
		verticesSize = meshVerticesSize / sizeof(float);
		indexesSize = meshIndexesSize / sizeof(unsigned int);
		
		if (vertices != NULL && indexes != NULL) {
			for (int i = 0; i < verticesSize; i++) {
				vertices[i] = meshVertices[i];
			}
			for (int i = 0; i < indexesSize; i++) {
				indexes[i] = meshIndexes[i];
			}
		}
		else {
			printf("invalid pointer");
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
	
}

auto moveMesh(mesh mesh, vector move) {
    for (int i = 0; i < mesh.verticesSize / 2; i++) {
		mesh.vertices[i * 2] += move.x;
		mesh.vertices[i * 2 + 1] += move.y;
	}
	mesh.position.x += move.x;
	mesh.position.y += move.y;
	return mesh;
}

void renderMesh(mesh mesh) {
	bindIndexMesh(mesh);

	glDrawElements(GL_TRIANGLES, mesh.indexesSize, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
	glBindVertexArray(0);
}

auto Circle(int res, float radius) {
	float* vertices;	
	vertices = (float*)malloc((res + 1) * 2 * sizeof(float));
	
	if (vertices == NULL) {
		printf("error allocating memory");
		return mesh(0,0,0,0);
	}

	float offset = 360 / res;
	for (int i = 0; i < res; i++) {
		vertices[i * 2] = cos(i * offset * radians) * (radius / 10) * hW;
		vertices[i * 2 + 1] = sin(i * offset * radians) * (radius / 10);
		//printf("%f \n", (i * offset * radians));
	}
	vertices[res * 2] = 0;
	vertices[res * 2 + 1] = 0;

	unsigned int* indices;
	indices = (unsigned int*)malloc((res * 3 * sizeof(unsigned int)));

	if (indices == NULL) {
		printf("error allocating memory");
		return mesh(0,0,0,0);
	}

	for (int j = 0; j < res - 1; j++) {
		indices[j * 3] = j;
		indices[j * 3 + 1] = j + 1;
		indices[j * 3 + 2] = res;
	}
	indices[res * 3 - 3] = res - 1;
	indices[res * 3 - 2] = 0;
	indices[res * 3 - 1] = res;

	mesh circle(vertices, (res + 1) * 2 * sizeof(float), indices, (res * 3 * sizeof(unsigned int)));

	free(vertices);
	free(indices);

	return circle;
}
