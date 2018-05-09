#ifndef CAMERA_WRAPPER_CPP
#define CAMERA_WRAPPER_CPP

#include "Core.h"
#include "TheRenderer.h"
#include "Behaviour.h"

class CameraWrapper : public Behaviour {
public:
	CameraPtr cam;

	void Start() {
		cam = TheRenderer::Instance()->renderer->getObjects()->getCamera("camera");
	}

	void Update() {
		transform->setPosition(cam->getPosition() * -1);
		//transform->setRotation(cam->_rotationAxes * -1);
	}
};

#endif /* defined(CAMERA_WRAPPER_CPP) */
