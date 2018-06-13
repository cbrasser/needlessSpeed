#ifndef CRASH_SCENE
#define CRASH_SCENE

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
#include "CrashSceneRenderer.cpp"

class CrashScene : public Scene {
public:
	void Load() {
		GameObject *QuadCrash = instanciate("QuadCrash");
		QuadCrash->addComponent<CrashSceneRenderer>();
	}
};

#endif /* defined(CRASH_SCENE_H) */