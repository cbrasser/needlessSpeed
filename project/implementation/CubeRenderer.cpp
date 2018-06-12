#ifndef CUBE_RENDERER_H
#define CUBE_RENDERER_H

#include "Core.h"
#include "ObjectRenderer.h"
#include "GameObject.h"
#include "TheRenderer.h"

class CubeRenderer : public ObjectRenderer {
public:
    
    void init() override {
        
        if (TheRenderer::Instance()->renderer->getObjects()->getModel("cube") == nullptr) {
            
            // Load the shader to render the cube for the skybox
            ShaderPtr skyShader = TheRenderer::Instance()->renderer->getObjects()->loadShaderFile("sky", 0, false, false, false, false, false);
            
            // Load cube model
            TheRenderer::Instance()->renderer->getObjects()->loadObjModel("cube.obj", false, false, skyShader);
            
            // Load the images for the cubemap

			TextureData skyL = TextureData("skybox3/skybox3X+.png");
			TextureData skyR = TextureData("skybox3/skybox3X-.png");
			TextureData skyB = TextureData("skybox3/skybox3Y-.png");
			TextureData skyT = TextureData("skybox3/skybox3Y+.png");
			TextureData skyF = TextureData("skybox3/skybox3Z+.png");
			TextureData skyBack = TextureData("skybox3/skybox3Z-.png");

            // Put the 6 textures into a vector (in the following order: left, right, bottom, top, front, back)
            std::vector<TextureData> skyImages;
            skyImages.push_back(skyR);
            skyImages.push_back(skyL);
            skyImages.push_back(skyT);
            skyImages.push_back(skyB);
            skyImages.push_back(skyF);
            skyImages.push_back(skyBack);
            
            // Create the cupemap
            CubeMapPtr skybox = TheRenderer::Instance()->renderer->getObjects()->createCubeMap("skybox", skyImages);
            
        }
    }
    
	void render(std::string cameraName, ShaderPtr customShader) override {

        ShaderPtr shader;
        if(customShader == nullptr){
            shader = TheRenderer::Instance()->renderer->getObjects()->getShader("sky");
        } else {
            shader = customShader;
        }
    
        vmml::Matrix4f modelMatrix = gameObject->getComponent<Transform>()->getTransformationMatrix();
        
        vmml::Vector3f originalCamPos = TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getPosition();
        
        // Temporarily bring camera to origin
        TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->setPosition(vmml::Vector3f(0.0f));
        
        // Update position of skybox as camera moves
        gameObject->getComponent<Transform>()->setPosition(TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getPosition());

        //ShaderPtr shader = TheRenderer::Instance()->renderer->getObjects()->getShader("sky");
        
        // Keep the camera centered in the skybox by setting the last column of the view matrix to zero so that
        // the skybox can still rotate with the camera but it is not traslated anymore
        vmml::Matrix4f view = TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->getViewMatrix();
        
        CubeMapPtr skybox = TheRenderer::Instance()->renderer->getObjects()->getCubeMap("skybox");
        
        if (shader.get()){
            
            //.vert uniforms
            shader->setUniform("ModelMatrix", modelMatrix);
            shader->setUniform("ViewMatrix", view);
            
            // .frag uniforms
            shader->setUniform("CubeMap", skybox);
        }
        
        // Put skybox in the render queue

		glDisable(GL_DEPTH_TEST);
        TheRenderer::Instance()->renderer->getModelRenderer()->drawModel("cube", cameraName, modelMatrix, std::vector<std::string>({}), false);
		glEnable(GL_DEPTH_TEST);
        
        // After drawing the skybox, bring the camera back to its original position
        // Thanks to this camera "shifting", it's impossible to leave to skybox
        TheRenderer::Instance()->renderer->getObjects()->getCamera(cameraName)->setPosition(originalCamPos);
    }
};

#endif /* defined(CUBE_RENDERER_H) */
