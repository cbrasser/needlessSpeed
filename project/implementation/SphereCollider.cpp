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

class SphereCollider : public Collider {
public:

    bool collide(Collider* other) {
        vmml::Vector3f pos1 = gameObject->getComponent<Transform>()->getPosition();
        vmml::Vector3f pos2 = other->gameObject->getComponent<Transform>()->getPosition();
        
        float minDistance = getRadius() + other->gameObject->getComponent<SphereCollider>()->getRadius();
        if((pos1 - pos2).squared_length() <= minDistance * minDistance){

            if ((other->gameObject->getComponent<TreeRenderer>() != nullptr && gameObject->getComponent<CarRenderer>() != nullptr)
				|| (gameObject->getComponent<TreeRenderer>() != nullptr && other->gameObject->getComponent<CarRenderer>() != nullptr)) {
                
				std::cout << "Collision Detected - Car and Tree" << std::endl;
                                                                                            
			}
			/**else if (gameObject->getComponent<AsteroidRenderer>() != nullptr &&
                other->gameObject->getComponent<AsteroidRenderer>() != nullptr) {
                std::cout << gameObject->name << " collidet with " << other->gameObject->name << std::endl;
                
                Explosion->getComponent<Transform>()->setPosition(pos1);
                Explosion->getComponent<ParticleSystemRenderer>()->init();
                Explosion->getComponent<ParticleSystemRenderer>()->particleSystem->activate();
                
                SecondExplosion->getComponent<Transform>()->setPosition(pos2);
                SecondExplosion->getComponent<ParticleSystemRenderer>()->init();
                SecondExplosion->getComponent<ParticleSystemRenderer>()->particleSystem->activate();
                
                gameObject->destroy();
                other->gameObject->destroy();
            }
            */    
			return true;
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

