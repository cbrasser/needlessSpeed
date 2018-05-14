#ifndef TEST_SCENE_CPP
#define TEST_SCENE_CPP

#include "Scene.h"
#include "GameObject.h"
#include "Component.h"
#include "Logic.h"
#include "CarRenderer.cpp"
#include "TrackRenderer.cpp"
#include "MoveScript.cpp"
#include "Physics.h"
#include "FreeCameraScript.cpp"
#include "RotationScript.cpp"
#include "SphereCollider.cpp"
#include "ShipScript.cpp"
#include "MoveScript.cpp"
#include "LaserManager.cpp"
#include "LaserScript.cpp"
#include "StickToFrontScript.cpp"
#include "TreeRenderer.cpp"
#include "CameraWrapper.cpp"
#include "ParticleSystemRenderer.cpp"
#include "ParticleSystem.h"

class TestScene : public Scene {
public:
	void Load() {

		std::cout << "=========================" << std::endl;

		/*** Create Objects ***/
		GameObject *Car = instanciate("Car");
		Car->addComponent<CarRenderer>();
		Car->addComponent<MoveScript>();

		GameObject *Track = instanciate("Track");
		Track->addComponent<TrackRenderer>();

		GameObject *Tree = instanciate("Tree");
		Tree->addComponent<TreeRenderer>();

		//Particles
		GameObject *ParticleSystem = instanciate("ParticleSystem");
		ParticleSystem->addComponent<ParticleSystemRenderer>();
		ParticleSystem->getComponent<Transform>()->setPosition(vmml::Vector3f(0.f, 0.f, 0.f));
		ParticleSystem->getComponent<ParticleSystemRenderer>()->init();

		//Camera
		GameObject *Camera = instanciate("Camera");
		Camera->addComponent<FreeCameraScript>();	

		//GameObject *ShadowCamera = instanciate("Camera");
		//ShadowCamera->addComponent<FreeCameraScript>();
	}
};

#endif /* defined(TEST_SCENE_CPP) */
