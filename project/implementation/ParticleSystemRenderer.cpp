#ifndef PARTICLE_SYSTEM_RENDERER_H
#define PARTICLE_SYSTEM_RENDERER_H

#include "Core.h"
#include "ObjectRenderer.h"
#include "GameObject.h"
#include "TheRenderer.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include "TheTime.h"

class ParticleSystemRenderer : public ObjectRenderer {
public:
	ParticleSystem* particleSystem = new ParticleSystem;

	float pi = 3.1414f;
	float frequency = 3.0f;
	GLfloat dayNightPulse = 0.0f;
	TheTime theTime;

//	GLint lastG; // Keyboard Input
    
    void init() override {

		particleSystem->Start();

        if (TheRenderer::Instance()->renderer->getObjects()->getModel("quad") == nullptr) {
			ShaderPtr spriteShader = TheRenderer::Instance()->renderer->getObjects()->loadShaderFile("sprite", 0, false, false, false, false, false);
		
			TheRenderer::Instance()->renderer->getObjects()->loadTexture("dirtSprite.png");

			TheRenderer::Instance()->renderer->getObjects()->loadObjModel("quad.obj", false, true, spriteShader);
        }
	}
    
	void render(std::string cameraName, ShaderPtr customShader) override {

        // Keyboard and touch inputs for testing purposes
//		GLint currentG = TheRenderer::Instance()->renderer->getInput()->getKeyState(bRenderer::KEY_G);
//		if (currentG != lastG) {
//			lastG = currentG;
//			if (currentG == bRenderer::INPUT_PRESS) {
//				particleSystem->activate();
//			}
//		}
        
        // Touch input
//        TouchMap touchMap = TheRenderer::Instance()->renderer->getInput()->getTouches();
//
//        for (auto t = touchMap.begin(); t != touchMap.end(); ++t)
//        {
//            Touch touch = t->second;
//            // If touch is in left half of the view: move around
//            if (touch.startPositionX < TheRenderer::Instance()->renderer->getView()->getWidth() / 2) {
//                particleSystem->activate();
//                
//            }
//
//        }

		ShaderPtr spriteShader;
		if(customShader == nullptr){
			spriteShader = TheRenderer::Instance()->renderer->getObjects()->getShader("sprite");
		} else {
			spriteShader = customShader;
		}
        
		//ShaderPtr spriteShader = TheRenderer::Instance()->renderer->getObjects()->getShader("sprite");

		TexturePtr texturePtr = TheRenderer::Instance()->renderer->getObjects()->getTexture("dirtSprite");
		TexturePtr colorLUT = TheRenderer::Instance()->renderer->getObjects()->getTexture("colorLUT");

		for (int i = 0; i < particleSystem->numOfParticles; i++) {
			dayNightPulse = 0.5*(1 + cos(theTime.time / frequency));

			spriteShader->setUniform("DiffuseMapNew", texturePtr);
			spriteShader->setUniform("DayNightPulse", dayNightPulse);
			spriteShader->setUniform("ColorLUT", colorLUT);
		}
        
       // if ( !particleSystem->isDone) { // not all particles are dead
		if (true) { // not all particles are dead

			vmml::Vector3f actualPosition = gameObject->getComponent<Transform>()->getPosition();

			vmml::Matrix4f bringToOrigin = vmml::create_translation(-actualPosition);
			vmml::Matrix4f moveBackToPosition = vmml::create_translation(actualPosition);

			for (int i = 0; i < particleSystem->numOfParticles; i++) {

				if (particleSystem->particleArray[i]->isAlive) {

					// needed vectors for calculations
					vmml::Vector3f cameraRight = TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->getRight();
					vmml::Vector3f cameraUp = TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->getUp();
					vmml::Vector3f cameraForward = TheRenderer::Instance()->renderer->getObjects()->getCamera("camera")->getForward();

					// startingAngle, points the tip of the flame always away from camera
					vmml::Vector3f cameraForwardProjectedOnXZPlane = cameraForward;
					cameraForwardProjectedOnXZPlane.y() = 0;
					cameraForwardProjectedOnXZPlane = normalize(cameraForwardProjectedOnXZPlane);
					float startingAngle = -std::acos(vmml::dot(vmml::Vector3f(0, 0, -1), cameraForwardProjectedOnXZPlane));
					if (cameraForward.x() < 0) { // Quadrant checking for startingAngle
						startingAngle = -startingAngle;
					}
					startingAngle += M_PI;

					// cameraAngle, points the quad towards the camera
					float cameraAngle = std::acos(vmml::dot(cameraUp, vmml::Vector3f(0, 1, 0))) - M_PI_2_F;
					if (cameraForward.y() > 0) { // quadrant checking for cameraAngle
						cameraAngle = -cameraAngle + M_PI;
					}

					// centerAngle, points the tip of the flame to the center of the particleSystem
					vmml::Vector3f flatDirection = particleSystem->particleArray[i]->direction; // Flat direction is going to be the direction flattened on the camera plane.
					flatDirection = normalize(flatDirection - cameraForward * vmml::dot(flatDirection, cameraForward)); //projects flatDirection on the camera plane
					float centerAngle = std::acos(vmml::dot(cameraUp, flatDirection));
					if (vmml::dot(cameraRight, flatDirection) > 0) { // quadrant checking for centerAngle
						centerAngle = -centerAngle;
					}
					centerAngle += M_PI; // remove this line if you want to flip the quad (have the flame pointing inwards)
					if (cameraUp.y() < 0) { // corrected orientation for when it is upside down
						centerAngle -= M_PI;
					}

					// Quads start on the xz plane pointing up, and the flame texture is pointing the negative-z axis

					// First rotate the quads with respect to the camera forward vector so that the flame points away from the camera at all times.
					vmml::Matrix4f startingRotation = vmml::create_rotation(startingAngle, vmml::Vector3f(0, 1, 0)); // turns quads toward the camera.
					// Then rotate the quad so that it is at all times toward the camera.
					vmml::Matrix4f cameraRotation = vmml::create_rotation(cameraAngle, cameraRight); // turns quads toward the camera.
					// Lastly rotate the quad to point towards the center of the particle system.
					vmml::Matrix4f centerRotation = vmml::create_rotation(centerAngle, cameraForward); // turns quads by radially pointing them to the center of the particle system.

					vmml::Matrix4f translation = vmml::create_translation(particleSystem->particleArray[i]->position); // positions quads in the correct place defined py pthe particle system.

					//logarithmic size based on timetolive
					vmml::Matrix4f scale = vmml::create_scaling(particleSystem->particleArray[i]->size * 2);
                    
                    vmml::Matrix4f modelMatrix = gameObject->getComponent<Transform>()->getTransformationMatrix(); // Luka please leave this line here and not out of the loop otherwise the whole explosionRender does not work properly anymore, cheers Silvo.
					modelMatrix = moveBackToPosition*translation*centerRotation*cameraRotation*startingRotation *scale*bringToOrigin*modelMatrix;


					vmml::Matrix4f view = TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getViewMatrix();
					vmml::Matrix4f projection = TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getProjectionMatrix();

					vmml::Matrix4f modelViewMatrix = view*modelMatrix;
                    
					TheRenderer::Instance()->renderer->getModelRenderer()->queueModelInstance("quad", "quad_" + std::to_string(i + 1), cameraName, modelMatrix, std::vector<std::string>({}), false, false, true, GL_SRC_COLOR, GL_ONE);
				}
				else {}; // do nothing because particle is not alive anymore
			}
			particleSystem->Update();
		}
	}
	void onDestroy() override {
		particleSystem->Destroy();
		delete particleSystem;
	};

};

#endif /* defined(PARTICLE_SYSTEM_H) */
