    #ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H

#include "Collider.h"
#include "Behaviour.h"
#include "TheRenderer.h"
#include "Core.h"
#include "AsteroidRenderer.cpp"
#include "LaserRenderer.cpp"
#include "TreeRenderer.cpp"
#include "CarRenderer.cpp"
#include "ShipRenderer.cpp"
#include "ParticleSystemRenderer.cpp"
#include "ParticleSystem.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "LightWrapper.cpp"
#include "MoveScript.cpp"
#include "StartLineRenderer.cpp"
#include "TheTime.h"
#include "UIRenderer.cpp"

class SphereCollider : public Collider {
public:

	TheTime theTime;
	double lapStartTime = 0.0;
	double lapEndTime = 0.0;
	double totalLapTime = 999999.0f;
	double tempTotalLapTime;
	double bestLapTime = 999999.0f;
	int lapCount = -1;

    bool collide(Collider* other) {
        vmml::Vector3f pos1 = gameObject->getComponent<Transform>()->getPosition();
        vmml::Vector3f pos2 = other->gameObject->getComponent<Transform>()->getPosition();
        
        float minDistance = getRadius() + other->gameObject->getComponent<SphereCollider>()->getRadius();
        if((pos1 - pos2).squared_length() <= minDistance * minDistance){

            if (other->gameObject->getComponent<TreeRenderer>() != nullptr && gameObject->getComponent<CarRenderer>() != nullptr) {
                
				std::cout << "Collision Detected - Car and Tree" << std::endl;
				gameObject->getComponent<MoveScript>()->isCollision = true;

			}
			else if (other->gameObject->getComponent<StartLineRenderer>() != nullptr && gameObject->getComponent<CarRenderer>() != nullptr) {
				std::cout << "Start Line Triggered" << std::endl;

				lapEndTime = theTime.time;
				tempTotalLapTime = lapEndTime - lapStartTime;
				lapStartTime = theTime.time;

				if (tempTotalLapTime > 2.0) {
					lapCount++;
					std::cout << "Lap Time: " << totalLapTime << std::endl;
					totalLapTime = tempTotalLapTime;

					if (totalLapTime < bestLapTime) {
						bestLapTime = totalLapTime;
						std::cout << "Best Lap Time: " << bestLapTime << std::endl;
					}

					if (lapCount > 0) {
						UItotalLapTime = totalLapTime;
						UIbestLapTime = bestLapTime;
					}
					
				}

            }
 
			return true;
        }
        
		if (gameObject->getComponent<MoveScript>() != nullptr) {
			gameObject->getComponent<MoveScript>()->isCollision = false;
		}
        return false;
    }
    
    void setRadius(float r) {
        _radius = r;
    }
    
    float getRadius() {
        return _radius;
    }
    
private:
    float _radius;
    
};

#endif /* defined(SPHERE_COLLIDER_H) */

