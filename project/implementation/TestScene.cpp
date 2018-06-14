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
		GameObject *Tree[54];
		// Instanciate trees
		for (int i = 0; i < 54; i++) {
			Tree[i] = instanciate("Tree" + std::to_string(i));
			Tree[i]->getComponent<Transform>()->setScale(vmml::Vector3f(3.5f, 3.5f, 3.5f));
			Tree[i]->addComponent<TreeRenderer>();
			Tree[i]->addComponent<SphereCollider>()->setRadius(1.1f);
		}
		
		// Trees inside the track
		for (int j = 0; j < 30; j++) {
			float x = (float(rand() % 1000) / 1000) * 91 - 46;
			float z = (float(rand() % 1000) / 1000) * 102 - 144;
			Tree[j]->getComponent<Transform>()->setPosition(vmml::Vector3f(x, 0.f, z));
		}

		Tree[30]->getComponent<Transform>()->setPosition(vmml::Vector3f(58.33f, 0.f, -39.485f));
		Tree[31]->getComponent<Transform>()->setPosition(vmml::Vector3f(68.04f, 0.f, -40.78f));
		Tree[32]->getComponent<Transform>()->setPosition(vmml::Vector3f(76.136f, 0.f, -46.865f));
		Tree[33]->getComponent<Transform>()->setPosition(vmml::Vector3f(28.13f, 0.f, -161.12f));
		Tree[34]->getComponent<Transform>()->setPosition(vmml::Vector3f(13.48f, 0.f, -170.74f));
		Tree[35]->getComponent<Transform>()->setPosition(vmml::Vector3f(-16.06f, 0.f, -169.94f));
		Tree[36]->getComponent<Transform>()->setPosition(vmml::Vector3f(-31.19f, 0.f, -167.2f));
		Tree[37]->getComponent<Transform>()->setPosition(vmml::Vector3f(-47.4f, 0.f, -59.7f));
		Tree[38]->getComponent<Transform>()->setPosition(vmml::Vector3f(-74.63f, 0.f, -70.0f));
		Tree[39]->getComponent<Transform>()->setPosition(vmml::Vector3f(-79.5f, 0.f, -48.4f));
		Tree[40]->getComponent<Transform>()->setPosition(vmml::Vector3f(-75.28f, 0.f, -38.27f));
		Tree[41]->getComponent<Transform>()->setPosition(vmml::Vector3f(-55.13f, 0.f, -32.08f));
		Tree[42]->getComponent<Transform>()->setPosition(vmml::Vector3f(-18.83f, 0.f, -28.8f));
		Tree[43]->getComponent<Transform>()->setPosition(vmml::Vector3f(20.67f, 0.f, -32.9f));

		// Trees outside the track
		Tree[44]->getComponent<Transform>()->setPosition(vmml::Vector3f(-45.16f, 0.f, 18.7f));
		Tree[45]->getComponent<Transform>()->setPosition(vmml::Vector3f(-83.87f, 0.f, 21.83f));
		Tree[46]->getComponent<Transform>()->setPosition(vmml::Vector3f(-118.25f, 0.f, -25.7f));
		Tree[47]->getComponent<Transform>()->setPosition(vmml::Vector3f(-133.65f, 0.f, -93.78f));
		Tree[48]->getComponent<Transform>()->setPosition(vmml::Vector3f(-92.45f, 0.f, -175.18f));
		Tree[49]->getComponent<Transform>()->setPosition(vmml::Vector3f(-56.48f, 0.f, -218.9f));
		Tree[50]->getComponent<Transform>()->setPosition(vmml::Vector3f(71.69f, 0.f, -170.29f));
		Tree[51]->getComponent<Transform>()->setPosition(vmml::Vector3f(81.37f, 0.f, -103.16f));
		Tree[52]->getComponent<Transform>()->setPosition(vmml::Vector3f(87.0f, 0.f, -7.93f));
		Tree[53]->getComponent<Transform>()->setPosition(vmml::Vector3f(58.38f, 0.f, 4.9f));


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
		StartLine->getComponent<Transform>()->setPosition(vmml::Vector3f(25.42f, 0.f, -21.625f));


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
