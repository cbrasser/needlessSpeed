#ifndef LASER_SCRIPT_H
#define LASER_SCRIPT_H

#include "Core.h"
#include "Behaviour.h"
#include "TheTime.h"
#include "TheRenderer.h"
#include "LightWrapper.cpp"

class LaserScript : public Behaviour {
public:

    void FixedUpdate() {
        if(_timeToLive > 0 && gameObject->isAlive) {
            vmml::Vector3f pos = transform->getPosition() + transform->forward() * _speed;
            transform->setPosition(pos);
            gameObject->getComponent<LightWrapper>()->setPosition(pos);
            _timeToLive -= 1;
        }else{
            gameObject->isAlive = false;
            gameObject->getComponent<LightWrapper>()->setRadius(0.0f);
            _timeToLive = 0;
        }
        
    }
    
    float getTimeToLive() {
        return _timeToLive;
    }
    
    void setTimeToLive(float time){
        _timeToLive = time;
    }
    
private:
    float _timeToLive;
    float _speed = 20;
    
};

#endif /* defined(LASER_SCRIPT_H) */
