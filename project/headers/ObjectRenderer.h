#ifndef OBJECT_RENDERER_H
#define OBJECT_RENDERER_H

#include "Component.h"
#include "TheRenderer.h"
#include "Core.h"

class ObjectRenderer : public Component{
public:
	ObjectRenderer();
	virtual void init() = 0;
	virtual void render(std::string cameraName,ShaderPtr customShader) = 0;
	virtual void onDestroy();
	void destroy();
};

#endif /* defined(OBJECT_RENDERER_H) */