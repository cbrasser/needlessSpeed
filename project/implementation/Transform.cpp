#include "Transform.h"
#include "GameObject.h"
#include "Core.h"
#include "TheRenderer.h"
#include "CameraWrapper.cpp"

vmml::Vector3f Transform::forward(){
	vmml::Matrix4f r = getRotationMatrix();
	return vmml::Vector3f(r.at(0, 2), r.at(1, 2), r.at(2, 2));
}

vmml::Vector3f Transform::up(){
	vmml::Matrix4f r = getRotationMatrix();
	return vmml::Vector3f(r.at(0, 1), r.at(1, 1), r.at(2, 1));
}

void Transform::removeChild(Transform * child){
	children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

vmml::Matrix4f Transform::getRotationMatrix(){
	return _rotMat;
}

vmml::Matrix4f Transform::getRotation()
{
	return _rotMat;
}

vmml::Vector3f Transform::getPosition(){
	return _position;
}

vmml::Vector3f Transform::getScale(){
	return _scale;
}

void Transform::setPosition(vmml::Vector3f position){
	if (!position.equals(_position)) {
		_position = position;
		_hasChanged = true;
	}
}
void Transform::setRotation(vmml::Matrix4f rot) {
	_rotMat = rot;
	_hasChanged = true;
}

void Transform::setRotation(vmml::Vector3f rotation){
	_rotMat = vmml::create_rotation(rotation[2], vmml::Vector3f::UNIT_Z) * vmml::create_rotation(rotation[0], vmml::Vector3f::UNIT_X) * vmml::create_rotation(rotation[1], vmml::Vector3f::UNIT_Y);
	_hasChanged = true;
}

void Transform::setScale(vmml::Vector3f scale){
	if (!scale.equals(_scale)) {
		_scale = scale;
		_hasChanged = true;
	}
}

void Transform::setParent(Transform *parent) {
	if (_parent != nullptr) {
		_parent->removeChild(this);
	}
	
	_parent = parent;
	
	if(parent != nullptr)
		parent->children.push_back(this);
}

void Transform::setParent(GameObject *_gameObject) {
	setParent(_gameObject->transform);
}

vmml::Matrix4f Transform::getTransformationMatrix(){
	if (_parent != nullptr) {
		return (_parent->getTransformationMatrix()) * getLocalTransformationMatrix();
	}
	else
		return getLocalTransformationMatrix();
}

vmml::Matrix4f Transform::getLocalTransformationMatrix(){
	if (_hasChanged) {
		_cache = (getRotationMatrix() * vmml::create_scaling(_scale));
		_cache[0][3] = _position.x();
		_cache[1][3] = _position.y();
		_cache[2][3] = _position.z();
		_hasChanged = false;
	}

	return _cache;
}
