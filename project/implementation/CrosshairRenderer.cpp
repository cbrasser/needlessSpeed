#ifndef CROSSHAIR_RENDERER_H
#define CROSSHAIR_RENDERER_H

#include "Core.h"
#include "ObjectRenderer.h"
#include "GameObject.h"
#include "TheRenderer.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CameraMovementScript.cpp"


class CrosshairRenderer : public ObjectRenderer {
public:
    float pitchAngle;
    float rollAngle;
    vmml::Vector3f camForwardDirection;
    vmml::Vector3f camRightDirection;
    vmml::Vector3f camUpDirection;

    
    void init() override {

		if (TheRenderer::Instance()->renderer->getObjects()->getModel("quadCross") == nullptr) {
			ShaderPtr crossShader = TheRenderer::Instance()->renderer->getObjects()->loadShaderFile("cross", 0, false, false, false, false, false);

			ModelPtr model = TheRenderer::Instance()->renderer->getObjects()->loadObjModel("quadCross.obj", false, true, crossShader);
		}

	}
    
	void render(std::string cameraName) override {
		ShaderPtr crossShader = TheRenderer::Instance()->renderer->getObjects()->getShader("cross");

		vmml::Matrix4f shipModelMatrix = gameObject->getComponent<Transform>()->getTransformationMatrix();
        
        vmml::Vector3f shipPos = gameObject->getComponent<Transform>()->getPosition();
        
        vmml::Vector3f shipDirection;
        shipDirection.x() = shipModelMatrix[0][2];
        shipDirection.y() = shipModelMatrix[1][2];
        shipDirection.z() = shipModelMatrix[2][2];
    
        vmml::Matrix4f quadModelMatrix = vmml::Matrix4f::IDENTITY;
        
        // Make the crosshair move accordingly to the pitch and roll of the camera
        GameObject *Cam = SceneManager::getCurrentScene()->getObjectByName("Camera");
        pitchAngle = Cam->getComponent<CameraMovementScript>()->pitch;
        rollAngle = Cam->getComponent<CameraMovementScript>()->roll;
        camForwardDirection = -TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getForward();
        camRightDirection = TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getRight();
        camUpDirection = TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getUp();

        vmml::Matrix4f pitchRotation = vmml::create_rotation(pitchAngle/2, camForwardDirection);
        
        vmml::Matrix4f rollRotation = vmml::create_rotation(rollAngle/2, camRightDirection);
        
		vmml::Matrix4f view = TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getViewMatrix();
		vmml::Matrix4f projection = TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getProjectionMatrix();

        float distanceFactor= 1000.0;
        
        shipDirection = rollRotation * pitchRotation * shipDirection;

        vmml::Vector3f shootPoint = shipPos + shipDirection * distanceFactor;
        
		vmml::Vector2f crosshairScreenPos = toScreenCoords(shootPoint,projection,view);
        
        vmml::Matrix4f translation = vmml::create_translation(vmml::Vector3f(crosshairScreenPos, -0.6)); //translate with z =-0.65 so that the quad is actually in front of the camera.
        vmml::Matrix4f rotateTowardsCamera = vmml::create_rotation(float(-M_PI_2_F), vmml::Vector3f(1.0, 0, 0)); //rotate quad because it is flat on xz axis
        vmml::Matrix4f scale = vmml::create_scaling(0.2);
        float viewPortHeight = TheRenderer::Instance()->renderer->getView()->getViewportHeight();
        float viewPortWidth = TheRenderer::Instance()->renderer->getView()->getViewportWidth();
        float factor = viewPortHeight / viewPortWidth;
        vmml::Matrix4f correctionScale = vmml::create_scaling(vmml::Vector3f(factor, 1, 1));
        
        quadModelMatrix = translation*correctionScale*rotateTowardsCamera*scale;
        vmml::Matrix4f quadViewMatrix = Camera::lookAt(vmml::Vector3f(0.0f, 0.0f, 0.25f), vmml::Vector3f::ZERO, vmml::Vector3f::UP);
        
        TheRenderer::Instance()->renderer->getModelRenderer()->queueModelInstance(TheRenderer::Instance()->renderer->getObjects()->getModel("quadCross"), "crosshair", quadModelMatrix, quadViewMatrix, vmml::Matrix4f::IDENTITY, std::vector<std::string>({}), false, false, true, GL_SRC_COLOR, GL_ONE);
	
	}
	void onDestroy() override {
	};

	vmml::Vector2f toScreenCoords(vmml::Vector3f point, vmml::Matrix4f projectionMatrix, vmml::Matrix4f viewMatrix) {
		vmml::Vector4f clipSpacePos = projectionMatrix * (viewMatrix * vmml::Vector4f(point, 1.0));
		if (clipSpacePos.w() == 0) {
			clipSpacePos.w() = 0.0001;
		}
		return vmml::Vector2f(clipSpacePos.x() / clipSpacePos.w(), clipSpacePos.y() / clipSpacePos.w());
	}
};

#endif /* defined(CROSSHAIR_RENDERER_H) */
