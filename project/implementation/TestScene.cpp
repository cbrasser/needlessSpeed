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
#include "MoveScript.cpp"
#include "TreeRenderer.cpp"
#include "CameraWrapper.cpp"
#include "ParticleSystemRenderer.cpp"
#include "ParticleSystem.h"
#include "StartLineRenderer.cpp"
#include "UIRenderer.cpp"
#include "TirestackRenderer.cpp"
#include "ForestRenderer.cpp"

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


		//Track
		GameObject *Track = instanciate("Track");
		Track->getComponent<Transform>()->setScale(vmml::Vector3f(2.f, 2.f, 2.f));
		Track->getComponent<Transform>()->setPosition(vmml::Vector3f(0.f, 0.1f, 0.f));
		Track->addComponent<TrackRenderer>();


		//Environment
		GameObject *Forest = instanciate("Forest");
		Forest->getComponent<Transform>()->setScale(vmml::Vector3f(2.3f, 1.f, 2.3f));
		Forest->getComponent<Transform>()->setPosition(vmml::Vector3f(20.f, -0.5f, 8.f));
		Forest->addComponent<ForestRenderer>();

		GameObject *Forest2 = instanciate("Forest2");
		Forest2->getComponent<Transform>()->setScale(vmml::Vector3f(2.5f, 1.f, 2.5f));
		Forest2->getComponent<Transform>()->setPosition(vmml::Vector3f(20.f, -0.5f, 8.f));
		Forest2->addComponent<ForestRenderer>();

		GameObject *Tree = instanciate("Tree");
		Tree->getComponent<Transform>()->setScale(vmml::Vector3f(1.5f, 1.5f, 1.5f));
		Tree->addComponent<TreeRenderer>();
		Tree->addComponent<SphereCollider>()->setRadius(1.1f);
		Tree->getComponent<Transform>()->setPosition(vmml::Vector3f(5.f, 0.f, 0.f));

		GameObject *Tree2 = instanciate("Tree2");
		Tree2->getComponent<Transform>()->setScale(vmml::Vector3f(1.5f, 1.5f, 1.5f));
		Tree2->addComponent<TreeRenderer>();
		Tree2->addComponent<SphereCollider>()->setRadius(1.1f);
		Tree2->getComponent<Transform>()->setPosition(vmml::Vector3f(5.f, 0.f, 5.f));

		GameObject *Tirestack = instanciate("Tirestack");
		Tirestack->addComponent<TirestackRenderer>();
		//Tirestack->addComponent<SphereCollider>()->setRadius(1.1f); TO DO
		Tirestack->getComponent<Transform>()->setPosition(vmml::Vector3f(0.f, 0.f, 6.f));


		//Timing Markers
		GameObject *StartLine = instanciate("StartLine");
		StartLine->addComponent<StartLineRenderer>();
		StartLine->addComponent<SphereCollider>()->setRadius(1.f);
		StartLine->getComponent<Transform>()->setPosition(vmml::Vector3f(10.f, 0.f, 0.f));


		//Particles
		GameObject *ParticleSystem = instanciate("ParticleSystem");
		ParticleSystem->addComponent<ParticleSystemRenderer>();
		ParticleSystem->getComponent<Transform>()->setPosition(vmml::Vector3f(0.f, 0.f, 0.f));
		ParticleSystem->getComponent<ParticleSystemRenderer>()->init();


		//Camera
		GameObject *Camera = instanciate("Camera");
		Camera->addComponent<FreeCameraScript>();	

		GameObject *ShadowCamera = instanciate("Camera");
		//ShadowCamera->addComponent<FreeCameraScript>();


		//UI
		GameObject *UI = instanciate("UI");
		UI->addComponent<UIRenderer>();

	}
};

#endif /* defined(TEST_SCENE_CPP) */
