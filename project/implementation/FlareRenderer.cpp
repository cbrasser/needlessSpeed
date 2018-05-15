#ifndef FLARE_RENDERER_H
#define FLARE_RENDERER_H

#include "Core.h"
#include "ObjectRenderer.h"
#include "GameObject.h"
#include "TheRenderer.h"
#include "FlareManager.h"
#include "Flare.h"

class FlareRenderer : public ObjectRenderer {
public:
	FlareManager* flareManager = new FlareManager;
    
    void init() override {
		flareManager->Start();

		if (TheRenderer::Instance()->renderer->getObjects()->getModel("quadFlare") == nullptr) {
			ShaderPtr flareShader = TheRenderer::Instance()->renderer->getObjects()->loadShaderFile("flare", 0, false, false, false, false, false);

			TheRenderer::Instance()->renderer->getObjects()->loadTexture("lensFlare1.png");
			TheRenderer::Instance()->renderer->getObjects()->loadTexture("lensFlare2.png");
			TheRenderer::Instance()->renderer->getObjects()->loadTexture("lensFlare3.png");
			TheRenderer::Instance()->renderer->getObjects()->loadTexture("lensFlare4.png");
			TheRenderer::Instance()->renderer->getObjects()->loadTexture("lensFlare5.png");
			TheRenderer::Instance()->renderer->getObjects()->loadTexture("lensFlare6.png");
			TheRenderer::Instance()->renderer->getObjects()->loadTexture("lensFlare7.png");

			ModelPtr model = TheRenderer::Instance()->renderer->getObjects()->loadObjModel("quadFlare.obj", false, true, flareShader);

			model->addInstance("flare_1");
			model->addInstance("flare_2");
			model->addInstance("flare_3");
			model->addInstance("flare_4");
			model->addInstance("flare_5");
			model->addInstance("flare_6");
			model->addInstance("flare_7");
		}

	}
    
	void render(std::string cameraName) override {
		ShaderPtr flareShader = TheRenderer::Instance()->renderer->getObjects()->getShader("flare");


		TexturePtr texturePtr1 = TheRenderer::Instance()->renderer->getObjects()->getTexture("lensFlare1");
		TexturePtr texturePtr2 = TheRenderer::Instance()->renderer->getObjects()->getTexture("lensFlare2");
		TexturePtr texturePtr3 = TheRenderer::Instance()->renderer->getObjects()->getTexture("lensFlare3");
		TexturePtr texturePtr4 = TheRenderer::Instance()->renderer->getObjects()->getTexture("lensFlare4");
		TexturePtr texturePtr5 = TheRenderer::Instance()->renderer->getObjects()->getTexture("lensFlare5");
		TexturePtr texturePtr6 = TheRenderer::Instance()->renderer->getObjects()->getTexture("lensFlare6");
        TexturePtr texturePtr7 = TheRenderer::Instance()->renderer->getObjects()->getTexture("lensFlare7");
            
        



		flareShader->setUniform("DiffuseMap1", texturePtr1);
		flareShader->setUniform("DiffuseMap2", texturePtr2);
		flareShader->setUniform("DiffuseMap3", texturePtr3);
		flareShader->setUniform("DiffuseMap4", texturePtr4);
		flareShader->setUniform("DiffuseMap5", texturePtr5);
		flareShader->setUniform("DiffuseMap6", texturePtr6);
		flareShader->setUniform("DiffuseMap7", texturePtr7);



		vmml::Vector3f actualPosition = gameObject->getComponent<Transform>()->getPosition();

		
		vmml::Matrix4f bringToOrigin = vmml::create_translation(-actualPosition);
		vmml::Matrix4f moveBackToPosition = vmml::create_translation(actualPosition);
		vmml::Matrix4f modelMatrix = gameObject->getComponent<Transform>()->getTransformationMatrix(); // Luka please leave this line here and not out of the loop otherwise the whole explosionRender does not work properly anymore, cheers Silvo.
		
		vmml::Vector3f cameraPosition = TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getPosition();
		vmml::Vector3f cameraRight = TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getRight();
		vmml::Vector3f cameraUp = TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getUp();
		vmml::Vector3f cameraForward = TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getForward();



		vmml::Matrix4f view = TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getViewMatrix();
		vmml::Matrix4f projection = TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getProjectionMatrix();

		vmml::Matrix4f modelViewMatrix = view*modelMatrix;


		vmml::Vector4f sunInWorldCoordinates = vmml::Vector4f(-500000, 20000,0,1); // INSERT SUN POSITION HERE
		
		vmml::Vector2f sunInScreenCoordinates = toScreenCoords(sunInWorldCoordinates,projection,view);


		flareManager->Update(sunInScreenCoordinates);

		flareShader->setUniform("transparencyFromCode", flareManager->transparency);

		// Need to rotate the model because the quad starts flat on the XZ plane.
		// Then we need to shrink it to match screen proportions.

		float forwardCheck = vmml::dot(cameraForward, vmml::Vector3f(sunInWorldCoordinates.x(), sunInWorldCoordinates.y(), sunInWorldCoordinates.z()) - cameraPosition);

//		if (forwardCheck > 0) {
			for (int i = 0; i < flareManager->numOfFlares; i++) {
				float centerAngle = acos(vmml::dot(normalize(sunInScreenCoordinates), vmml::Vector2f(0, 1)));
				if (sunInScreenCoordinates.x() > 0) { // Quadrant checking for centerAngle
					centerAngle = -centerAngle;
				}

                int s = 1;
                if (forwardCheck < 0) {
                    s = 0;
                }

                
				vmml::Matrix4f translation = vmml::create_translation(vmml::Vector3f(flareManager->flareArray[i]->position, -0.55 - 0.02*i)); //translate with z =-0.65 so that the quad is actually in front of the camera.
				vmml::Matrix4f rotateTowardsCamera = vmml::create_rotation(float(-M_PI_2_F), vmml::Vector3f(1.0, 0, 0)); //rotate quad because it is flat on xz axis
				vmml::Matrix4f rotateTowardsCenter = vmml::create_rotation(centerAngle, vmml::Vector3f(0, 0, 1.0)); // rotate quad to center it toward the sun
				vmml::Matrix4f scale = vmml::create_scaling(flareManager->flareArray[i]->scale*s);
				float viewPortHeight = TheRenderer::Instance()->renderer->getView()->getViewportHeight();
				float viewPortWidth = TheRenderer::Instance()->renderer->getView()->getViewportWidth();
				float factor = viewPortHeight / viewPortWidth;
				vmml::Matrix4f correctionScale = vmml::create_scaling(vmml::Vector3f(factor, 1, 1));

                
				vmml::Matrix4f flareModelMatrix = translation*correctionScale*rotateTowardsCenter*rotateTowardsCamera*scale;
				vmml::Matrix4f flareViewMatrix = Camera::lookAt(vmml::Vector3f(0.0f, 0.0f, 0.25f), vmml::Vector3f::ZERO, vmml::Vector3f::UP);
                

				ModelPtr model = TheRenderer::Instance()->renderer->getObjects()->getModel("quadFlare");

				Model::InstanceMapPtr instanceMap = model->getInstanceProperties("flare_" + std::to_string(i + 1));

				for (auto j = instanceMap->begin(); j != instanceMap->end(); ++j)
				{

					PropertiesPtr properties = j->second;

					properties->setScalar("textureToUse", (i + 1));
                    
				}
                
				TheRenderer::Instance()->renderer->getModelRenderer()->queueModelInstance(TheRenderer::Instance()->renderer->getObjects()->getModel("quadFlare"), "flare_" + std::to_string(i + 1), flareModelMatrix, flareViewMatrix, vmml::Matrix4f::IDENTITY, std::vector<std::string>({}), false, false, true, GL_SRC_COLOR, GL_ONE);


			}
//		}

	
	}
	void onDestroy() override {
		flareManager->Destroy();
		delete flareManager;
	};


	vmml::Vector2f toScreenCoords(vmml::Vector3f point, vmml::Matrix4f projectionMatrix, vmml::Matrix4f viewMatrix) {
		vmml::Vector4f clipSpacePos = projectionMatrix * (viewMatrix * vmml::Vector4f(point, 1.0));
		if (clipSpacePos.w() == 0) {
			clipSpacePos.w() = 0.0001;
		}
		return vmml::Vector2f(clipSpacePos.x() / clipSpacePos.w(), clipSpacePos.y() / clipSpacePos.w());
	}


};

#endif /* defined(FLARE_RENDERER_H) */
