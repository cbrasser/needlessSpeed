#include "Particle.h"


Particle::Particle() {
	timeToLive = 20 + (rand() % 40);
	velocity = 1; 
	position = vmml::Vector3f(0, 0, 0);
	direction = Particle::newDirection();
	isAlive = true;
	randomScale = 0.01f * (rand() % 100);
	size = 0.005f;
};

vmml::Vector3f  Particle::newDirection() {
	// all three values are in the range [-1,1] when they are later normalized
	return vmml::normalize(vmml::Vector3f(
		((rand() % 200) - 100),
		((rand() % 200) - 100), 
		((rand() % 200) - 100)));
}

void Particle::reset() { //Resets the values to their original
	timeToLive = 20 + (rand() % 40);
	velocity = 1;
	position = vmml::Vector3f(0, 0, 0);
	direction = Particle::newDirection();
	isAlive = true;
	randomScale = 0.01f * (rand() % 100);
	size = 0.005f;
}
