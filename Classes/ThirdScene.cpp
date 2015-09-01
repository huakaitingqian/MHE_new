#include "ThirdScene.h"

USING_NS_CC;

ThirdScene::ThirdScene()
{
	curScene = GameScene3;
}

ThirdScene::~ThirdScene()
{

}

Scene* ThirdScene::createScene()
{
	 // 'scene' is an autorelease object
	auto scene = Scene::create();
	
	// 'layer' is an autorelease object
	auto layer = ThirdScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	layer->m_emitter = ParticleSnow::create();
	layer->m_emitter->retain();

	//auto p = layer->m_emitter->getPosition();
	//layer->m_emitter->setPosition( Vec2( p.x, p.y-110) );
	layer->m_emitter->setLife(20);
	layer->m_emitter->setLifeVar(1);

	// gravity
	layer->m_emitter->setGravity(Vec2(0,-10));

	// speed of particles
	layer->m_emitter->setSpeed(30);
	layer->m_emitter->setSpeedVar(30);


	Color4F startColor = layer->m_emitter->getStartColor();
	startColor.r = 0.9f;
	startColor.g = 0.9f;
	startColor.b = 0.9f;
	layer->m_emitter->setStartColor(startColor);

	Color4F startColorVar = layer->m_emitter->getStartColorVar();
	startColorVar.b = 0.1f;
	layer->m_emitter->setStartColorVar(startColorVar);

	layer->m_emitter->setEmissionRate(1);

	layer->m_emitter->setTexture( Director::getInstance()->getTextureCache()->addImage("particle/1.png"));

	layer->addChild(layer->m_emitter);

	// return the scene
	return scene;
}