#pragma once

#include "vector.h"

struct rigidBody {
public:
	vector position;
	vector velocity;

	void refresh() {
		position.x += velocity.x;
		position.y += velocity.y;
	}
};

struct meshCollider {
public:
	vector position;
	float* vertices;
	unsigned int* indexes;
	int verticesSize;
	int indexesSize;

	void freeArrays() {
		free(vertices);
		free(indexes);
	}

	meshCollider(float meshVertices[], int meshVerticesSize, unsigned int meshIndexes[], int meshIndexesSize) {
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
};

void addVelocity(rigidBody rb, vector velocity) {
	rb.velocity.x += velocity.x;
	rb.velocity.y += velocity.y;

}



