#include "SecondScene.h"

USING_NS_CC;

SecondScene::SecondScene()
{
	curScene = GameScene2;
}

SecondScene::~SecondScene()
{

}

Scene* SecondScene::createScene()
{
	 // 'scene' is an autorelease object
	auto scene = Scene::create();
	
	// 'layer' is an autorelease object
	auto layer = SecondScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	//particle system
	layer->m_emitter = ParticleSnow::create();
	layer->m_emitter->retain();

	//auto p = layer->m_emitter->getPosition();
	//layer->m_emitter->setPosition( Vec2( p.x, p.y-110) );
	layer->m_emitter->setLife(3);
	layer->m_emitter->setLifeVar(1);

	// gravity
	layer->m_emitter->setGravity(Vec2(0,-10));

	// speed of particles
	layer->m_emitter->setSpeed(130);
	layer->m_emitter->setSpeedVar(30);


	Color4F startColor = layer->m_emitter->getStartColor();
	startColor.r = 0.9f;
	startColor.g = 0.9f;
	startColor.b = 0.9f;
	layer->m_emitter->setStartColor(startColor);

	Color4F startColorVar = layer->m_emitter->getStartColorVar();
	startColorVar.b = 0.1f;
	layer->m_emitter->setStartColorVar(startColorVar);

	layer->m_emitter->setEmissionRate(layer->m_emitter->getTotalParticles()/layer->m_emitter->getLife());

	layer->m_emitter->setTexture( Director::getInstance()->getTextureCache()->addImage("particle/snow.png"));

	layer->addChild(layer->m_emitter);

	// return the scene
	return scene;
}