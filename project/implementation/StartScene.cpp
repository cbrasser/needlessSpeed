#ifndef START_SCENE
#define START_SCENE

#include "Scene.h"
#include "GameObject.h"
#include "Component.h"
#include "Logic.h"

#include "MoveScript.cpp"
#include "Physics.h"
#include "FreeCameraScript.cpp"
#include "SphereCollider.cpp"
#include "MoveScript.cpp"
#include "CubeRenderer.cpp"
#include "ParticleSystemRenderer.cpp"
#include "ParticleSystem.h"
#include "StartSceneRenderer.cpp"

class StartScene : public Scene {
public:
	void Load() {
		GameObject *QuadStart = instanciate("QuadStart");
		QuadStart->addComponent<StartSceneRenderer>();
	}
};

#endif /* defined(START_SCENE_H) */
