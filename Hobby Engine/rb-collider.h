#pragma once

#include <math.h>
#include "vector.h"

struct rigidBody {
public:
	vector position;
	vector velocity;
	
	rigidBody(vector position = vector(0, 0), vector velocity = vector(0, 0)) {
		this->position = position;
		this->velocity = velocity;
	}

	void refresh() {
		position.x += velocity.x;
		position.y += velocity.y;
	}
};

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

void addVelocity(rigidBody rb, vector velocity) {
	rb.velocity.x += velocity.x;
	rb.velocity.y += velocity.y;

}

bool circleColliding(circleCollider circle1, circleCollider circle2) {
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

auto collision(rigidBody obj1, rigidBody obj2) {
	float angle = atan2(obj1.position.x - obj2.position.x, obj1.position.y - obj2.position.y);
	float xChange = sin(angle);
	float yChange = cos(angle);
	printf("%f", yChange);

	float yRatio = yChange / (abs(yChange) + abs(xChange));
	float xRatio = xChange / (abs(yChange) + abs(xChange));
	float force = (abs(obj1.velocity.x) + abs(obj1.velocity.y));
	//printf("%f", yRatio + xRatio);

	vector velocity(force * xRatio, force * yRatio);
	obj1.velocity = velocity;
	return obj1;
}
