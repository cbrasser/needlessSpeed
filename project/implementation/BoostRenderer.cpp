#ifndef BOOST_RENDERER_H
#define BOOST_RENDERER_H

#include "Core.h"
#include "ObjectRenderer.h"
#include "GameObject.h"
#include "TheRenderer.h"

class BoostRenderer : public ObjectRenderer {
public:
	void init() override {
		if (TheRenderer::Instance()->renderer->getObjects()->getModel("bo") == nullptr) {
			ShaderPtr flatShader = TheRenderer::Instance()->renderer->getObjects()->loadShaderFile("boost", 0, false, true, true, true);
			TheRenderer::Instance()->renderer->getObjects()->loadObjModel("bo.obj", false, true, flatShader, nullptr);		
		}
	}

	void render(std::string cameraName) override {
		vmml::Matrix4f modelMatrix = gameObject->getComponent<Transform>()->getTransformationMatrix();
		TheRenderer::Instance()->renderer->getModelRenderer()->queueModelInstance("bo", "Boost_" + std::to_string(gameObject->getId()), cameraName, modelMatrix, std::vector<std::string>({ "" }), false, false, false);
	}
};

#endif /* defined(BOOST_RENDERER_H) */
