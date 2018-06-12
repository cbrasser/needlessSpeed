
#ifndef ROTATION_SCRIPT_H
#define ROTATION_SCRIPT_H

#include "Behaviour.h"
#include "TheTime.h"

class RotationScript : public Behaviour {
public:
	float speed;
	vmml::Vector3f rotationAxis;

	void Start() {
		speed = (rand() % 20 + 1) / 10.0f;
		rotationAxis = vmml::Vector3f((rand() % 10) / 10.0f, (rand() % 10) / 10.0f, (rand() % 10) / 10.0f);
	}
	
	void Update() {
		vmml::Matrix4f rotMat = vmml::create_rotation((float)(speed * TheTime::deltaTime), vmml::Vector3f::UNIT_Z);
		transform->setRotation(transform->getRotation() * rotMat);
	}
};

#endif /* defined(ROTATION_SCRIPT_H) */