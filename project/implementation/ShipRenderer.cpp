#ifndef SHIP_RENDERER_H
#define SHIP_RENDERER_H

#include "Core.h"
#include "ObjectRenderer.h"
#include "GameObject.h"
#include "TheRenderer.h"
#include "SceneManager.h"
#include "CameraMovementScript.cpp"

class ShipRenderer : public ObjectRenderer {
public:
    
    void init() override {

        if (TheRenderer::Instance()->renderer->getObjects()->getModel("SpaceShip") == nullptr) {
            
            PropertiesPtr customProperties = TheRenderer::Instance()->renderer->getObjects()->createProperties("customProperties");

            
            ShaderPtr flatShader = TheRenderer::Instance()->renderer->getObjects()->loadShaderFile("flatShip", 1, false, true, true, true, false);
            
            TheRenderer::Instance()->renderer->getObjects()->loadObjModel("SpaceShip.obj", false, true, flatShader, customProperties);
        }
    }
    
	void render(std::string cameraName) override {
        vmml::Matrix4f modelMatrix = gameObject->getComponent<Transform>()->getTransformationMatrix();
        
        TheRenderer::Instance()->renderer->getModelRenderer()->queueModelInstance("SpaceShip", "SpaceShip" + std::to_string(gameObject->getId()), cameraName, modelMatrix, std::vector<std::string>({ "shipLight" }), false, false, false);
    }
};

#endif /* defined(SHIP_RENDERER_H) */
