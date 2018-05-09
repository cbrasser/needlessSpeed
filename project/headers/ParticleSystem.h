#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "Particle.h"
#include "TheTime.h"


class ParticleSystem {

public:
	int numOfParticles;
	Particle** particleArray;
	bool isDone;
	
	void updateSize(int index);
	void activate();
	void Start();
	void Update();
	void Destroy();
};



#endif /* defined(PARTICLE_SYSTEM_H) */