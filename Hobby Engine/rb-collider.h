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



void addVelocity(rigidBody rb, vector velocity) {
	rb.velocity.x += velocity.x;
	rb.velocity.y += velocity.y;

}



