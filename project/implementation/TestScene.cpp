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

class TestScene : public Scene {
public:
	void Load() {

		std::cout << "=========================" << std::endl;

		/*** Create Objects ***/
		GameObject *Car = instanciate("Car");
		Car->addComponent<CarRenderer>();
		Car->addComponent<MoveScript>();

		GameObject *Tree = instanciate("Tree1");
		Tree -> addComponent<TreRenderer>();

		GameObject *Tree2 = instanciate("Tree2");
		Tree -> addComponent<TreRenderer>();

		GameObject *Track = instanciate("Track");
		Track->addComponent<TrackRenderer>();

		GameObject *Tree = instanciate("Tree");
		Tree->addComponent<TreeRenderer>();

		GameObject *Camera = instanciate("Camera");
		Camera->addComponent<FreeCameraScript>();	

	}
};

#endif /* defined(TEST_SCENE_CPP) */
