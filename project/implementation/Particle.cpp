#include "Particle.h"
#include "Scene.h"
#include "SceneManager.h"


Particle::Particle() {
	timeToLive = 20 + (rand() % 40);
	velocity = 1; 
	position = vmml::Vector3f(0, 1, 0); //set first and last value to match car spawn point
	direction = Particle::newDirection();
	isAlive = true;
	randomScale = 0.025f * (rand() % 100);
	size = 0.04f;
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
	position = SceneManager::getCurrentScene()->getObjectByName("Car")->transform->getPosition();
	double carX = position[0];
	double carY = position[2];
	position = vmml::Vector3f(carX, 1, carY);
	direction = Particle::newDirection();
	isAlive = true;
	randomScale = 0.025f * (rand() % 100);
	size = 0.04f;
}
