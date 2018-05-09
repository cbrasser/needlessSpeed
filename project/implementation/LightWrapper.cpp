#ifndef LIGHT_WRAPPER_H
#define LIGHT_WRAPPER_H

#include "Core.h"
#include "Component.h"
#include "TheRenderer.h"

class LightWrapper : public Component {
public:
    void createLight(std::string name, float radius){
        //name, pos, diffcolor, speccolor, intensity, attenuation, radius
        _light = TheRenderer::Instance()->renderer->getObjects()->createLight(name, vmml::Vector3f(5.0f, 0.0f, 0.0f), vmml::Vector3f(1.0f, 0.0f, 0.0f), vmml::Vector3f(1.0f, 0.0f, 0.0f), 10000000000000.0f, 0.0f, radius);
        _name = name;
    }
    
    vmml::Vector4f getPosition() {
        return _light->getPosition();
    }
    
    float getRadius() {
        return _light->getRadius();
    }
    
    std::string getName(){
        return _name;
    }
    
    void setPosition(vmml::Vector3f position) {
        _light->setPosition(position);
    }
    
    void setRadius(float radius) {
        _light->setRadius(radius);
    }
    
    void setLight(vmml::Vector3f color){
        _light->setDiffuseColor(color);
        _light->setSpecularColor(color);
    }
    
private:
    LightPtr _light;
    std::string _name;
};

#endif /* defined(LIGHT_WRAPPER_H) */
