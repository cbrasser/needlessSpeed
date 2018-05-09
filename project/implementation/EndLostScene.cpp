#ifndef END_LOST_SCENE
#define END_LOST_SCENE

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
#include "EndLostRenderer.cpp"

class EndLostScene : public Scene {
public:
	void Load() {
		GameObject *EndLost = instanciate("EndLost");
		EndLost->addComponent<EndLostRenderer>();
        
	}
};

#endif /* defined(END_LOST_SCENE) */
