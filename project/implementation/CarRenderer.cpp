#ifndef CAR_RENDERER_H
#define CAR_RENDERER_H

#include "Core.h"
#include "ObjectRenderer.h"
#include "GameObject.h"
#include "TheRenderer.h"
#include "LightWrapper.cpp"


class CarRenderer : public ObjectRenderer {
public:

	void init() override {
		if (TheRenderer::Instance()->renderer->getObjects()->getModel("car") == nullptr) {
            std::cout << "============init car renderer=============" << std::endl;
            // Use flat shader
            ShaderPtr carShader = TheRenderer::Instance()->renderer->getObjects()->loadShaderFile("car", 0, false, false, false, false, false);
            TheRenderer::Instance()->renderer->getObjects()->loadObjModel("car.obj", false, true, carShader, nullptr);
		}
	}

	void render() override {
		std::cout << "============render car renderer=============" << std::endl;

		vmml::Matrix4f modelMatrix = gameObject->getComponent<Transform>()->getTransformationMatrix();
        TexturePtr carLUT = TheRenderer::Instance()->renderer->getObjects()->getTexture("colorLUT");

		ShaderPtr shader = TheRenderer::Instance()->renderer->getObjects()->getShader("car");
		vmml::Matrix4f viewMatrix = TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->getViewMatrix();
		if (shader.get())
	{
		shader->setUniform("ProjectionMatrix", vmml::Matrix4f::IDENTITY);
		shader->setUniform("ViewMatrix", viewMatrix);
		shader->setUniform("ModelMatrix", modelMatrix);
		shader->setUniform("ColorLUT", carLUT);
		
		vmml::Matrix3f normalMatrix;
		vmml::compute_inverse(vmml::transpose(vmml::Matrix3f(modelMatrix)), normalMatrix);
		shader->setUniform("NormalMatrix", normalMatrix);

		vmml::Vector4f eyePos = vmml::Vector4f(0.0f, 0.0f, 10.0f, 1.0f);
		shader->setUniform("EyePos", eyePos);

		shader->setUniform("LightPos", vmml::Vector4f(1.f, 1.f, 1.f, 1.f));
	}
        //TheRenderer::Instance()->renderer->getModelRenderer()->queueModelInstance("car", "car" + std::to_string(gameObject->getId()), "camera", modelMatrix, std::vector<std::string>({ "firstLight"}), false, false, false);
    	TheRenderer::Instance()->renderer->getModelRenderer()->drawModel("car", "camera", modelMatrix, std::vector<std::string>({ }));
    }
};

#endif /* defined(ASTEROID_RENDERER_H) */