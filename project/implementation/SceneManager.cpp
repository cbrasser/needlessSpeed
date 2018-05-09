#include "SceneManager.h"
#include "Scene.h"
#include "TheRenderer.h"
#include "Core.h"
#include "Logic.h"

Scene* SceneManager::currentScene;
std::string SceneManager::currentSceneName;
std::map<std::string, Scene*> SceneManager::sceneMap;

void SceneManager::addScene(const std::string name, Scene* scene){
	sceneMap[name] = scene;
}

void SceneManager::loadScene(Scene * scene){
	unloadScene(currentScene);
    scene->Load();
	currentScene = scene;

	TheRenderer::Instance()->init();
	Logic::start();
}

void SceneManager::loadScene(const std::string & name, int asteroidAmount){
    unloadScene(currentScene);
    sceneMap[name]->Load(asteroidAmount);

    currentScene = sceneMap[name];
    
    TheRenderer::Instance()->init();
    Logic::start();
    
    currentSceneName = name;

}

void SceneManager::loadScene(const std::string & name){
	loadScene(sceneMap[name]);
	currentSceneName = name;
}

void SceneManager::unloadScene(Scene * scene){
	if (currentScene == nullptr) return;

	scene->unload();
	currentScene = nullptr;
}

void SceneManager::unloadScene(const std::string & name){
	unloadScene(sceneMap[name]);
}

std::string SceneManager::getCurrentName() {
	return currentSceneName;
}

Scene* SceneManager::getCurrentScene() {
	return currentScene;
}

void SceneManager::destroy(){

	for (auto const &scene : sceneMap) {
		scene.second->unload();
		delete scene.second;
	}
}
