#include "SceneManager.h"
#include "StartScene.h"
USING_NS_CC;

void SceneManager::goMenu()
{
	Scene *scene = (StartScene::createScene());
	SceneManager::go(scene);
}

void SceneManager::go(Scene* scene)
{
	Layer* layer = (Layer*)scene;

	Director *director = Director::getInstance();
	Scene *newScene = SceneManager::wrap(layer);
	if ( director->getRunningScene() )
	{
		director->replaceScene(newScene);
	}
	else
	{
		director->runWithScene(newScene);
	}
}

Scene* SceneManager::wrap(Layer *layer)
{
	Scene *newScene = Scene::create();
	newScene->addChild(layer);
	return newScene;
}