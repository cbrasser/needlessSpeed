#ifndef TEST_SCENE_CPP
#define TEST_SCENE_CPP

#include "Scene.h"
#include "GameObject.h"
#include "Component.h"
#include "Logic.h"
#include "CarRenderer.cpp"
#include "TrackRenderer.cpp"
#include "WheelRenderer.cpp"
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

		//Car and Wheels
		GameObject *Car = instanciate("Car");
		Car->addComponent<CarRenderer>();
		Car->addComponent<SphereCollider>()->setRadius(1.2f);
		Car->getComponent<Transform>()->setPosition(vmml::Vector3f(0.f, 0.2f, 0.f));
		Car->addComponent<MoveScript>();
		
		GameObject *WheelLR = instanciate("WheelLR");
		WheelLR->addComponent<WheelRenderer>();
		WheelLR->getComponent<Transform>()->setParent(Car);
		WheelLR->getComponent<Transform>()->setPosition(vmml::Vector3f(0.65f, 0.2f, 1.32f));

		GameObject *WheelLF = instanciate("WheelLF");
		WheelLF->addComponent<WheelRenderer>();
		WheelLF->getComponent<Transform>()->setParent(Car);
		WheelLF->getComponent<Transform>()->setPosition(vmml::Vector3f(0.65f, 0.2f, -1.125f));

		GameObject *WheelRR = instanciate("WheelRR");
		WheelRR->addComponent<WheelRenderer>();
		WheelRR->getComponent<Transform>()->setParent(Car);
		WheelRR->getComponent<Transform>()->setRotation(vmml::Vector3f(0.f, 3.14159f, 0.f));
		WheelRR->getComponent<Transform>()->setPosition(vmml::Vector3f(-0.64f, 0.2f, 1.32f));

		GameObject *WheelRF = instanciate("WheelRF");
		WheelRF->addComponent<WheelRenderer>();
		WheelRF->getComponent<Transform>()->setParent(Car);
		WheelRF->getComponent<Transform>()->setRotation(vmml::Vector3f(0.f, 3.14159f, 0.f));
		WheelRF->getComponent<Transform>()->setPosition(vmml::Vector3f(-0.64f, 0.2f, -1.125f));

		//Environment
		GameObject *Track = instanciate("Track");
		Track->addComponent<TrackRenderer>();

		GameObject *Tree = instanciate("Tree");
		Tree->addComponent<TreeRenderer>();
		Tree->addComponent<SphereCollider>()->setRadius(1.1f);
		Tree->getComponent<Transform>()->setPosition(vmml::Vector3f(5.f, 0.f, 0.f));

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
