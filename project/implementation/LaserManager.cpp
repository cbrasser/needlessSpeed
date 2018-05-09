#ifndef LASER_MANAGER_H
#define LASER_MANAGER_H

#include "Core.h"
#include "Behaviour.h"
#include "TheTime.h"
#include "TheRenderer.h"
#include "LaserScript.cpp"
#include "LaserRenderer.cpp"
#include "SphereCollider.cpp"
#include "Scene.h"
#include "SceneManager.h"
#include "LightWrapper.cpp"


class LaserManager : public Behaviour {
public:
    int numOfLasers = 7;
    GameObject* laserArray[7];
    
    float scaleFactor = 1.5f;
    const float distanceFactor = 7.f;
    
    // Variable added to control the shooting and avoid a continuous laser shoot, making the game a little more challenging
    int timeToShoot = 25;
    
    void Update() {
        TouchMap touchMap = TheRenderer::Instance()->renderer->getInput()->getTouches();
        for (auto t = touchMap.begin(); t != touchMap.end(); ++t) {
            Touch touch = t->second;
            if (timeToShoot > 25) {
                if (touch.startPositionX > TheRenderer::Instance()->renderer->getView()->getWidth() / 2) {
                    Shoot();
                    timeToShoot = 0;
                }
            }
        }
        timeToShoot++;
    }

    void Shoot() {
        float timeleft = laserArray[0]->getComponent<LaserScript>()->getTimeToLive();
        int oldest = 0;
        
        vmml::Vector3f shipDirection = transform->forward() * distanceFactor;
        
        for (int i = 0; i < numOfLasers; i++) {
            if (timeleft > laserArray[i]->getComponent<LaserScript>()->getTimeToLive()) {
                timeleft = laserArray[i]->getComponent<LaserScript>()->getTimeToLive();
                oldest = i;
            }
            if(!laserArray[i]->isAlive){
                vmml::Matrix4f rotation = transform->getRotation();
                vmml::Vector3f position = transform->getPosition() - shipDirection;
                laserArray[i]->transform->setPosition(position);
                laserArray[i]->transform->setRotation(rotation);
                laserArray[i]->transform->setScale(vmml::Vector3f(scaleFactor));
                laserArray[i]->isAlive = true;
                laserArray[i]->getComponent<LaserScript>()->setTimeToLive(100);
                laserArray[i]->getComponent<LightWrapper>()->setPosition(position);
                laserArray[i]->getComponent<LightWrapper>()->setRadius(250.0f);
                
                return;
            }
            if(i == numOfLasers-1){
                vmml::Matrix4f rotation = transform->getRotation();
                vmml::Vector3f position = transform->getPosition() - shipDirection;
                laserArray[oldest]->transform->setPosition(position);
                laserArray[oldest]->transform->setRotation(rotation);
                laserArray[oldest]->transform->setScale(vmml::Vector3f(scaleFactor));
                laserArray[oldest]->isAlive = true;
                laserArray[oldest]->getComponent<LaserScript>()->setTimeToLive(100);
                laserArray[oldest]->getComponent<LightWrapper>()->setPosition(position);
                laserArray[oldest]->getComponent<LightWrapper>()->setRadius(250.0f);
                
                return;
            }
        }
    }
    
};
#endif /* defined(LASER_MANAGER_H) */
