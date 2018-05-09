#ifndef FLARE_MANAGER_H
#define FLARE_MANAGER_H

#include "Flare.h"

class FlareManager {

public:
	int numOfFlares;
	Flare** flareArray;
	float spacing;
	float transparency;
	
	void Start();
	void Update(vmml::Vector2f sunPosition);
	void Destroy();
};



#endif /* defined(FLARE_MANAGER_H) */