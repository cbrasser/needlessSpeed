#ifndef TRACK_RENDERER_H
#define TRACK_RENDERER_H

#include "Core.h"
#include "ObjectRenderer.h"
#include "GameObject.h"
#include "TheRenderer.h"
#include "LightWrapper.cpp"
#include "TheTime.h"

class TrackRenderer : public ObjectRenderer {
public:

	float pi = 3.1414f;
	float frequency = 3.0f;
	GLfloat dayNightPulse = 0.0f;
	vmml::Vector3f lightDirection = vmml::Vector3f(1.f, 1.f, 1.f);
	GLfloat directionFloat = 0.0f;
	TheTime theTime;



	void init() override {
		if (TheRenderer::Instance()->renderer->getObjects()->getModel("TrackFinal") == nullptr) {
          
            ShaderPtr generalShader = TheRenderer::Instance()->renderer->getObjects()->loadShaderFile("general", 0, false, false, false, false, false);
            TheRenderer::Instance()->renderer->getObjects()->loadObjModel("TrackFinal.obj", false, true, generalShader, nullptr);
		}
	}

	void render(std::string cameraName, ShaderPtr customShader) override {

		ShaderPtr shader = TheRenderer::Instance()->renderer->getObjects()->getShader("general");
		if(customShader == nullptr){
			shader->setUniform("shadow",0.0);
		} else {
			shader->setUniform("shadow",1.0);
		}

		//shadow stuff
		vmml::Matrix4f lightViewMatrix = TheRenderer::Instance()->renderer->getObjects()->getCamera("shadowCamera")->getViewMatrix();
		vmml::Matrix4f lightProjectionMatrix = TheRenderer::Instance()->renderer->getObjects()->getCamera("shadowCamera")->getProjectionMatrix();
		vmml::Matrix4f lightSpaceMatrix = lightProjectionMatrix * lightViewMatrix;


		vmml::Matrix4f modelMatrix = gameObject->getComponent<Transform>()->getTransformationMatrix();
        TexturePtr colorLUT = TheRenderer::Instance()->renderer->getObjects()->getTexture("colorLUT");
		vmml::Matrix4f viewMatrix = TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getViewMatrix();
		vmml::Matrix4f projectionMatrix = TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getProjectionMatrix();

		
		
		//Light Calculations
		dayNightPulse = 0.5*(1 + cos(theTime.time / frequency));
		directionFloat = fmod(theTime.time, pi * 2 * frequency) / (pi * frequency) - 1;
		lightDirection = vmml::Vector3f((directionFloat * 2), 1.f, 0.f);

		if (shader.get())
	{
		shader->setUniform("shadowMap", TheRenderer::Instance()->renderer->getObjects()->getDepthMap("depthMap"));
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
	}
        //TheRenderer::Instance()->renderer->getModelRenderer()->queueModelInstance("car", "car" + std::to_string(gameObject->getId()), "camera", modelMatrix, std::vector<std::string>({ "firstLight"}), false, false, false);
    	TheRenderer::Instance()->renderer->getModelRenderer()->drawModel("TrackFinal", cameraName, modelMatrix, std::vector<std::string>({ }));
    }
};

#endif /* defined(TRACK_RENDERER_H) */
