#include "ObjectRenderer.h"
#include "TheRenderer.h"

ObjectRenderer::ObjectRenderer() {
	TheRenderer::addToRenderQueue(this);
}

void ObjectRenderer::onDestroy() {}

void ObjectRenderer::destroy(){
	onDestroy();
	TheRenderer::removeFromRenderQueue(this);
}
