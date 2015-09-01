#include "cocos2d.h"
#include "PropManager.h"
#include "BulletManager.h"
#include "SurvivalScene.h"

extern bool OpenMusicEffect;

USING_NS_CC;

float getRandom(float basic, float variance)
{
	return basic+(0.5-CCRANDOM_0_1())*variance*2;
}


PropManager::PropManager(void)
{
	m_animation1 = NULL;
	m_animation2 = NULL;
	m_animation3 = NULL;
	m_animation4 = NULL;
	m_animation5 = NULL;
	m_animation6 = NULL;
}


PropManager::~PropManager(void)
{
}

PropManager* PropManager::create(BulletManager* pBulletManger)
{
	PropManager* newManager = new PropManager;
	newManager->m_bulletManager = pBulletManger;

	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->removeSpriteFrames();
	Animation* animation;

	switch (pBulletManger->SceneType)
	{
	case GameScene4:
		newManager->m_time = 3.0f;
		newManager->m_timeVariance = 1.5f;
		newManager->m_duration = 15.0f;
		newManager->m_durationVariance = 5.0f;
		break;
	case GameScene5:
		newManager->m_time = 2.0f;
		newManager->m_timeVariance = 1.0f;
		newManager->m_duration = 20.0f;
		newManager->m_durationVariance = 5.0f;
		// bind animation
		cache->addSpriteFramesWithFile("prop/ppf_0.plist");
		
		//animation1
		animation = Animation::create();
		for(int i = 0; i < 6; i++)
		{
			const char* png = String::createWithFormat("ppf_00_0%d.png", i)->getCString();
			animation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		animation->setDelayPerUnit(0.3);
		newManager->setAnimation1(animation);

		//animation2
		animation = Animation::create();
		for(int i = 0; i < 4; i++)
		{
			const char* png = String::createWithFormat("ppf_01_0%d.png", i)->getCString();
			animation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		animation->setDelayPerUnit(0.2);
		newManager->setAnimation2(animation);

		//animation3
		animation = Animation::create();
		for(int i = 0; i < 3; i++)
		{
			const char* png = String::createWithFormat("ppf_02_0%d.png", i)->getCString();
			animation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		animation->setDelayPerUnit(0.2);
		newManager->setAnimation3(animation);

		//animation4
		animation = Animation::create();
		for(int i = 0; i < 3; i++)
		{
			const char* png = String::createWithFormat("ppf_03_0%d.png", i)->getCString();
			animation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		animation->setDelayPerUnit(0.2);
		newManager->setAnimation4(animation);

		//animation5
		animation = Animation::create();
		for(int i = 0; i < 4; i++)
		{
			const char* png = String::createWithFormat("ppf_04_0%d.png", i)->getCString();
			animation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		animation->setDelayPerUnit(0.2);
		newManager->setAnimation5(animation);

		//animation6
		animation = Animation::create();
		for(int i = 0; i < 3; i++)
		{
			const char* png = String::createWithFormat("ppf_04_0%d.png", i)->getCString();
			animation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		animation->setDelayPerUnit(0.3);
		newManager->setAnimation6(animation);

		break;
	default:
		//gamescene1-3
		newManager->m_time = 15.0f;
		newManager->m_timeVariance = 5.0f;
		newManager->m_duration = 20.0f;
		newManager->m_durationVariance = 5.0f;
		break;
	}

	newManager->m_curTime = 0;
	newManager->m_nextTime = getRandom(newManager->m_time, newManager->m_timeVariance);

	return newManager;
}

void PropManager::update(float deltaTime)
{
	if(m_curTime < m_nextTime)
	{
		m_curTime+=deltaTime;
	}
	else
	{
		m_curTime = 0;
		m_nextTime=getRandom(m_time, m_timeVariance);
		switch(m_bulletManager->SceneType)
		{
		case GameScene4:
			survivalUpdate(deltaTime);
			break;
		case GameScene5:
			competitionUpdate(deltaTime);
			break;
		default:
			classicUpdate(deltaTime);
			break;
		}
	}

	// delete prop
	for( Prop* pProp : m_propDeleteVector )
	{
		Vector<Prop*>::iterator iter = m_propVector.find(pProp);
		if(iter != m_propVector.end())
		{
			if(OpenMusicEffect)
			{
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Prop/sd_00.wav");
			}
			m_bulletManager->getLayer()->removeChild(*iter);
			iter = m_propVector.erase(iter);
		}
	}
	m_propDeleteVector.clear();
}

Vector<Prop*>* PropManager::getPropVector()
{
	return &m_propVector;
}

void PropManager::deleteProp(Prop* pProp)
{
	m_propDeleteVector.pushBack(pProp);
}

void PropManager::classicUpdate(float deltaTime)
{
	// add prop
	float curDuration = getRandom(m_duration, m_durationVariance);
	Prop* newProp = Prop::createProp(m_bulletManager->SceneType, normal);
	float x = CCRANDOM_0_1()*(Director::getInstance()->getVisibleSize().width);
	newProp->setPosition(x, Director::getInstance()->getVisibleSize().height);
	m_bulletManager->getLayer()->addChild(newProp);
	m_propVector.pushBack(newProp);

	newProp->runAction(Sequence::create(
		MoveBy::create(curDuration, Vec2(0, -Director::getInstance()->getVisibleSize().height)),
		CallFuncN::create([&](Node* sender){
			sender->getParent()->removeChild(sender);
	}),
		NULL));
}

void PropManager::survivalUpdate(float deltaTime)
{
	// add prop
	float bombRate = 0.15;
	float curDuration = getRandom(m_duration, m_durationVariance);
	Prop* newProp;
	if(CCRANDOM_0_1()<bombRate)
	{
		newProp = Prop::createProp(m_bulletManager->SceneType,bomb);
	}
	else
	{
		newProp = Prop::createProp(m_bulletManager->SceneType,normal);
	}
	
	float x = CCRANDOM_0_1()*(Director::getInstance()->getVisibleSize().width);
	newProp->setPosition(x, Director::getInstance()->getVisibleSize().height);
	m_bulletManager->getLayer()->addChild(newProp);
	m_propVector.pushBack(newProp);

	newProp->runAction(Sequence::create(
		MoveBy::create(curDuration, Vec2(0, -Director::getInstance()->getVisibleSize().height)),
		CallFuncN::create([&](Node* sender){
			sender->getParent()->removeChild(sender);
	}),
		NULL));

	// prop drop
	for( Prop* pProp : m_propVector )
	{
		if(pProp->getType() == normal)
		{
			if(pProp->getPositionY() < Director::getInstance()->getVisibleSize().height * 0.15)
			{
				m_propDeleteVector.pushBack(pProp);
				Person* pPerson = (Person*)m_bulletManager->getSpriteVector()->getRandomObject();
				pPerson->notHit();
			}
		}
	}
}

void PropManager::competitionUpdate(float deltaTime)
{
	// add prop
	float curDuration = getRandom(m_duration, m_durationVariance);
	Prop* newProp = Prop::createProp(m_bulletManager->SceneType, normal);
	m_bulletManager->getLayer()->addChild(newProp);
	m_propVector.pushBack(newProp);

	float height = Director::getInstance()->getVisibleSize().height;
	float width = Director::getInstance()->getVisibleSize().width;

	int random = CCRANDOM_0_1()*6;
	switch (random)
	{
	case 0:
		newProp->runAction(RepeatForever::create(Animate::create(m_animation1)));
		break;
	case 1:
		newProp->runAction(RepeatForever::create(Animate::create(m_animation2)));
		break;
	case 2:
		newProp->runAction(RepeatForever::create(Animate::create(m_animation3)));
		break;
	case 3:
		newProp->runAction(RepeatForever::create(Animate::create(m_animation4)));
		break;
	case 4:
		newProp->runAction(RepeatForever::create(Animate::create(m_animation5)));
		break;
	case 5:
		newProp->runAction(RepeatForever::create(Animate::create(m_animation6)));
		break;
	default:
		break;
	}
	
	if(random%2)
	{
		float y = height*0.8 - CCRANDOM_0_1()*height*0.3;
		newProp->setPosition(0, y);
		newProp->setScaleX(-newProp->getScaleX());

		newProp->runAction(Sequence::create(
			MoveBy::create(curDuration, Vec2(width, 0.2*height*(0.5-CCRANDOM_0_1()))),
			CallFuncN::create([&](Node* sender){
				sender->getParent()->removeChild(sender);
			}),
			NULL));
	}
	else
	{
		float y = height*0.8 - CCRANDOM_0_1()*height*0.3;
		newProp->setPosition(width, y);
		
		newProp->runAction(Sequence::create(
			MoveBy::create(curDuration, Vec2(-width, 0.2*height*(0.5-CCRANDOM_0_1()))),
			CallFuncN::create([&](Node* sender){
				sender->getParent()->removeChild(sender);
		}),
			NULL));
	}
	
}