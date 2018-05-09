#ifndef STICK_TO_FRONT_SCRIPT_CPP
#define STICK_TO_FRONT_SCRIPT_CPP

#include "Behaviour.h"
#include "Core.h"
#include "TheRenderer.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CameraMovementScript.cpp"
#include "GameObject.h"

class StickToFrontScript : public Behaviour {
public:
	CameraPtr cam;
    GameObject *Cam;
    float pitchAngle;
    float rollAngle;
    vmml::Vector3f camForwardDirection;
    vmml::Vector3f camRightDirection;
    vmml::Vector3f camUpDirection;
    
	void Start(){
		cam = TheRenderer::Instance()->renderer->getObjects()->getCamera("camera");
        Cam = SceneManager::getCurrentScene()->getObjectByName("Camera");
	}

	void Update(){
        // Camera axis
        camForwardDirection = cam->getForward();
        camRightDirection = cam->getRight();
        camUpDirection = cam->getUp();
        
		transform->setPosition(-cam->getPosition() - (camForwardDirection * -10 + camUpDirection * 4));
		transform->setRotation(cam->getInverseRotation());
        
        // Make the ship move accordingly to the pitch and roll of the camera
        pitchAngle = Cam->getComponent<CameraMovementScript>()->pitch;
        rollAngle = Cam->getComponent<CameraMovementScript>()->roll;

        vmml::Matrix4f pitchRotation = vmml::create_rotation(pitchAngle/2, -camForwardDirection);
        vmml::Matrix4f rollRotation = vmml::create_rotation(rollAngle/2, camRightDirection);
        vmml::Matrix4f yawRotation = vmml::create_rotation(pitchAngle/2, camUpDirection);
        
        // Apply the rotations to the ship
        transform->setRotation(yawRotation * rollRotation * pitchRotation * transform->getRotation());
    }
};

#endif /* defined(STICK_TO_FRONT_SCRIPT_CPP) */
