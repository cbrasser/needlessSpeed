#ifndef START_LINE_RENDERER_H
#define START_LINE_RENDERER_H

#include "Core.h"
#include "ObjectRenderer.h"
#include "GameObject.h"
#include "TheRenderer.h"
#include "LightWrapper.cpp"
#include "TheTime.h"

class StartLineRenderer : public ObjectRenderer {
public:

	void init() override {
		if (TheRenderer::Instance()->renderer->getObjects()->getModel("Cube") == nullptr) {

			ShaderPtr markerShader = TheRenderer::Instance()->renderer->getObjects()->loadShaderFile("marker", 0, false, false, false, false, false);
			TheRenderer::Instance()->renderer->getObjects()->loadObjModel("Cube.obj", false, true, markerShader, nullptr);
		}
	}

	void render(std::string cameraName, ShaderPtr customShader) override {

		ShaderPtr shader;
		if(customShader == nullptr){
			shader = TheRenderer::Instance()->renderer->getObjects()->getShader("marker");
		} else {
			shader = customShader;
		}

		vmml::Matrix4f modelMatrix = gameObject->getComponent<Transform>()->getTransformationMatrix();

		//ShaderPtr shader = TheRenderer::Instance()->renderer->getObjects()->getShader("marker");
		vmml::Matrix4f viewMatrix = TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->getViewMatrix();

		if (shader.get())
		{
			shader->setUniform("ProjectionMatrix", vmml::Matrix4f::IDENTITY);
			shader->setUniform("ViewMatrix", viewMatrix);
			shader->setUniform("ModelMatrix", modelMatrix);

			vmml::Vector4f eyePos = vmml::Vector4f(0.0f, 0.0f, 10.0f, 1.0f);
			shader->setUniform("EyePos", eyePos);

		}
		//TheRenderer::Instance()->renderer->getModelRenderer()->queueModelInstance("car", "car" + std::to_string(gameObject->getId()), "camera", modelMatrix, std::vector<std::string>({ "firstLight"}), false, false, false);
		TheRenderer::Instance()->renderer->getModelRenderer()->drawModel("Cube", cameraName, modelMatrix, std::vector<std::string>({}));
	}
};

#endif /* defined(START_LINE_RENDERER_H) */
