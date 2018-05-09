#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H

#include "Collider.h"
#include "Behaviour.h"
#include "TheRenderer.h"
#include "Core.h"
#include "AsteroidRenderer.cpp"
#include "LaserRenderer.cpp"
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

            GameObject *Explosion = SceneManager::getCurrentScene()->getObjectByName("ParticleSystem");
            GameObject *SecondExplosion = SceneManager::getCurrentScene()->getObjectByName("ParticleSystem");

            if (gameObject->getComponent<AsteroidRenderer>() != nullptr &&
                other->gameObject->getComponent<ShipRenderer>() != nullptr) {
                
                Explosion->getComponent<Transform>()->setPosition(pos1);
                Explosion->getComponent<ParticleSystemRenderer>()->init();
                Explosion->getComponent<ParticleSystemRenderer>()->particleSystem->activate();
                
                SecondExplosion->getComponent<Transform>()->setPosition(pos2);
                SecondExplosion->getComponent<ParticleSystemRenderer>()->init();
                SecondExplosion->getComponent<ParticleSystemRenderer>()->particleSystem->activate();
                
                // Destroy the asteroid
                gameObject->destroy();
                // Destroy the ship
                other->gameObject->destroy();
                
                
                
			} else if (other->gameObject->getComponent<AsteroidRenderer>() != nullptr &&
                gameObject->getComponent<ShipRenderer>() != nullptr) {
                
                Explosion->getComponent<Transform>()->setPosition(pos2);
                Explosion->getComponent<ParticleSystemRenderer>()->init();
                Explosion->getComponent<ParticleSystemRenderer>()->particleSystem->activate();
                
                SecondExplosion->getComponent<Transform>()->setPosition(pos1);
                SecondExplosion->getComponent<ParticleSystemRenderer>()->init();
                SecondExplosion->getComponent<ParticleSystemRenderer>()->particleSystem->activate();

                // Destroy the asteroid
                other->gameObject->destroy();
                // Destroy the ship
                gameObject->destroy();
                                                                                                
			} else if (gameObject->getComponent<AsteroidRenderer>() != nullptr &&
                other->gameObject->getComponent<LaserRenderer>() != nullptr) {
                
                Explosion->getComponent<Transform>()->setPosition(pos1);
                Explosion->getComponent<ParticleSystemRenderer>()->init();
                Explosion->getComponent<ParticleSystemRenderer>()->particleSystem->activate();
                gameObject->destroy();
                
                other->gameObject->getComponent<LightWrapper>()->setRadius(0.0f);
                other->gameObject->isAlive = false;
                
            } else if (other->gameObject->getComponent<AsteroidRenderer>() != nullptr &&
                gameObject->getComponent<LaserRenderer>() != nullptr) {
                
                Explosion->getComponent<Transform>()->setPosition(pos2);
                Explosion->getComponent<ParticleSystemRenderer>()->init();
                Explosion->getComponent<ParticleSystemRenderer>()->particleSystem->activate();
                other->gameObject->destroy();
                
                gameObject->getComponent<LightWrapper>()->setRadius(0.0f);
                gameObject->isAlive = false;
                
            } else if (gameObject->getComponent<AsteroidRenderer>() != nullptr &&
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

