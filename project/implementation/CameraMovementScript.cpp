#ifndef CAMERA_MOVEMENT_SCRIPT_H
#define CAMERA_MOVEMENT_SCRIPT_H

#include "Core.h"
#include "TheRenderer.h"
#include "Behaviour.h"
#include "TheTime.h"
#include "Scene.h"
#include "SceneManager.h"

class CameraMovementScript : public Behaviour {
public:
    float speed = 3.5f;
    float boost = 3.8f;
    double pitch;
    double newPitch;
    double roll;
    double newRoll;
    vmml::Vector3f cameraForwardDirection;
    vmml::Vector3f newPos;
    // Fov
    GLfloat baseFov = 90;
    GLfloat targetFov = 120;
    GLfloat fov = baseFov;
    float boostLerpPercent = 0.9;
    float brakeLerpPercent = 0.4;
    bool isPressed;
    // Boost
    float scalingFactor = 1;
	Transform* booster;

	void Start() {
		booster = SceneManager::getCurrentScene()->getObjectByName("Boost")->transform;
	}
    
    void Update() {
        
        //// Adjust aspect ratio ////
        TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->setAspectRatio(TheRenderer::Instance()->renderer->getView()->getAspectRatio());
        
        /// Update camera ///
        double deltaCameraY = 0.0;
        double deltaCameraX = 0.0;
        
        cameraForwardDirection = TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->getForward();
        
        /* iOS */
        if (TheRenderer::Instance()->renderer->isRunning()) {
            
            newPos = TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->getPosition() - (speed*cameraForwardDirection);

            // Control movement using touch
            TouchMap touchMap = TheRenderer::Instance()->renderer->getInput()->getTouches();
            for (auto t = touchMap.begin(); t != touchMap.end(); ++t)
            {
                Touch touch = t->second;
                // If touch is in left half of the view: move forward
                if (touch.startPositionX < TheRenderer::Instance()->renderer->getView()->getWidth() / 2) {
                    // Compute new position
                    newPos = TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->getPosition() - (speed*boost*cameraForwardDirection);
                    // The user is touching
                    isPressed = true;
                }
                // If touch is in right half of the view: shoot (implemented in LaserManager.cpp)
            }
            
            // When boosting enlarge fov (with lerpPercent = 0.9, the target fov - 120 - is reached in 33 frames)
            if (isPressed && fov < targetFov) {
                fov = fov + 1*boostLerpPercent;
                
                // Boost
                scalingFactor += 0.1f * boostLerpPercent;
                if (scalingFactor >= 2.0f) {
                    scalingFactor = 2.0f;
                }
                booster->setScale(vmml::Vector3f(1.0f, 1.0f, scalingFactor));

            }
            // When braking slowly reduce fov
            if (!isPressed && fov > baseFov) {
                fov = fov - 1*brakeLerpPercent;
                
                // Boost
                scalingFactor -= 0.1f * brakeLerpPercent;
                if (scalingFactor <= 1.0f) {
                    scalingFactor = 1.0f;
                }
                booster->setScale(vmml::Vector3f(1.0f, 1.0f, scalingFactor));

            }
            
            // Control movement using gyroscope (look around)
            // left vs right (with ipad in landscape mode)
            pitch = TheRenderer::Instance()->renderer->getInput()->getGyroscopePitch();
            
            // up vs down
            // adjust the initial roll so that the "zero" is set to 1 rad instead of 0 (completely horizontal)
            roll = TheRenderer::Instance()->renderer->getInput()->getGyroscopeRoll() + M_PI_4;
            
            if (pitch != newPitch){
                // positive pitch if on landscape mode the pysical button of the ipad is on the right (our default orientation)
                // negative pitch if on landscape mode the pysical button of the ipad is on the left
                // the decreasing factor is needed to slow down the movement of the camera
                deltaCameraY = pitch * 0.15;
            }
            newPitch = pitch;
            
            if (roll != newRoll){
                // positive roll if on landscape mode the pysical button of the ipad is on the right (our default orientation)
                // negative roll if on landscape mode the pysical button of the ipad is on the left
                deltaCameraX = roll * 0.08;
            }
            newRoll = roll;
            
            // Set a max up and down movement amplitude
            // ATTENTION: this work only with the following orientation
            // Reset the camera movement (delta of the camera) at 0.5 and when you want to go further up (delta camera is negative)
            if (cameraForwardDirection.y() > 0.9 && deltaCameraX < 0){
                deltaCameraX = 0.0;
            }
            // Reset the camera movement (delta of the camera) at -0.5 and when you want to go further down (delta camera is positive)
            if (cameraForwardDirection.y() < -0.9 && deltaCameraX > 0){
                deltaCameraX = 0.0;
            }
            
            TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->setPosition(newPos);
            TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->rotateCamera(deltaCameraX, deltaCameraY, 0.0f);
            TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->setFieldOfView(fov);
            // At the beginning of each frame the user is considered not having touched
            isPressed = false;
        }
    }
};

#endif /* defined(CAMERA_MOVEMENT_SCRIPT_H) */
