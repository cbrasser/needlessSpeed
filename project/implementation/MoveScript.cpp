#ifndef MOVE_SCRIPT_H
#define MOVE_SCRIPT_H

#include "Core.h"
#include "Behaviour.h"
#include "TheRenderer.h"
#include "TheTime.h"
#include "Scene.h"
#include "SceneManager.h"




class MoveScript : public Behaviour{
public: 
	float acceleration = 0.0f;
	float turning = 0.0f;
	float time = 0.0f;
	float pi = 3.14f;
	vmml::Vector3f position = vmml::Vector3f(0,0,0);
	vmml::Vector3f velocity = vmml::Vector3f(0,0,0);

	float getAcceleration(float velocityForAcceleration){
	float accFac = 20.0f;
	float intervalLimit = 0.2;
	float frictionFactor = 0.15; // smaller than intervalLimit
	float mean = 3.0f;
	float std = 5.0f;
	float var = 10.0f;
	float abs;
	if(velocityForAcceleration<0.0f){
		abs = - 2*velocityForAcceleration;
	} else {
		abs = 2*velocityForAcceleration;
	}

	//We are driving forwards
	if(velocityForAcceleration>intervalLimit){
		
		//Accelerating further
		if (TheRenderer::Instance()->renderer->getInput()->getKeyState(bRenderer::KEY_W) == bRenderer::INPUT_PRESS){
			// float returnVal = (1/(sqrt(2*pi*var)))*exp((-(abs-mean)*(abs-mean)/(2*var)));
			// std::cout<<"\nreturn value: "<<returnVal<<"\n";
			return 1.0f;
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
	} else{
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

float getTurning(float turning)
{
	float newTurning = turning;

	
			if (TheRenderer::Instance()->renderer->getInput()->getKeyState(bRenderer::KEY_A) == bRenderer::INPUT_PRESS)
				newTurning -= 1.0;
			else if (TheRenderer::Instance()->renderer->getInput()->getKeyState(bRenderer::KEY_D) == bRenderer::INPUT_PRESS)
				newTurning += 1.0;
		

		return newTurning;

}

	void Update() {

		position = transform->getPosition();
		
		float abs = 0.0;
		for(int i = 0; i < velocity.size(); i++) abs += velocity[i] * velocity[i];
		abs = sqrt(abs);
		vmml::Vector3f someOtherVelocity = velocity;
		vmml::Vector3f carDir = vmml::Vector3f(-sin(turning/20),0,-cos(turning/20));

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
		turning = this->getTurning(turning);
		std::cout<<"Velocity with directions: "<<velocityForAcceleration;
		std::cout<<"accelerating output: "<<accelerating;
		
		vmml::Vector3f acceleration = accelerating*carDir;

		std::cout<<"acceleration vector: "<<acceleration;
		std::cout<<"veloctiy vector 1: "<<velocity;
		velocity += acceleration;


		std::cout<<"veloctiy vector 2: "<<velocity;

		if(abs>20.0f){
				velocity = vmml::normalize(velocity)*20.0f;
		}
		
		
		vmml::Vector3f newPos = position+velocity*TheTime::deltaTime;
		position = newPos;
		//vmml::Vector3f rot = vmml::Vector3f(0,1,0);
		//vmml::Vector3f scale = vmml::Vector3f(1,1,1);
		//vmml::Matrix4f carModelMatrix = vmml::create_translation(newPos)*vmml::create_rotation(turning/20,rot)*vmml::create_scaling(scale);

		vmml::Vector3f pos = transform->getPosition();
		transform->setPosition(newPos);
		transform->setRotation(turning/20*vmml::Vector3f(0,1,0));
		
	}
};






#endif /* defined(MOVE_SCRIPT_H) */