#include "PostProcessing.h"

GLint PostProcessing::defaultFBO;
vmml::Matrix4f PostProcessing::modelMatrix;
vmml::Matrix4f PostProcessing::_viewMatrixHUD;

MaterialPtr PostProcessing::cutOffMaterial;
MaterialPtr PostProcessing::blurMaterial;
MaterialPtr PostProcessing::additivMaterial;

ModelPtr PostProcessing::cutOffSprite;
ModelPtr PostProcessing::blurSprite;
ModelPtr PostProcessing::additivSprite;

TexturePtr PostProcessing::fbo_original;
TexturePtr PostProcessing::fbo_texture1;
TexturePtr PostProcessing::fbo_texture2;
TexturePtr PostProcessing::fbo_blured;
TexturePtr PostProcessing::lens_dirt;

ObjectManagerPtr PostProcessing::objectManager;

void PostProcessing::init() {
	objectManager = TheRenderer::Instance()->renderer->getObjects();
	modelMatrix = vmml::create_translation(vmml::Vector3f(0.0f, 0.0f, -0.01f));
	_viewMatrixHUD = Camera::lookAt(vmml::Vector3f(0.0f, 0.0f, 0.25f), vmml::Vector3f::ZERO, vmml::Vector3f::UP);

	objectManager->createFramebuffer("fbo");
	fbo_original = objectManager->createTexture("fbo_original", 0.f, 0.f);
	fbo_texture1 = objectManager->createTexture("fbo_texture1", 0.f, 0.f);
	fbo_texture2 = objectManager->createTexture("fbo_texture2", 0.f, 0.f);
	fbo_blured = objectManager->createTexture("fbo_blured", 0.f, 0.f);
    lens_dirt = objectManager->loadTexture("lens_dirt.png");

	ShaderPtr cutOffShader = objectManager->loadShaderFile("cutOffShader", 0, false, false, false, false, false);			// load shader that blurs the texture
	cutOffMaterial = objectManager->createMaterial("cutOffMaterial", cutOffShader);								// create an empty material to assign either texture1 or texture2 to
	cutOffSprite = objectManager->createSprite("cutOffSprite", cutOffMaterial);																// create a sprite using the material created above

	ShaderPtr blurShader = objectManager->loadShaderFile("blurShader", 0, false, false, false, false, false);			// load shader that blurs the texture
	blurMaterial = objectManager->createMaterial("blurMaterial", blurShader);								// create an empty material to assign either texture1 or texture2 to
	blurSprite = objectManager->createSprite("blurSprite", blurMaterial);																// create a sprite using the material created above

	ShaderPtr additivShader = objectManager->loadShaderFile("additivShader", 0, false, false, false, false, false);			// load shader that blurs the texture
	additivMaterial = objectManager->createMaterial("additivMaterial", additivShader);								// create an empty material to assign either texture1 or texture2 to
	additivSprite = objectManager->createSprite("additivSprite", additivMaterial);
}

void PostProcessing::preProcess() {
	defaultFBO = Framebuffer::getCurrentFramebuffer();	// get current fbo to bind it again after drawing the scene
	objectManager->getFramebuffer("fbo")->bindTexture(fbo_original, false);	// bind the fbo
}

void PostProcessing::postProcess() {

	/*** CUTOF PROCESS ***/
	// Bind Buffer
	TheRenderer::Instance()->renderer->getView()->setViewportSize(TheRenderer::Instance()->renderer->getView()->getWidth() / 4, TheRenderer::Instance()->renderer->getView()->getHeight() / 4);
	objectManager->getFramebuffer("fbo")->bindTexture(fbo_texture1, false);
	// Set shader property
	cutOffMaterial->setTexture("fbo_texture", fbo_original);
	cutOffMaterial->setScalar("thresHold", static_cast<GLfloat>(0.8f));
	// Draw
	TheRenderer::Instance()->renderer->getModelRenderer()->drawModel(cutOffSprite, modelMatrix, _viewMatrixHUD, vmml::Matrix4f::IDENTITY, std::vector<std::string>({}), false);


	/*** BLUR PROCESS ***/
	bool b = true;
	int numberOfBlurSteps = 4;

	for (int i = 0; i < numberOfBlurSteps; i++) {
		if (i != numberOfBlurSteps - 1) {
			// Bind Buffer
			objectManager->getFramebuffer("fbo")->bindTexture(b ? fbo_texture2 : fbo_texture1, false);
		}
		else {
			// Bind Buffer
			objectManager->getFramebuffer("fbo")->bindTexture(fbo_blured, false);
		}
		// Set shader property
		blurMaterial->setTexture("fbo_texture", b ? fbo_texture1 : fbo_texture2);
		blurMaterial->setScalar("isVertical", static_cast<GLfloat>(b));

		// Draw
		TheRenderer::Instance()->renderer->getModelRenderer()->drawModel(blurSprite, modelMatrix, _viewMatrixHUD, vmml::Matrix4f::IDENTITY, std::vector<std::string>({}), false);
		b = !b;
	}



	/*** ADDITIV PROCESS ***/
	// Bind Buffer
	objectManager->getFramebuffer("fbo")->unbind(defaultFBO); //unbind (original fbo will be bound)
	TheRenderer::Instance()->renderer->getView()->setViewportSize(TheRenderer::Instance()->renderer->getView()->getWidth(), TheRenderer::Instance()->renderer->getView()->getHeight());
	// Set shader property
	additivMaterial->setTexture("fbo_original", fbo_original);
	additivMaterial->setTexture("fbo_blurTexture", fbo_blured);
    additivMaterial->setTexture("lens_dirt", lens_dirt);
	additivMaterial->setScalar("intensity", static_cast<GLfloat>(1.2f));
	additivMaterial->setScalar("dirtThresHold", static_cast<GLfloat>(0.1f));
	// Draw
	TheRenderer::Instance()->renderer->getModelRenderer()->drawModel(additivSprite, modelMatrix, _viewMatrixHUD, vmml::Matrix4f::IDENTITY, std::vector<std::string>({}), false);
}
