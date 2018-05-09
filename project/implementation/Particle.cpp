#include "Particle.h"


Particle::Particle() {
	timeToLive = 20 + (rand()%20);
	velocity = 1 + 0.1*(rand() % 10);
	size = 1;
	position = vmml::Vector3f(0, 0, 0);
	direction = Particle::newDirection();
	isAlive = false;
};

vmml::Vector3f  Particle::newDirection() {
	// all three values are in the range [-1,1] when they are later normalized
	return vmml::normalize(vmml::Vector3f(
		((rand() % 200) - 100),
		((rand() % 200) - 100), 
		((rand() % 200) - 100)));
}
