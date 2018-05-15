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
		float desiredDelta = 12.0f;
		double deltaCameraY = 1.3;
		double deltaCameraX = 0.0;
		double cameraUpward = 0.0;
		double cameraSideward = 0.0;
		double cameraUpward2 = 0.0;
		double cameraSideward2 = 0.0;


		double _cameraSpeed = 5.0f;

		vmml::Vector3f camPos =TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->getPosition();
		vmml::Matrix4f camRot =TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->getRotation();
		vmml::Vector3f position = SceneManager::getCurrentScene()->getObjectByName("Car")->transform->getPosition();
		vmml::Matrix4f carRot = SceneManager::getCurrentScene()->getObjectByName("Car")->transform->getRotation();

		std::cout<<"\nCar Rotation: "<<carRot;


		double camX = camPos[0];
		double camZ = camPos[1];
		double camY = camPos[2];
		double carX = - position[0];
		double carY = - position[2];

		cameraSideward =  (camX-carX);	
		cameraUpward = camY - carY;// - desiredDelta;

		cameraSideward2 = desiredDelta*carRot[0][2];
		cameraUpward2 = desiredDelta*carRot[0][0];
		std::cout << "\n";
		std::cout << "\n";
		std::cout <<"\ncamera rotation: "<< camRot;
		std::cout <<"\ncar rotation : "<< carRot;


		double deltaRotation = acos(carRot[0][2]) - acos(camRot[0][2]);
		std::cout <<"\ncar rotation angle: "<<acos(carRot[0][2]);
		std::cout <<"\ncamera rotation angle: "<<acos(camRot[0][2]);
		std::cout <<"\ndeltaRotation: "<<deltaRotation;

		//// Update camera ////
		if (TheRenderer::Instance()->renderer->isRunning()) {
            if(cameraSideward>=1.0f || cameraSideward <= 1.0f){
            		//Lerp towards center of the car in carX
					TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->moveCameraSideward(cameraSideward*_cameraSpeed*TheTime::deltaTime);

					//rotate around the car dependend on its rotation and how far we want to be away from the car, describes a circle around the car together with the same line in y below
					TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->moveCameraSideward(cameraSideward2*_cameraSpeed*TheTime::deltaTime);

					//rotate so that upward movement is parallel to the plane
					TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->rotateCamera(-cameraAngle+90*3.1415/180,0.f,0.f);

					//Lerp towards center of the car in Y
					TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->moveCameraUpward(cameraUpward*_cameraSpeed*TheTime::deltaTime);

					//rotate around car in y
					TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->moveCameraUpward(cameraUpward2*_cameraSpeed*TheTime::deltaTime);

					//Rotate back to game view
					TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->rotateCamera(-90*3.1415/180+cameraAngle,0.f,0.f);

					TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->rotateCamera(0.f,deltaRotation,0.f);
			}
		}
	}
};

#endif /* defined(FREE_CAMERA_SCRIPT_H) */
