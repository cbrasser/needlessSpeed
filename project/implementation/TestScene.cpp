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
		Car->getComponent<Transform>()->setRotation(vmml::Vector3f(0.f, 71.f, 0.f));
		Car->getComponent<Transform>()->setPosition(vmml::Vector3f(5.716f, 0.2f, -7.05f));
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

		//Trees
		GameObject *Tree[25];
		for (int i = 0; i < 25; i++) {
			Tree[i] = instanciate("Tree" + std::to_string(i));
			Tree[i]->getComponent<Transform>()->setScale(vmml::Vector3f(1.5f, 1.5f, 1.5f));
			Tree[i]->addComponent<TreeRenderer>();
			Tree[i]->addComponent<SphereCollider>()->setRadius(1.1f);
			float x = (float(rand() % 1000) / 1000) * 91 - 46;
			float z = (float(rand() % 1000) / 1000) * 102 - 144;
			Tree[i]->getComponent<Transform>()->setPosition(vmml::Vector3f(x, 0.f, z));
		}

		
		//Tirestacks
		GameObject *Tirestack[28];
		for (int i = 0; i < 28; i++) {
			Tirestack[i] = instanciate("Tirestack" + std::to_string(i));
			Tirestack[i]->addComponent<TirestackRenderer>();
			Tirestack[i]->addComponent<SphereCollider>()->setRadius(0.4f);
		}

		Tirestack[0]->getComponent<Transform>()->setPosition(vmml::Vector3f(-2.07f, 0.2f, -199.9f));
		Tirestack[1]->getComponent<Transform>()->setPosition(vmml::Vector3f(-2.07f, 0.2f, -201.4f));
		Tirestack[2]->getComponent<Transform>()->setPosition(vmml::Vector3f(-2.07f, 0.2f, -202.9f));
		Tirestack[3]->getComponent<Transform>()->setPosition(vmml::Vector3f(-2.07f, 0.2f, -204.4f));
		Tirestack[4]->getComponent<Transform>()->setPosition(vmml::Vector3f(-2.07f, 0.2f, -205.9f));
		Tirestack[5]->getComponent<Transform>()->setPosition(vmml::Vector3f(-24.07f, 0.2f, -192.3f));
		Tirestack[6]->getComponent<Transform>()->setPosition(vmml::Vector3f(-24.07f, 0.2f, -190.8f));
		Tirestack[7]->getComponent<Transform>()->setPosition(vmml::Vector3f(-24.07f, 0.2f, -189.3f));
		Tirestack[8]->getComponent<Transform>()->setPosition(vmml::Vector3f(-24.07f, 0.2f, -187.8f));
		Tirestack[9]->getComponent<Transform>()->setPosition(vmml::Vector3f(-24.07f, 0.2f, -186.3f));
		Tirestack[10]->getComponent<Transform>()->setPosition(vmml::Vector3f(83.3f, 0.2f, -38.05f));
		Tirestack[11]->getComponent<Transform>()->setPosition(vmml::Vector3f(85.3f, 0.2f, -45.72f));
		Tirestack[12]->getComponent<Transform>()->setPosition(vmml::Vector3f(82.3f, 0.2f, -53.37f));
		Tirestack[13]->getComponent<Transform>()->setPosition(vmml::Vector3f(72.95f, 0.2f, -64.98f));
		Tirestack[14]->getComponent<Transform>()->setPosition(vmml::Vector3f(34.26f, 0.2f, -192.17f));
		Tirestack[15]->getComponent<Transform>()->setPosition(vmml::Vector3f(34.26f, 0.2f, -192.17f));
		Tirestack[16]->getComponent<Transform>()->setPosition(vmml::Vector3f(-55.62f, 0.2f, -174.15f));
		Tirestack[17]->getComponent<Transform>()->setPosition(vmml::Vector3f(-77.03f, 0.2f, -135.66f));
		Tirestack[18]->getComponent<Transform>()->setPosition(vmml::Vector3f(-73.69f, 0.2f, -111.54f));
		Tirestack[19]->getComponent<Transform>()->setPosition(vmml::Vector3f(-88.82f, 0.2f, -99.45f));
		Tirestack[20]->getComponent<Transform>()->setPosition(vmml::Vector3f(-87.1f, 0.2f, -77.6f));
		Tirestack[21]->getComponent<Transform>()->setPosition(vmml::Vector3f(-90.79f, 0.2f, -71.42f));
		Tirestack[22]->getComponent<Transform>()->setPosition(vmml::Vector3f(-91.74f, 0.2f, -59.47f));
		Tirestack[23]->getComponent<Transform>()->setPosition(vmml::Vector3f(-89.85f, 0.2f, -48.65f));
		Tirestack[24]->getComponent<Transform>()->setPosition(vmml::Vector3f(-87.66f, 0.2f, -41.64f));
		Tirestack[25]->getComponent<Transform>()->setPosition(vmml::Vector3f(-80.83f, 0.2f, -32.29f));
		Tirestack[26]->getComponent<Transform>()->setPosition(vmml::Vector3f(-72.26f, 0.2f, -25.50f));
		Tirestack[27]->getComponent<Transform>()->setPosition(vmml::Vector3f(-60.50f, 0.2f, -20.07f));



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


		//UI
		GameObject *UI = instanciate("UI");
		UI->addComponent<UIRenderer>();

	}
};

#endif /* defined(TEST_SCENE_CPP) */
