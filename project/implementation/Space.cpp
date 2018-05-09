#ifndef SPACE_HPP
#define SPACE_HPP

#include "Scene.h"
#include "GameObject.h"
#include "Component.h"
#include "Logic.h"
#include "AsteroidRenderer.cpp"
#include "ShipRenderer.cpp"
#include "MoveScript.cpp"
#include "Physics.h"
#include "CameraFollowScript.cpp"
#include "RotationScript.cpp"
#include "SphereCollider.cpp"
#include "ShipScript.cpp"
#include "MoveScript.cpp"
#include "CubeRenderer.cpp"
#include "ParticleSystemRenderer.cpp"
#include "ParticleSystem.h"
#include "FlareRenderer.cpp"
#include "FreeCameraScript.cpp"
#include "StickShipToCameraScript.cpp"
#include "CameraMovementScript.cpp"
#include "CameraWrapper.cpp"
#include "StickToFrontScript.cpp"
#include "LaserRenderer.cpp"
#include "LaserManager.cpp"
#include "LaserScript.cpp"
#include "BoostRenderer.cpp"
#include "CrosshairRenderer.cpp"
#include "LightWrapper.cpp"


class Space: public Scene {
public:
	
    void Load() override {
    }
    
    void Load(int asteroidAmount) override{
        
		// Uncomment this line to generate different random numbers every time the app is launched
        // srand (time(NULL));
        
        std::cout << "=========================" << std::endl;
		
		/*** Configure space ***/
		// SkyBox
		GameObject *SkyBox = instanciate("SkyBox");
		SkyBox->addComponent<CubeRenderer>();
		SkyBox->getComponent<Transform>()->setScale(vmml::Vector3f(100));

		/*** Create Objects ***/
		for (int i = 0; i < asteroidAmount; ++i) {
			GameObject *Asteroid = instanciate("Asteroid" + std::to_string(i));
			Asteroid->addComponent<AsteroidRenderer>();
			Asteroid->addComponent<RotationScript>();
            float randScale = (rand() % 500) / 10.0f + 10.0f; // safety check so that radius is never 0
            Asteroid->addComponent<SphereCollider>();
            Asteroid->getComponent<SphereCollider>()->setRadius(randScale * 1.2f + 15.0f); // enlarge collider since asteroids are not spherical
 			Asteroid->getComponent<Transform>()->setScale(vmml::Vector3f(randScale));
			Asteroid->getComponent<Transform>()->setPosition(vmml::Vector3f((rand() % 1400 - 700) * 5, (rand() % 1200 - 600) * 5, (rand() % 400 - 200) * 5));
		}

        GameObject *Camera = instanciate("Camera");
        Camera->addComponent<CameraMovementScript>();

		GameObject *Ship = instanciate("Ship");
		Ship->addComponent<ShipRenderer>();
		Ship->addComponent<SphereCollider>()->setRadius(8);
		Ship->addComponent<StickToFrontScript>();
        Ship->addComponent<LaserManager>();
        Ship->getComponent<Transform>()->setPosition(vmml::Vector3f(0, 0, 0));
        Ship->addComponent<CrosshairRenderer>();

		GameObject *Boost = instanciate("Boost");
		Boost->addComponent<BoostRenderer>();
		Boost->transform->setParent(Ship);
        Boost->getComponent<Transform>()->setPosition(vmml::Vector3f(0, 0, -0.5));


        int nrOfLasers = Ship->getComponent<LaserManager>()->numOfLasers;
        for (int i = 0; i < nrOfLasers; ++i) {
            GameObject *Laser = instanciate("Laser_"+std::to_string(i));
            Laser->isAlive = false;
            Laser->addComponent<LaserRenderer>();
            Laser->addComponent<LaserScript>();
            Laser->getComponent<LaserScript>()->setTimeToLive(0);
            Laser->addComponent<SphereCollider>();
            Laser->getComponent<SphereCollider>()->setRadius(5);
            //the renederers expect these lights, with these names!
            Laser->addComponent<LightWrapper>();
            Laser->getComponent<LightWrapper>()->createLight("laserLight"+std::to_string(i), 0.0f);
            Ship->getComponent<LaserManager>()->laserArray[i] = Laser;
            
        }
        
        // The object particle system must ALWAYS be created before the flare object !!!!
        GameObject *ParticleSystem = instanciate("ParticleSystem");
        ParticleSystem->addComponent<ParticleSystemRenderer>();
        
		GameObject *LensFlare = instanciate("LensFlare");
		LensFlare->addComponent<FlareRenderer>();
		LensFlare->getComponent<Transform>()->setPosition(vmml::Vector3f(0, 0, 0));


		std::cout << "=========================" << std::endl;
	}
};

#endif /* defined(SPACE_HPP) */
