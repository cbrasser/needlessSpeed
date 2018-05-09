#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vmmlib/util.hpp>
#include <vector>
#include "Component.h"

class Transform : public Component{
public:

	void setPosition(vmml::Vector3f position);
	void setRotation(vmml::Vector3f rotation);
	void setRotation(vmml::Matrix4f rot);
	void setScale(vmml::Vector3f scale);
	void setParent(Transform *_parent);
	void setParent(GameObject *_gameObject);
	vmml::Matrix4f getRotationMatrix();
	vmml::Matrix4f getRotation();
	vmml::Vector3f getPosition();
	vmml::Vector3f getScale();

	vmml::Matrix4f getTransformationMatrix();
	vmml::Vector3f forward();
	vmml::Vector3f up();
	std::vector<Transform*> children;
	Transform* getParent() { return _parent; }
	void removeChild(Transform* child);
private:
	vmml::Matrix4f _rotMat;
	bool _hasChanged = true;
	vmml::Vector3f _position = vmml::Vector3f::ZERO;
	//vmml::Vector3f _rotation = vmml::Vector3f::ZERO;
	vmml::Vector3f _scale = vmml::Vector3f::ONE;
	vmml::Matrix4f _cache;
	Transform* _parent;
	
	vmml::Matrix4f getLocalTransformationMatrix();
};
#endif /* defined(TRANSFORM_H) */
