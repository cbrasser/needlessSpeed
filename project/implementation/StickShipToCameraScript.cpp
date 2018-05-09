#ifndef STICK_SHIP_TO_CAMERA_CPP
#define STICK_SHIP_TO_CAMERA_CPP

#include "Core.h"
#include "TheRenderer.h"
#include "Behaviour.h"
#include "TheTime.h"

class StickShipToCameraScript : public Behaviour {
public:
	Transform* ship;
	CameraPtr cam;
	vmml::Vector3f _rotationAxes;

	void Start() {
		cam = TheRenderer::Instance()->renderer->getObjects()->getCamera("camera");
	}

	void Update() {



		ship->setPosition( -(cam->getPosition() + cam->getForward() * -10));
		//ship->setRotation(-(cam->_rotationAxes));
	}


	vmml::Matrix4f getRotation()
	{
		return  vmml::create_rotation(_rotationAxes[2], vmml::Vector3f::UNIT_Z) * vmml::create_rotation(_rotationAxes[0], vmml::Vector3f::UNIT_X) * vmml::create_rotation(_rotationAxes[1], vmml::Vector3f::UNIT_Y);
	}

	vmml::Matrix4f getInverseRotation()
	{
		vmml::Matrix4f rotInv = vmml::Matrix4f::IDENTITY;
		getRotation().transpose_to(rotInv);
		return rotInv;
	}
};

#endif /* defined(STICK_SHIP_TO_CAMERA_CPP) */
