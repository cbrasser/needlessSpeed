#ifndef LASER_RENDERER_H
#define LASER_RENDERER_H

#include "Core.h"
#include "ObjectRenderer.h"
#include "GameObject.h"
#include "TheRenderer.h"


class LaserRenderer : public ObjectRenderer {
public:
    
    void init() override {
        if (TheRenderer::Instance()->renderer->getObjects()->getModel("laser") == nullptr) {

            PropertiesPtr customProperties = TheRenderer::Instance()->renderer->getObjects()->createProperties("customProperties");
            ShaderPtr flatShader = TheRenderer::Instance()->renderer->getObjects()->loadShaderFile("laser", 1, false, true, true, true);
            
            TheRenderer::Instance()->renderer->getObjects()->loadObjModel("laser.obj", false, true, flatShader, customProperties);
        }
    }
    
	void render(std::string cameraName) override {
        if(gameObject->isAlive) {
            vmml::Matrix4f modelMatrix = gameObject->getComponent<Transform>()->getTransformationMatrix();
            
            TheRenderer::Instance()->renderer->getModelRenderer()->queueModelInstance("laser", "laser" + std::to_string(gameObject->getId()), cameraName, modelMatrix, std::vector<std::string>({ "firstLight" }), false, false, false);
        }
    }
    

};

#endif /* defined(LASER_RENDERER_H) */
