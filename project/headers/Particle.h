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
	vmml::Vector3f direction;
	bool isAlive;

	Particle();
	static vmml::Vector3f newDirection();
};

#endif /* defined(PARTICLE_H) */
