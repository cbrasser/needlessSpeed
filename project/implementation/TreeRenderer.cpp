#ifndef TREE_RENDERER_H
#define TREE_RENDERER_H

#include "Core.h"
#include "ObjectRenderer.h"
#include "GameObject.h"
#include "TheRenderer.h"
#include "LightWrapper.cpp"
#include "TheTime.h"

class TreeRenderer : public ObjectRenderer {
public:

	float pi = 3.1414f;
	float frequency = 3.0f;
	GLfloat dayNightPulse = 0.0f;
	vmml::Vector3f lightDirection = vmml::Vector3f(1.f, 1.f, 1.f);
	GLfloat directionFloat = 0.0f;
	GLfloat treeAnimation = 0.0f;
	TheTime theTime;

	void init() override {
		if (TheRenderer::Instance()->renderer->getObjects()->getModel("Tree") == nullptr) {
			
			ShaderPtr treeShader = TheRenderer::Instance()->renderer->getObjects()->loadShaderFile("tree", 0, false, false, false, false, false);
			TheRenderer::Instance()->renderer->getObjects()->loadObjModel("Tree.obj", false, true, treeShader, nullptr);
		}
	}

	void render(std::string cameraName, ShaderPtr customShader) override {

		ShaderPtr shader;
		if(customShader == nullptr){
			shader = TheRenderer::Instance()->renderer->getObjects()->getShader("tree");
			shader->setUniform("shadow",0.0);
		} else {
			shader = TheRenderer::Instance()->renderer->getObjects()->getShader("tree");
			shader->setUniform("shadow",1.0);
		}

		vmml::Matrix4f modelMatrix = gameObject->getComponent<Transform>()->getTransformationMatrix();
		//vmml::Matrix4f modelMatrix = vmml::create_scaling(vmml::Vector3f(1,1,1));
		TexturePtr colorLUT = TheRenderer::Instance()->renderer->getObjects()->getTexture("colorLUT");

		//ShaderPtr shader = TheRenderer::Instance()->renderer->getObjects()->getShader("tree");
		vmml::Matrix4f viewMatrix = TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getViewMatrix();
		vmml::Matrix4f projectionMatrix = TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getProjectionMatrix();

		vmml::Matrix4f lightViewMatrix = TheRenderer::Instance()->renderer->getObjects()->getCamera("shadowCamera")->getViewMatrix();
		vmml::Matrix4f lightProjectionMatrix = TheRenderer::Instance()->renderer->getObjects()->getCamera("shadowCamera")->getProjectionMatrix();
		vmml::Matrix4f lightSpaceMatrix = lightProjectionMatrix * lightViewMatrix;


		//Light Calculations
		dayNightPulse = 0.5*(1 + cos(theTime.time / frequency));
		directionFloat = fmod(theTime.time, pi * 2 * frequency) / (pi * frequency) - 1;
		lightDirection = vmml::Vector3f((directionFloat * 2), 1.f, 0.f);

		//Tree Animation
		treeAnimation = 0.005 * (199 + sin(2 * pi * theTime.time));

		if (shader.get())
		{
			shader->setUniform("lightSpaceMatrix", lightSpaceMatrix);
			shader->setUniform("ProjectionMatrix", projectionMatrix);
			shader->setUniform("ViewMatrix", viewMatrix);
			shader->setUniform("ModelMatrix", modelMatrix);
			shader->setUniform("ColorLUT", colorLUT);

			vmml::Matrix3f normalMatrix;
			vmml::compute_inverse(vmml::transpose(vmml::Matrix3f(modelMatrix)), normalMatrix);
			shader->setUniform("NormalMatrix", normalMatrix);

			shader->setUniform("LightDirection", lightDirection);
			shader->setUniform("DayNightPulse", dayNightPulse);

			shader->setUniform("TreeAnimation", treeAnimation);
		}
		//TheRenderer::Instance()->renderer->getModelRenderer()->queueModelInstance("car", "car" + std::to_string(gameObject->getId()), "camera", modelMatrix, std::vector<std::string>({ "firstLight"}), false, false, false);
		TheRenderer::Instance()->renderer->getModelRenderer()->drawModel("Tree", cameraName, modelMatrix, std::vector<std::string>({}));
	}
};

#endif /* defined(ASTEROID_RENDERER_H) */