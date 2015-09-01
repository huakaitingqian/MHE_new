#include "BulletManager.h"

extern bool OpenMusicEffect;

USING_NS_CC;

BulletManager::BulletManager()
{
	m_normalAnimation = NULL;
	m_specialAnimation = NULL;
	m_stunAnimation = NULL;
}

BulletManager::~BulletManager()
{
	clean();
}

BulletManager* BulletManager::create(GameSceneType gamescenetype, Layer* curLayer, Vector<Sprite*>* pSpriteVector, Vec2 g)
{
	BulletManager* newManager = new BulletManager();
	newManager->m_g = g;
	newManager->m_layer = curLayer;
	newManager->m_pSpriteVector = pSpriteVector;
	newManager->SceneType = gamescenetype;
	newManager->m_propManager = PropManager::create(newManager);

	// create action
	auto cache = SpriteFrameCache::sharedSpriteFrameCache();
	Animation* normalAnimation = NULL;
	Animation* specialAnimation = NULL;
	Animation* stunAnimation = NULL;

	switch (gamescenetype)
	{
	case GameScene1:
		cache->addSpriteFramesWithFile("bullet/blef_000_0.plist");
		normalAnimation = Animation::create();
		for(int i = 0; i < 5; i++)
		{
			const char* png = String::createWithFormat("00_0%d.png", i)->getCString();
			normalAnimation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		normalAnimation->setDelayPerUnit(0.07);
		newManager->setNormalAnimation(normalAnimation);

		specialAnimation = Animation::create();
		for(int i = 0; i < 5; i++)
		{
			const char* png = String::createWithFormat("01_0%d.png", i)->getCString();
			specialAnimation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		specialAnimation->setDelayPerUnit(0.07);
		newManager->setSpecialAnimation(specialAnimation);
		break;

	case GameScene2:
		cache->addSpriteFramesWithFile("bullet/blef_001_0.plist");
		normalAnimation = Animation::create();
		for(int i = 0; i < 7; i++)
		{
			const char* png = String::createWithFormat("00_0%d.png", i)->getCString();
			normalAnimation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		normalAnimation->setDelayPerUnit(0.07);
		newManager->setNormalAnimation(normalAnimation);

		specialAnimation = Animation::create();
		for(int i = 0; i < 6; i++)
		{
			const char* png = String::createWithFormat("01_0%d.png", i)->getCString();
			specialAnimation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		specialAnimation->setDelayPerUnit(0.07);
		newManager->setSpecialAnimation(specialAnimation);
		break;

	case GameScene3:
		cache->addSpriteFramesWithFile("bullet/blef_002_0.plist");
		normalAnimation = Animation::create();
		for(int i = 0; i < 5; i++)
		{
			const char* png = String::createWithFormat("00_0%d.png", i)->getCString();
			normalAnimation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		normalAnimation->setDelayPerUnit(0.07);
		newManager->setNormalAnimation(normalAnimation);

		specialAnimation = Animation::create();
		for(int i = 0; i < 10; i++)
		{
			const char* png = String::createWithFormat("01_0%d.png", i)->getCString();
			specialAnimation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		specialAnimation->setDelayPerUnit(0.07);
		newManager->setSpecialAnimation(specialAnimation);
		break;

	case GameScene4:
		cache->addSpriteFramesWithFile("bullet/blef_001_0.plist");
		normalAnimation = Animation::create();
		for(int i = 0; i < 7; i++)
		{
			const char* png = String::createWithFormat("00_0%d.png", i)->getCString();
			normalAnimation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		normalAnimation->setDelayPerUnit(0.07);
		newManager->setNormalAnimation(normalAnimation);
		break;

	case GameScene5:
		cache->addSpriteFramesWithFile("bullet/blef_001_0.plist");
		normalAnimation = Animation::create();
		for(int i = 0; i < 7; i++)
		{
			const char* png = String::createWithFormat("00_0%d.png", i)->getCString();
			normalAnimation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(png));
		}
		normalAnimation->setDelayPerUnit(0.07);
		newManager->setNormalAnimation(normalAnimation);
		break;

	default:
		break;
	}

	return newManager;
}

void BulletManager::update(float deltaTime)
{
	m_propManager->update(deltaTime);

	Vector<Bullet*>::iterator iter;
	for( Bullet* pBullet : m_BulletVector )
	{
		pBullet->update(m_g, deltaTime);
	}

	// remove bullet per second
	for( Bullet* pBullet : m_BulletDeleteVector )
	{
		iter = m_BulletVector.find(pBullet);
		if(iter != m_BulletVector.end())
		{
			// run animate
			(*iter)->getEmitter()->setAutoRemoveOnFinish(true);
			(*iter)->getEmitter()->stopSystem();
			bulletExplode(*iter);
			m_BulletVector.erase(iter);
		}
	}
	m_BulletDeleteVector.clear();
}

void BulletManager::shoot(bulletType type, Owner owner, Point pos, Vec2 velocity)
{
	if(type == SpecialBullet)
	{
		float module = sqrt(velocity.x*velocity.x+velocity.y*velocity.y);
		float cita, cita1, cita2;
		if(velocity.x == 0)
		{
			if(velocity.y>0)
			{
				cita = 3.14/2;
			}
			else
			{
				cita = -3.14/2;
			}
		}
		else
		{
			cita = atan(velocity.y/velocity.x);
			if(velocity.x < 0)
			{
				cita+=3.14;
			}
		}
		cita1 = cita+0.08;
		cita2 = cita-0.08;
		
		Bullet* pBullet;

		pBullet = Bullet::createBullet(type, pos, Vec2(module*cos(cita2),module*sin(cita2)), owner, this);
		m_layer->addChild(pBullet->getEmitter(), 1);
		m_layer->addChild(pBullet, 1);
		m_BulletVector.pushBack(pBullet);

		pBullet = Bullet::createBullet(type, pos, velocity, owner, this);
		m_layer->addChild(pBullet->getEmitter(), 1);
		m_layer->addChild(pBullet, 1);
		m_BulletVector.pushBack(pBullet);

		pBullet = Bullet::createBullet(type, pos, Vec2(module*cos(cita1),module*sin(cita1)), owner, this);
		m_layer->addChild(pBullet->getEmitter(), 1);
		m_layer->addChild(pBullet, 1);
		m_BulletVector.pushBack(pBullet);
		
	}
	else
	{
		Bullet* pBullet = Bullet::createBullet(type, pos, velocity, owner, this);
		m_layer->addChild(pBullet->getEmitter(), 1);
		m_layer->addChild(pBullet, 1);
		m_BulletVector.pushBack(pBullet);
	}
}

void BulletManager::clean()
{
}

Vector<Bullet*>* BulletManager::getBulletVector()
{
	return &m_BulletVector;
}

cocos2d::Layer* BulletManager::getLayer()
{
	return m_layer;
}

void BulletManager::deleteBullet(Bullet* pBullet)
{
	if(m_BulletDeleteVector.find(pBullet)==m_BulletDeleteVector.end())
	{
		m_BulletDeleteVector.pushBack(pBullet);
	}
}

cocos2d::Vector<cocos2d::Sprite*>* BulletManager::getSpriteVector()
{
	return m_pSpriteVector;
}

void BulletManager::bulletExplode(Bullet* pBullet)
{
	char wav[100];
	sprintf(wav, "bullet/sd_0%d_0%d.wav", SceneType, (pBullet->getType()));
	if(OpenMusicEffect)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(wav);
	}
		
	switch (pBullet->getType())
	{
	case NormalBullet:
		if(m_normalAnimation)
		{
			Action *action = Sequence::create(
				Animate::create(m_normalAnimation),
				CallFuncN::create([&](Node* sender){
					sender->getParent()->removeChild(sender);
			}),
			NULL);
			pBullet->runAction(action);
		}
		else
		{
			m_layer->removeChild(pBullet);
			deleteBullet(pBullet);
		}
		break;
	case SpecialBullet:
		if(m_specialAnimation)
		{
			Action *action = Sequence::create(
				Animate::create(m_specialAnimation),
				CallFuncN::create([&](Node* sender){
					sender->getParent()->removeChild(sender);
			}),
				NULL);
			pBullet->runAction(action);
		}
		else
		{
			m_layer->removeChild(pBullet);
			deleteBullet(pBullet);
		}
		break;
	case StunBullet:
		if(m_stunAnimation)
		{
			Action *action = Sequence::create(
				Animate::create(m_stunAnimation),
				CallFuncN::create([&](Node* sender){
					sender->getParent()->removeChild(sender);
			}),
				NULL);
			pBullet->runAction(action);
		}
		else
		{
			deleteBullet(pBullet);
			m_layer->removeChild(pBullet);
		}
		break;

	default:
		break;
	}
}

PropManager* BulletManager::getPropManager()
{
	return m_propManager;
}