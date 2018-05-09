#ifndef POST_PROCESSING_H
#define POST_PROCESSING_H

#include "TheRenderer.h"
#include "Core.h"

class PostProcessing {
public:
	static void init();
	static void preProcess();
	static void postProcess();
	
private:
	static GLint defaultFBO;
	static vmml::Matrix4f modelMatrix;
	static vmml::Matrix4f _viewMatrixHUD;

	static MaterialPtr cutOffMaterial;
	static MaterialPtr blurMaterial;
	static MaterialPtr additivMaterial;

	static ModelPtr cutOffSprite;
	static ModelPtr blurSprite;
	static ModelPtr additivSprite;

	static TexturePtr fbo_original;
	static TexturePtr fbo_texture1;
	static TexturePtr fbo_texture2;
	static TexturePtr fbo_blured;
    static TexturePtr lens_dirt;


	static ObjectManagerPtr objectManager;
};

#endif /* defined(POST_PROCESSING_H) */
