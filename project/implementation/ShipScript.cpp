#ifndef SHIP_SCRIPT_H
#define SHIP_SCRIPT_H

#include "Core.h"
#include "Behaviour.h"
#include "TheTime.h"
#include "TheRenderer.h"

class ShipScript : public Behaviour {
private:
    vmml::Vector3f velocity;

public:
	float speedFalloff = 0.004f;
	float speed = 1.2f;
	float boost = 1.8f;
	double _mouseX, _mouseY;
	GLint _lastStateSpaceKey = bRenderer::INPUT_UNDEFINED;
	


	void Start() {
		velocity = vmml::Vector3f::ZERO;
	}
	
	void Update() {
		double deltaCameraY = 0.0;
		double deltaCameraX = 0.0;

		// mouse look
		double xpos, ypos; 
		bool hasCursor = false;
		TheRenderer::Instance()->renderer->getInput()->getCursorPosition(&xpos, &ypos, &hasCursor);

		deltaCameraY = (xpos - _mouseX) / 1000;
		_mouseX = xpos;
		deltaCameraX = (ypos - _mouseY) / 1000;
		_mouseY = ypos;

		// movement using wasd keys
		if (TheRenderer::Instance()->renderer->getInput()->getKeyState(bRenderer::KEY_F) == bRenderer::INPUT_PRESS) {
			if (TheRenderer::Instance()->renderer->getInput()->getKeyState(bRenderer::KEY_LEFT_SHIFT) == bRenderer::INPUT_PRESS)
				velocity += transform->forward() * (speed * boost * TheTime::deltaTime);
			else
				velocity += transform->forward() * (speed * TheTime::deltaTime);
		}
		
		if(velocity.length() > 0)
			velocity += velocity * -1 * speedFalloff;

		transform->setPosition(transform->getPosition() + velocity);
//		transform->setRotation(transform->getRotation() - vmml::Vector3f(deltaCameraX, deltaCameraY, 0.0f));
	}
};

#endif /* defined(SHIP_SCRIPT_H) */
