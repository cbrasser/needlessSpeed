#include "Collider.h"
#include "Physics.h"

Collider::Collider() {
	Physics::addToPhysicsList(this);
}

void Collider::destroy(){
	Physics::removeFromPhysicsList(this);
}
