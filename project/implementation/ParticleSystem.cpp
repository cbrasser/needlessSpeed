#include "ParticleSystem.h"

void ParticleSystem::Start() {
	numOfParticles = 10; // Specify amount of particles here
	particleArray = new Particle*[numOfParticles];
	bool isDone = true;
	
	for (int i = 0; i < numOfParticles; i++) {
		particleArray[i] = new Particle();
	}
}

void ParticleSystem::updateSize(int index) { // logarithmic function that calculates
	particleArray[index]->size = particleArray[index]->randomScale*(log10f(-(20 - particleArray[index]->timeToLive)/2 + 400.1) + 1)/5;
}

void ParticleSystem::Update() {
	bool allDead = true;
	for (int i = 0; i < numOfParticles; i++) {

		if (particleArray[i]->timeToLive <= 0) {
			particleArray[i]->reset();

		}
		else {	// if the particle is still alive ( timeToLive > 0 ) then update its position and timeToLive.
			allDead = false;
			updateSize(i);
			particleArray[i]->timeToLive -= 1;
			particleArray[i]->position += particleArray[i]->direction * particleArray[i]->velocity * TheTime::deltaTime;
		}
	} 
	if (allDead) {
		isDone = true;
	}
}

void ParticleSystem::Destroy() {
	delete[] particleArray;
}
