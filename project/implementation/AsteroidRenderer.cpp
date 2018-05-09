#ifndef ASTEROID_RENDERER_H
#define ASTEROID_RENDERER_H

#include "Core.h"
#include "ObjectRenderer.h"
#include "GameObject.h"
#include "TheRenderer.h"
#include "LightWrapper.cpp"


class AsteroidRenderer : public ObjectRenderer {
public:

	void init() override {
		if (TheRenderer::Instance()->renderer->getObjects()->getModel("asteroid") == nullptr) {
            
            // Use flat shader
            ShaderPtr flatShader = TheRenderer::Instance()->renderer->getObjects()->loadShaderFile("flatAsteroid", 8, true, true, true, true, false);
            
            TheRenderer::Instance()->renderer->getObjects()->loadObjModel("asteroid.obj", false, true, flatShader, nullptr);
		}
	}

	void render() override {
		/*
		vmml::Vector3f front = transform->forward() * 10;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(1.0f, 0.0f, 0.0f); //blue color
		glPointSize(100.0f);//set point size to 10 pixels
		glBegin(GL_POINTS);
		//glVertex3f(-1 * front.x(), -1 * front.y(), -1 * front.z());
		glVertex3f(0, 0, 0);
		glEnd();
		*/

		vmml::Matrix4f modelMatrix = gameObject->getComponent<Transform>()->getTransformationMatrix();
        
        TheRenderer::Instance()->renderer->getModelRenderer()->queueModelInstance("asteroid", "asteroid_" + std::to_string(gameObject->getId()), "camera", modelMatrix, std::vector<std::string>({ "firstLight", "laserLight0",
            "laserLight1",
            "laserLight2",
            "laserLight3",
            "laserLight4",
            "laserLight5",
            "laserLight6"}), false, false, false);
    }
};

#endif /* defined(ASTEROID_RENDERER_H) */
