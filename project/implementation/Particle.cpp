#include "Particle.h"
#include "Scene.h"
#include "SceneManager.h"


Particle::Particle() {
	timeToLive = 20 + (rand() % 40); 
	position = vmml::Vector3f(0, 1, 0); //set first and last value to match car spawn point
	direction = Particle::newDirection();
	isAlive = true;
	randomScale = 0.025f * (rand() % 100);
	size = 0.0f;
	velocity = 0.f;
};

vmml::Vector3f  Particle::newDirection() {
	// all three values are in the range [-1,1] when they are later normalized
	return vmml::normalize(vmml::Vector3f(
		((rand() % 200) - 100),
		((rand() % 200) - 100), 
		((rand() % 200) - 100)));
}

void Particle::reset() { //Resets the values to their original
	tempPosition;
	timeToLive = 20 + (rand() % 40);
	velocity = 1;
	oldPosition = tempPosition;
	tempPosition = SceneManager::getCurrentScene()->getObjectByName("Car")->transform->getPosition();
	float velocity = calculateVelocity(oldPosition, tempPosition);
	double carX = tempPosition[0];
	double carY = tempPosition[2];
	position = vmml::Vector3f(carX, 0.5, carY);
	direction = Particle::newDirection();
	isAlive = true;
	randomScale = 0.025f * (rand() % 100);
	if (velocity >= 20.0f) {
		velocity = 20.0f;
	}
	size = 0.08f * velocity;
}

float Particle::calculateVelocity(vmml::Vector3f oldPosition, vmml::Vector3f tempPosition) {
	
	vmml::Vector3f positionDifference = tempPosition - oldPosition;
	float velocity = 0.0;
	for (int i = 0; i < positionDifference.size(); i++) {
		velocity += positionDifference[i] * positionDifference[i];
	}
	velocity = sqrt(velocity);

	return velocity;
}

