#ifndef END_WIN_SCENE
#define END_WIN_SCENE

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
#include "EndWinRenderer.cpp"

class EndWinScene : public Scene {
public:
	void Load() {
		GameObject *EndWin = instanciate("EndWin");
		EndWin->addComponent<EndWinRenderer>();
	}
};

#endif /* defined(END_WIN_SCENE) */
