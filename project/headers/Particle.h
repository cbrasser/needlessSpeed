#ifndef PARTICLE_H
#define PARTICLE_H

#include <vmmlib/util.hpp>

class Particle{
public:
	int timeToLive;
	int velocity;
	float size;
    float randomScale;
	vmml::Vector3f position;
	vmml::Vector3f tempPosition;
	vmml::Vector3f oldPosition;
	vmml::Vector3f direction;
	bool isAlive;
	double carX;
	double carY;

	Particle();
	static vmml::Vector3f newDirection();
	void reset();
	float Particle::calculateVelocity(vmml::Vector3f oldPosition, vmml::Vector3f tempPosition);
};

#endif /* defined(PARTICLE_H) */
