#ifndef MAIN_MENU_SCENE
#define MAIN_MENU_SCENE

#include "Scene.h"
#include "GameObject.h"
#include "Component.h"
#include "Logic.h"
#include "AsteroidRenderer.cpp"
#include "ShipRenderer.cpp"
#include "MoveScript.cpp"
#include "Physics.h"
#include "FreeCameraScript.cpp"
#include "RotationScript.cpp"
#include "SphereCollider.cpp"
#include "ShipScript.cpp"
#include "MoveScript.cpp"
#include "CubeRenderer.cpp"
#include "ParticleSystemRenderer.cpp"
#include "ParticleSystem.h"
#include "MainMenuRenderer.cpp"

class MainMenuScene : public Scene {
public:
	void Load() {
		GameObject *QuadMenu = instanciate("QuadMenu");
		QuadMenu->addComponent<MainMenuRenderer>();
	}
};

#endif /* defined(MAIN_MENU_SCENE) */
