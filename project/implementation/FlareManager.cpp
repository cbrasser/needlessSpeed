#include "FlareManager.h"

void FlareManager::Start() {
	numOfFlares = 7; // Specify amount of flares here
	flareArray = new Flare*[numOfFlares];
	transparency = 1.0;

	for (int i = 0; i < numOfFlares; i++) {
		float scale = 1.0;
		flareArray[i] = new Flare(scale);
	}
}

void FlareManager::Update(vmml::Vector2f sunPosition){
	float spacing = 0.2;
	vmml::Vector2f centerOfScreen = vmml::Vector2f(0,0);
	vmml::Vector2f sunToCenter = centerOfScreen - sunPosition;
	float sunToCenterLength = sunToCenter.length();
	transparency = -sunToCenterLength / 3 + 1;
	if (transparency < 0) {
		transparency = 0;
	}


	for (int i = 0; i < numOfFlares; i++) {
		flareArray[i]->position = sunPosition + spacing * i * sunToCenter;
		flareArray[i]->scale = (std::log(-sunToCenterLength + 2) / 2 + 0.8 + i*0.2)/2; //logarithmic function that scales every flare based on distance from center, the flares have an increasing size starting from the sun position;
		if (flareArray[i]->scale <= 0) {
			flareArray[i]->scale = 0;
		}
		if (i == 1) {
			flareArray[i]->scale *= 5;
		}	
	}
}

void FlareManager::Destroy() {
	delete[] flareArray;
}
