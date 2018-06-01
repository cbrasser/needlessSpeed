#ifndef MOVE_SCRIPT_H
#define MOVE_SCRIPT_H

#include "Core.h"
#include "Behaviour.h"
#include "TheRenderer.h"
#include "TheTime.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Collider.h"
#include "Physics.h"

class MoveScript : public Behaviour{
public: 
	//Changed every frame by the factor calculated based on current acceleration & inputs
    float acceleration = 0.0f;
    float turning = 0.0f;
    //The higher this factor, the slower the cart turns
    float turningIntensity = 30;
    float time = 0.0f;
    float pi = 3.14f;
    double pitch;
    double newPitch;
    double roll;
    double newRoll;
    float rollZero = -1.2; // -1.6 is holding it vertical
    vmml::Vector3f position = vmml::Vector3f(0,0,0);
    vmml::Vector3f velocity = vmml::Vector3f(0,0,0);
    TheTime theTime;
	bool isCollision = false;

    float getAcceleration(float velocityForAcceleration){
        float accFac = 20.0f;
        
        float intervalLimit = 0.2;
        float frictionFactor = 0.14; // smaller than intervalLimit, should act like friction
        //mean, var and std needed for acceleration function
        float mean = 1.0f;
        float std = 5.0f;
        float var = 25.0f;
        float abs;
        
        //Absolute value of acceleration
        if(velocityForAcceleration<0.0f){
            abs = - 2*velocityForAcceleration;
        } else {
            abs = 2*velocityForAcceleration;
        }
        
        /* iOS: control movement using touch screen */
        if (Input::isTouchDevice()) {
            
            if (TheRenderer::Instance()->renderer->isRunning()) {
                //We are driving forwards
                //std::cout << "gyroscope angle: " << (TheRenderer::Instance()->renderer->getInput()->getGyroscopeRoll()) << std::endl;
                if(velocityForAcceleration>intervalLimit){
                    
                    //Accelerating further
                    if ((TheRenderer::Instance()->renderer->getInput()->getGyroscopeRoll()) >= (rollZero + 0.15)){
                        float returnVal = (1/(sqrt(2*pi*var)))*exp((-(abs-mean)*(abs-mean)/(2*var)));
                        // std::cout<<"\nreturn value: "<<returnVal<<"\n";
                        return 1.0f;
                        //Breaking fast
                    }else if ((TheRenderer::Instance()->renderer->getInput()->getGyroscopeRoll()) <= (rollZero - 0.15)){
                        //return -(1/(sqrt(2*pi*var)))*exp((-(abs-mean)*(abs-mean)/(2*var)));
                        return -1.0f;
                    }
                    //Breaking slowly
                    else {
                        //return -(1/(sqrt(2*pi*var)))*exp((-(abs-mean)*(abs-mean)/(2*var)));
                        return -frictionFactor;
                    }
                    //Standing still
                }else if(velocityForAcceleration<=intervalLimit && velocityForAcceleration >= -intervalLimit){
                    //Accelerating
                    if ((TheRenderer::Instance()->renderer->getInput()->getGyroscopeRoll()) >= (rollZero + 0.15)){
                        //return (1/(sqrt(2*pi*var)))*exp((-(abs-mean)*(abs-mean)/(2*var)));
                        return 1.0f;
                        //Accelerating backwards
                    }else if ((TheRenderer::Instance()->renderer->getInput()->getGyroscopeRoll()) <= (rollZero - 0.15)){
                        //return -(1/(sqrt(2*pi*var)))*exp((-(abs-mean)*(abs-mean)/(2*var)));
                        return -1.0f;
                    }
                    //Nothing
                    else {
                        return -velocityForAcceleration;
                    }
                    //Driving backwards
                }else{
                    //Breaking fast
                    if ((TheRenderer::Instance()->renderer->getInput()->getGyroscopeRoll()) >= (rollZero + 0.15)){
                        //return -(1/(sqrt(2*pi*var)))*exp((-(abs-mean)*(abs-mean)/(2*var)));
                        return 1.0f;
                        //Accelerating further backwards
                    }else if ((TheRenderer::Instance()->renderer->getInput()->getGyroscopeRoll()) <= (rollZero - 0.15)){
                        //return (1/(sqrt(2*pi*var)))*exp((-(abs-mean)*(abs-mean)/(2*var)));
                        return -1.0f;
                        //Breaking
                    } else {
                        //return -(1/(sqrt(2*pi*var)))*exp((-(abs-mean)*(abs-mean)/(2*var)));
                        return frictionFactor;
                    }
                }
            }
            /* Windows: control movement using keyboard */
        }else{
            
            //We are driving forwards
            if(velocityForAcceleration>intervalLimit){
                
                //Accelerating further
                if (TheRenderer::Instance()->renderer->getInput()->getKeyState(bRenderer::KEY_W) == bRenderer::INPUT_PRESS){
                    return 1.0f; 
                    //(1/(sqrt(2*pi*var)))*exp((-(abs-mean)*(abs-mean)/(2*var)));
                    // std::cout<<"\nreturn value: "<<returnVal<<"\n";
                    //Breaking fast
                }else if (TheRenderer::Instance()->renderer->getInput()->getKeyState(bRenderer::KEY_S) == bRenderer::INPUT_PRESS){
                    //return -(1/(sqrt(2*pi*var)))*exp((-(abs-mean)*(abs-mean)/(2*var)));
                    return -1.0f;
                }
                //Breaking slowly
                else {
                    //return -(1/(sqrt(2*pi*var)))*exp((-(abs-mean)*(abs-mean)/(2*var)));
                    return -frictionFactor;
                }
                //Standing still
            }else if(velocityForAcceleration<=intervalLimit && velocityForAcceleration >= -intervalLimit){
                //Accelerating
                if (TheRenderer::Instance()->renderer->getInput()->getKeyState(bRenderer::KEY_W) == bRenderer::INPUT_PRESS){
                    //return (1/(sqrt(2*pi*var)))*exp((-(abs-mean)*(abs-mean)/(2*var)));
                    return 1.0f;
                    //Accelerating backwards
                }else if (TheRenderer::Instance()->renderer->getInput()->getKeyState(bRenderer::KEY_S) == bRenderer::INPUT_PRESS){
                    //return -(1/(sqrt(2*pi*var)))*exp((-(abs-mean)*(abs-mean)/(2*var)));
                    return -1.0f;
                }
                //Nothing
                else {
                    return -velocityForAcceleration;
                }
                //Driving backwards
            }else{
                //Breaking fast
                if (TheRenderer::Instance()->renderer->getInput()->getKeyState(bRenderer::KEY_W) == bRenderer::INPUT_PRESS){
                    //return -(1/(sqrt(2*pi*var)))*exp((-(abs-mean)*(abs-mean)/(2*var)));
                    return 1.0f;
                    //Accelerating further backwards
                }else if (TheRenderer::Instance()->renderer->getInput()->getKeyState(bRenderer::KEY_S) == bRenderer::INPUT_PRESS){
                    //return (1/(sqrt(2*pi*var)))*exp((-(abs-mean)*(abs-mean)/(2*var)));
                    return -1.0f;
                    //Breaking
                } else {
                    //return -(1/(sqrt(2*pi*var)))*exp((-(abs-mean)*(abs-mean)/(2*var)));
                    return frictionFactor;
                }
            }
        }
    }
    
    float getTurning(float turning, float velocityForAcceleration){
    	float intervalLimit = 0.2;
        
        /* iOS: control movement using touch screen */
        if (Input::isTouchDevice()) {
            float newTurning = turning;
            
            if (TheRenderer::Instance()->renderer->getInput()->getGyroscopePitch() <= -0.15) {
                newTurning -= 1.0;
            }
            else if (TheRenderer::Instance()->renderer->getInput()->getGyroscopePitch() >= 0.15) {
                newTurning += 1.0;
            }
            
            return newTurning;
            
            /* Windows: control movement using keyboard */
        }else{
            float newTurning = turning;
            
            if (TheRenderer::Instance()->renderer->getInput()->getKeyState(bRenderer::KEY_A) == bRenderer::INPUT_PRESS) {
            	if(velocityForAcceleration ==0){
            		newTurning += 0.0;
            	} else {
            		newTurning -= 1.0;
            	}
                
            }
            else if (TheRenderer::Instance()->renderer->getInput()->getKeyState(bRenderer::KEY_D) == bRenderer::INPUT_PRESS) {
                if(velocityForAcceleration == 0){
                	newTurning +=0.0;
                }else {
                	newTurning +=1.0;
                } 
            }
            
            return newTurning;
        }
    }
    
    void Update() {

		//std::cout << "Movement Script Boolean" << isCollision << std::endl;

        position = transform->getPosition();
        
        float abs = 0.0;
        float wheelSpeed = 0.0;
        for(int i = 0; i < velocity.size(); i++) abs += velocity[i] * velocity[i];
        abs = sqrt(abs);
    	//Honestly i have no idea why i did some things here
        vmml::Vector3f someOtherVelocity = velocity;
        vmml::Vector3f carDir = vmml::Vector3f(-sin(turning/turningIntensity),0,-cos(turning/turningIntensity));
        
        if(vmml::dot(carDir, vmml::normalize(someOtherVelocity)) >0){
            velocity = abs * carDir;
        }else {
            velocity = -abs * carDir;
        }
        
        float velocityForAcceleration = abs;
        if(vmml::dot(carDir, vmml::normalize(someOtherVelocity)) <0){
            velocityForAcceleration = -velocityForAcceleration;
        }
        float accelerating = this->getAcceleration(velocityForAcceleration);
        
        float turningDirection = 0.0f;
        float turningOld = turning;
        turning = this->getTurning(turning, velocityForAcceleration);
        if (turningOld < turning) {
            turningDirection = -1.f;
        }
        else if (turningOld > turning) {
            turningDirection = 1.f;
        }
        else {
            turningDirection = 0.f;
        }
        
        vmml::Vector3f acceleration = accelerating*carDir;
        
        velocity += acceleration;
        //Max speed
        if(abs>35.0f){
            velocity = vmml::normalize(velocity)*35.0f;
        }
        
        
        vmml::Vector3f newPos = position+velocity*TheTime::deltaTime;
        position = newPos;
        //vmml::Vector3f rot = vmml::Vector3f(0,1,0);
        //vmml::Vector3f scale = vmml::Vector3f(1,1,1);
        //vmml::Matrix4f carModelMatrix = vmml::create_translation(newPos)*vmml::create_rotation(turning/20,rot)*vmml::create_scaling(scale);
        
        vmml::Vector3f pos = transform->getPosition();
        transform->setPosition(newPos);
        transform->setRotation(turning/turningIntensity*vmml::Vector3f(0,1,0));
        
        
        
        //Wheel Animation
        if (abs >= 5.f) {
            wheelSpeed = 5.f;
        }
        else {
            wheelSpeed = abs;
        }

		//TODO: Might need to also take in consideration if we are driving forwards/backwards
        if (turningDirection < 0.f) { //turning right
        	if(velocityForAcceleration >= 0){
        	SceneManager::getCurrentScene()->getObjectByName("WheelLF")->transform->setRotationMultiple(vmml::Vector3f(-0.2f * wheelSpeed * theTime.time, 0.f, 0.f), vmml::Vector3f(0.f, 0.5f , 0.f));
            SceneManager::getCurrentScene()->getObjectByName("WheelRF")->transform->setRotationMultiple(vmml::Vector3f(0.2f * wheelSpeed * theTime.time, 0.f, 0.f), vmml::Vector3f(0.f, (3.14159f + 0.5f) , 0.f));
        	} else {
        	SceneManager::getCurrentScene()->getObjectByName("WheelLF")->transform->setRotationMultiple(vmml::Vector3f(-0.2f * wheelSpeed * theTime.time, 0.f, 0.f), vmml::Vector3f(0.f, -0.5f , 0.f));
            SceneManager::getCurrentScene()->getObjectByName("WheelRF")->transform->setRotationMultiple(vmml::Vector3f(0.2f * wheelSpeed * theTime.time, 0.f, 0.f), vmml::Vector3f(0.f, (3.14159f - 0.5f) , 0.f));
        	}

            
            SceneManager::getCurrentScene()->getObjectByName("WheelLR")->transform->setRotation(vmml::Vector3f(-0.2f * wheelSpeed * theTime.time, 0.f, 0.f));
            SceneManager::getCurrentScene()->getObjectByName("WheelRR")->transform->setRotation(vmml::Vector3f(-0.2f * wheelSpeed * theTime.time, (3.14159f + 0.f), 0.f));
        }
        else if (turningDirection > 0.f) { //turning left
        	if(velocityForAcceleration >= 0){
        		SceneManager::getCurrentScene()->getObjectByName("WheelLF")->transform->setRotationMultiple(vmml::Vector3f(-0.2f * wheelSpeed * theTime.time, 0.f, 0.f), vmml::Vector3f(0.f, -0.5f, 0.f));
            	SceneManager::getCurrentScene()->getObjectByName("WheelRF")->transform->setRotationMultiple(vmml::Vector3f(0.2f * wheelSpeed * theTime.time, 0.f, 0.f), vmml::Vector3f(0.f, (3.14159f - 0.5f), 0.f));
        	}else {
        		SceneManager::getCurrentScene()->getObjectByName("WheelLF")->transform->setRotationMultiple(vmml::Vector3f(-0.2f * wheelSpeed * theTime.time, 0.f, 0.f), vmml::Vector3f(0.f, 0.5f, 0.f));
            SceneManager::getCurrentScene()->getObjectByName("WheelRF")->transform->setRotationMultiple(vmml::Vector3f(0.2f * wheelSpeed * theTime.time, 0.f, 0.f), vmml::Vector3f(0.f, (3.14159f + 0.5f), 0.f));
        	}
            
            
            SceneManager::getCurrentScene()->getObjectByName("WheelLR")->transform->setRotation(vmml::Vector3f(-0.2f * wheelSpeed * theTime.time, 0.f, 0.f));
            SceneManager::getCurrentScene()->getObjectByName("WheelRR")->transform->setRotation(vmml::Vector3f(-0.2f * wheelSpeed * theTime.time, (3.14159f + 0.f), 0.f));
        }
        else { //not turning
            SceneManager::getCurrentScene()->getObjectByName("WheelLF")->transform->setRotation(vmml::Vector3f(-0.2f * wheelSpeed * theTime.time, 0.f, 0.f));
            SceneManager::getCurrentScene()->getObjectByName("WheelRF")->transform->setRotation(vmml::Vector3f(-0.2f * wheelSpeed * theTime.time, (3.14159f + 0.f), 0.f));
            
            SceneManager::getCurrentScene()->getObjectByName("WheelLR")->transform->setRotation(vmml::Vector3f(-0.2f * wheelSpeed * theTime.time, 0.f, 0.f));
            SceneManager::getCurrentScene()->getObjectByName("WheelRR")->transform->setRotation(vmml::Vector3f(-0.2f * wheelSpeed * theTime.time, (3.14159f + 0.f), 0.f));
        }
    }
};


#endif /* defined(MOVE_SCRIPT_H) */
