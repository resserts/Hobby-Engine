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

void addVelocity(rigidBody rb, vector velocity) {
	rb.velocity.x += velocity.x;
	rb.velocity.y += velocity.y;

}

