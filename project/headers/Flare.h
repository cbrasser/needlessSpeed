#ifndef FLARE_H
#define FLARE_H

#include <vmmlib/util.hpp>

class Flare{
public:
	float scale;
	vmml::Vector2f position;

	Flare(float);
};

#endif /* defined(FLARE_H) */