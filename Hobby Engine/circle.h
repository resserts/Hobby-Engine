#pragma once

#include <math.h>
#include "variables.h"
#include "vector.h"
#include "rb-collider.h"
#include "mesh.h"


struct circleCollider {
public:
	float radius;
	vector position;

	circleCollider(vector position, float radius) {
		this->position.x = position.x;
		this->position.y = position.y;
		this->radius = radius / 10.0f;
	}
};

bool circlesColliding(circleCollider circle1, circleCollider circle2) {
	float distance = sqrt(pow(circle1.position.x - circle2.position.x, 2) + pow(circle1.position.y - circle2.position.y, 2));
	float colDist = abs(circle1.radius + circle2.radius);
	//printf("%f\n", distance);
	if (distance <= colDist) {
		return true;
	}
	else {
		return false;
	}
}

void circlesCollision(rigidBody *obj1, rigidBody *obj2) {
	float angle = atan2(obj1->position.x - obj2->position.x, obj1->position.y - obj2->position.y);
	float xChange = sin(angle);
	float yChange = cos(angle);
	//printf("%f", yChange);

	float yRatio = yChange / (abs(yChange) + abs(xChange));
	float xRatio = xChange / (abs(yChange) + abs(xChange));
	float force = (abs(obj2->velocity.x) + abs(obj2->velocity.y));
	//printf("%f", yRatio + xRatio);

	vector obj1Velocity((force * xRatio),(force * yRatio));

	angle = atan2(obj2->position.x - obj1->position.x, obj2->position.y - obj1->position.y);
	xChange = sin(angle);
	yChange = cos(angle);
	//printf("%f", yChange);

	yRatio = yChange / (abs(yChange) + abs(xChange));
	xRatio = xChange / (abs(yChange) + abs(xChange));
	force = (abs(obj1->velocity.x) + abs(obj1->velocity.y));
	//printf("%f", yRatio + xRatio);

	vector obj2Velocity((force * xRatio), (force * yRatio));

	obj1->velocity = obj1Velocity;
	obj2->velocity = obj2Velocity;
}

void circleInBoxCol(circleCollider circleCol, rigidBody* circleRb) {
	if (abs(circleCol.position.x) + circleCol.radius >= 1.0f && circleCol.position.x * circleRb->velocity.x > 0) {
		circleRb->velocity.x *= -1.0f;
	}
	if (abs(circleCol.position.y) + circleCol.radius >= 1.0f && circleCol.position.y * circleRb->velocity.y > 0) {
		circleRb->velocity.y *= -1.0f;
	}
}

auto CircleMesh(int res, float radius) {
	float* vertices;	
	vertices = (float*)malloc((res + 1) * 2 * sizeof(float));
	
	if (vertices == NULL) {
		printf("error allocating memory");
		mesh* error = new mesh(0, 0, 0, 0);
		return error;
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
		mesh* error = new mesh(0, 0, 0, 0);
		return error;
	}

	for (int j = 0; j < res - 1; j++) {
		indices[j * 3] = j;
		indices[j * 3 + 1] = j + 1;
		indices[j * 3 + 2] = res;
	}
	indices[res * 3 - 3] = res - 1;
	indices[res * 3 - 2] = 0;
	indices[res * 3 - 1] = res;

	mesh* circle = new mesh(vertices, (res + 1) * 2 * sizeof(float), indices, (res * 3 * sizeof(unsigned int)));

	free(vertices);
	free(indices);

	return circle;
}

struct circle {
public:
	circleCollider* collider;
	mesh* mesh;
	rigidBody* rb;
	circle(float radius = 1, vector position = vector(0, 0), int res = 36, vector velocity = vector(0, 0)) {
		collider = new circleCollider(position, radius);
		mesh = CircleMesh(res, radius);
		rb = new rigidBody(position, velocity);
		
		moveMesh(mesh, position);
	}
	~circle() {
		mesh->freeArrays();
		delete mesh;
		delete collider;
		delete rb;
	}

	void refresh() {

		rb->refresh();
		vector meshMove = vector(rb->position.x - mesh->position.x + rb->velocity.x, rb->position.y - mesh->position.y + rb->velocity.y);
		moveMesh(mesh, meshMove);
		collider->position = rb->position;
	}
};
