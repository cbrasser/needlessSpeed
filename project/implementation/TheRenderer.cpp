#include <iostream>
#include "TheRenderer.h"
#include "Core.h"
#include "ObjectRenderer.h"

TheRenderer* TheRenderer::instance;
std::vector<ObjectRenderer*> TheRenderer::renderQueue;


void TheRenderer::addToRenderQueue(ObjectRenderer *objectRenderer) {
	renderQueue.push_back(objectRenderer);
}

void TheRenderer::removeFromRenderQueue(ObjectRenderer *objectRenderer) {
	renderQueue.erase(std::remove(renderQueue.begin(), renderQueue.end(), objectRenderer), renderQueue.end());
}

void TheRenderer::init() {
	for (std::vector<ObjectRenderer*>::iterator it = renderQueue.begin(); it != renderQueue.end(); ++it) {
		(*it)->init();
	}
}

void TheRenderer::render() {
	for (std::vector<ObjectRenderer*>::iterator it = renderQueue.begin(); it != renderQueue.end(); ++it) {
		if ((*it)->getEnable())
			(*it)->render();
	}

	renderer->getModelRenderer()->drawQueue(/*GL_LINES*/);
	renderer->getModelRenderer()->clearQueue();
}

void TheRenderer::destroy() {
	renderQueue.clear();
}

TheRenderer* TheRenderer::Instance() {
	return instance;
}

void TheRenderer::printList(){
	for (std::vector<ObjectRenderer*>::iterator it = renderQueue.begin(); it != renderQueue.end(); ++it) {
		std::cout << (*it)->getName() << std::endl;
	}
}