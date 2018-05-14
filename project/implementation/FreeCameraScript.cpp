#ifndef FREE_CAMERA_SCRIPT_H
#define FREE_CAMERA_SCRIPT_H

#include "Core.h"
#include "TheRenderer.h"
#include "Behaviour.h"
#include "TheTime.h"
#include "Scene.h"
#include "SceneManager.h"

class FreeCameraScript : public Behaviour {
public:
	float speed = 10.0f;
	double _mouseX, _mouseY;
	GLint _lastStateSpaceKey = bRenderer::INPUT_UNDEFINED;
    double pitch;
    double newPitch;
    double roll;
    double newRoll;
    vmml::Vector3f cameraForwardDirection;
    

	void Update() {
		//// Adjust aspect ratio ////
		TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->setAspectRatio(TheRenderer::Instance()->renderer->getView()->getAspectRatio());


		float cameraAngle = 0.5f;
		float desiredDelta = 8.0f;
		double deltaCameraY = 1.3;
		double deltaCameraX = 0.0;
		double cameraUpward = 0.0;
		double cameraSideward = 0.0;

		double _cameraSpeed = 5.0f;

		vmml::Vector3f camPos =TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->getPosition();
		vmml::Vector3f position = SceneManager::getCurrentScene()->getObjectByName("Car")->transform->getPosition();

		double camX = camPos[0];
		double camY = camPos[2];
		double carX = - position[0];
		double carY = - position[2];

		cameraSideward =  (camX-carX);
		cameraUpward = camY - carY - desiredDelta;

		/*std::cout<<"\nCar Position: "<<position;
		std::cout<<"\nCamera Position: "<<camPos;
		std::cout<<"\ncameraSideward: "<<cameraSideward;
		std::cout<<"\ncameraUpward: "<<cameraUpward;*/

		//// Update camera ////
		if (TheRenderer::Instance()->renderer->isRunning()) {
            if(cameraSideward>=1.0f || cameraSideward <= 1.0f){
					TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->moveCameraSideward(cameraSideward*_cameraSpeed*TheTime::deltaTime);
					TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->rotateCamera(-cameraAngle+90*3.1415/180,0.f,0.f);
					TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->moveCameraUpward(cameraUpward*_cameraSpeed*TheTime::deltaTime);
					vmml::Matrix4f camRot = TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->getRotation();
					TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->rotateCamera(-90*3.1415/180+cameraAngle,0.f,0.f);
			}
		}
	}
};

#endif /* defined(FREE_CAMERA_SCRIPT_H) */
