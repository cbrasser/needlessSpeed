#ifndef CAMERA_FOLLOW_SCRIPT_CPP
#define CAMERA_FOLLOW_SCRIPT_CPP

#include "Core.h"
#include "TheRenderer.h"
#include "Behaviour.h"
#include "TheTime.h"

class CameraFollowScript : public Behaviour {
public:
	float speed = 10.0f;
	Transform* ship;
	CameraPtr cam;

	void Start() {
		cam = TheRenderer::Instance()->renderer->getObjects()->getCamera("camera");
	}

	void LateUpdate() {

		vmml::Vector3f target = (ship->getPosition() + ship->forward() * -10);
		cam->setPosition(target * -1);
//		cam->setPosition(lerp(cam->getPosition(), target, TheTime::deltaTime * speed));

		vmml::Vector3f rot = vmml::Vector3f(ship->getRotation().x() * -1, ship->getRotation().y() * -1, ship->getRotation().z());
		cam->setRotation(rot);

		// TODO: convert the lookat matrix to rotation and appy the rotation to the camera
		/*
		vmml::Matrix4f mat = Camera::lookAt(TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->getPosition(), ship->position, ship->up());
		vmml::Vector3f rot = 0;
		TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->setRotation(rot);
		*/

		//std::cout << "Ship: " << ship->position << " " << ship->rotation << std::endl;
		//std::cout << "Camera: " << cam->getPosition() << " " << cam->_rotationAxes << std::endl;
	}

	vmml::Vector3f lerp(vmml::Vector3f start, vmml::Vector3f end, float percent) {
		return (start + percent*(end - start));
	}
};

#endif /* defined(CAMERA_FOLLOW_SCRIPT_CPP) */