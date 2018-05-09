#ifndef MAIN_MENU_RENDERER_CPP
#define MAIN_MENU_RENDERER_CPP

#include "../headers/Core.h"
#include "../headers/ObjectRenderer.h"
#include "../headers/GameObject.h"
#include "../headers/TheRenderer.h"

class MainMenuRenderer : public ObjectRenderer {
public:
	void init() override {

		if (TheRenderer::Instance()->renderer->getObjects()->getModel("quadMenu") == nullptr) {
			ShaderPtr menuShader = TheRenderer::Instance()->renderer->getObjects()->loadShaderFile("sprite", 0, false, false, false, false, false);

			TheRenderer::Instance()->renderer->getObjects()->loadTexture("menuscreen.png");

			TheRenderer::Instance()->renderer->getObjects()->loadObjModel("quadMenu.obj", false, true, menuShader);

		}
	}

	void render() override {

		ShaderPtr spriteShader = TheRenderer::Instance()->renderer->getObjects()->getShader("sprite");

		TexturePtr texturePtr = TheRenderer::Instance()->renderer->getObjects()->getTexture("menuscreen");
		spriteShader->setUniform("DiffuseMapNew", texturePtr);

		float viewPortHeight = TheRenderer::Instance()->renderer->getView()->getViewportHeight();
		float viewPortWidth = TheRenderer::Instance()->renderer->getView()->getViewportWidth();
		float factor = viewPortHeight / viewPortWidth;

		vmml::Matrix4f correctionScale = vmml::create_scaling(vmml::Vector3f(factor, 1, 1));
		vmml::Matrix4f rotateTowardsCamera = vmml::create_rotation(float(-M_PI_2_F), vmml::Vector3f(1.0, 0, 0)); //rotate quad because it is flat on xz axis when loaded

		vmml::Matrix4f translation = vmml::create_translation(vmml::Vector3f(0, 0, 0.65)); //translate with z =-0.65 so that the quad is actually in front of the camera.

		vmml::Matrix4f scale = vmml::create_scaling(2);

		vmml::Matrix4f modelMatrix = translation*rotateTowardsCamera*scale;
		vmml::Matrix4f viewMatrix = Camera::lookAt(vmml::Vector3f(0.0f, 0.0f, 0.65f), vmml::Vector3f::ZERO, vmml::Vector3f::UP);

		TheRenderer::Instance()->renderer->getModelRenderer()->queueModelInstance(TheRenderer::Instance()->renderer->getObjects()->getModel("quadMenu"), "quadMenu", modelMatrix, viewMatrix, vmml::Matrix4f::IDENTITY, std::vector<std::string>({}));
	}
};

#endif /* defined(MAIN_MENU_RENDERER_CPP) */
