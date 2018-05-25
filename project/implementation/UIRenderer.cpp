#ifndef UI_RENDERER_H
#define UI_RENDERER_H

#include "Core.h"
#include "ObjectRenderer.h"
#include "GameObject.h"
#include "TheRenderer.h"


//Values for the lap times
static double UItotalLapTime = 999999.0;
static double UIbestLapTime = 999999.0;

class UIRenderer : public ObjectRenderer {
public:

	//Values for the lap times
	//static double UItotalLapTime = 999999.0;
	//static double UIbestLapTime = 999999.0;

	void init() override {
		if (TheRenderer::Instance()->renderer->getObjects()->getTextSprite("Lap Timer") == nullptr) {
		
			// create text sprites for lap timer
			FontPtr font = TheRenderer::Instance()->renderer->getObjects()->loadFont("nfs.ttf", 50);
			TheRenderer::Instance()->renderer->getObjects()->createTextSprite("Lap Timer", vmml::Vector3f(1.f, 1.f, 1.f), "temp", font);
		}
	}

	void render(std::string cameraName) override {

		float titleScale = 0.08f;
		vmml::Matrix4f scaling = vmml::create_scaling(vmml::Vector3f(titleScale / TheRenderer::Instance()->renderer->getView()->getAspectRatio(), titleScale, titleScale));
		vmml::Matrix4f uiModelMatrix = vmml::create_translation(vmml::Vector3f(-0.98f, 0.8f, -0.65f)) * scaling;
		if (UItotalLapTime == 999999.0) {
			TheRenderer::Instance()->renderer->getObjects()->getTextSprite("Lap Timer")->setText(
				"NEEDLESS SPEED \nLast Lap Time: No lap driven yet \nBest Lap Time: No lap driven yet \n"
			);
		}
		else {
			TheRenderer::Instance()->renderer->getObjects()->getTextSprite("Lap Timer")->setText(
				"NEEDLESS SPEED \nLast Lap Time: " + std::to_string(UItotalLapTime) + "\n" +
				"Best Lap Time: " + std::to_string(UIbestLapTime) + "\n"
			);
		}
		TheRenderer::Instance()->renderer->getModelRenderer()->drawModel(TheRenderer::Instance()->renderer->getObjects()->getTextSprite("Lap Timer"), uiModelMatrix, Camera::lookAt(vmml::Vector3f(0.0f, 0.0f, 0.25f), vmml::Vector3f::ZERO, vmml::Vector3f::UP), vmml::Matrix4f::IDENTITY, std::vector<std::string>({}), false);

	}
};

#endif /* defined(UI_RENDERER_H) */