#include "StateController.h"
#include <random>
USING_NS_CC;

StateController::StateController():
	shootPositon(-1,-1),hitPosition(-1,-1),
	curNPC(nullptr), curPlayer(nullptr), 
	gravity(0,0),velocity(0,0), 
	playerShoot(false),time(0.0),skill2time(0.0),skill3time(0.0)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	srand(0);
}

StateController::~StateController()
{
}

StateController* StateController::create(NPC* curNPC, Player* curPlayer, Vec2 gravity, BulletManager* bulletManager, GameSceneType type)
{
	StateController* newStateController = new StateController();
	newStateController->curNPC = curNPC;
	newStateController->curPlayer = curPlayer;
	newStateController->gravity =gravity;
	newStateController->m_pBulletMangeer = bulletManager;
	newStateController->curScene = type;

	return newStateController;
}

void StateController::playerShooting(cocos2d::Vec2 shootPositon, cocos2d::Vec2 velocity)
{
	this->hitPosition = shootPositon + Vec2(velocity.x * (2*velocity.y)/(-gravity.y), 0);
	playerShoot = true;
	CCLOG("the hit position is x=%f, y=%f",hitPosition.x, hitPosition.y);
}

void StateController::update(float dt)
{
	time += dt;
	skill2time += dt;
	skill3time += dt;
	if(playerShoot && curNPC->getBoundingBox().intersectsRect(Rect(hitPosition.x-150, hitPosition.y-150, 300, 300)))
	{
		playerShoot = false;
		avoid();
	}
	/*else if(curNPC->getSP()>50 && time>1 && skill2time>1)
	{
		skill3time = 0.0;
		curNPC->setSP(curNPC->getSP()-50);
		fire(StunBullet);
	}
	else if(skill2time>18 && time>1 && skill3time>1)
	{
		skill2time = 0.0;
		fire(SpecialBullet);
	}
	else if(time > 4 && skill2time>1 && skill3time>1)
	{
		time = 0.0;
		fire(NormalBullet);
	}*/

	switch (curScene)
	{
	case GameScene3:
		if(curNPC->getSP()>50 && time>1 && skill2time>1)
		{
			skill3time = 0.0;
			curNPC->setSP(curNPC->getSP()-50);
			fire(StunBullet);
		}
	case GameScene2:
		if(skill2time>18 && time>1 && skill3time>1)
		{
			skill2time = 0.0;
			fire(SpecialBullet);
		}
	case GameScene1:
		if(time > 4 && skill2time>1 && skill3time>1)
		{
			time = 0.0;
			fire(NormalBullet);
		}
		break;
	default:
		break;
	}

	if(curNPC->getActionState() == Move_Action)
	{
		if(npcDestination.x > curNPC->getPosition().x+1 && curNPC->getBoundingBox().getMaxX()+2 < visibleSize.width-10)
			curNPC->setPosition(curNPC->getPosition() + Vec2(2,0));
		else if(npcDestination.x < curNPC->getPosition().x-1 && curNPC->getBoundingBox().getMinX()+2 > visibleSize.width*3/5)
			curNPC->setPosition(curNPC->getPosition() - Vec2(2,0));
	}

}

void StateController::fire(bulletType type)
{
	if(curNPC->getActionState() != Frozen_Action)
	{
		Vec2 playerPositon = curPlayer->getPosition();
		Vec2 shootVelocity;

		//随机数
		int temp = visibleSize.width/4 * rand()/(RAND_MAX+1.0);

		Vec2 tempPosition = curNPC->getPosition();
		tempPosition += Vec2(temp-visibleSize.width/4/2, 0);
	
		shootVelocity.x =- sqrt((-gravity.y) * (tempPosition.x - playerPositon.x) / 4);
		shootVelocity.y = 2 * (-shootVelocity.x);
	
		curNPC->fireAction();
		m_pBulletMangeer->shoot(type, npc,curNPC->getPosition(),shootVelocity);
	}
}

void StateController::avoid()
{
	if(curNPC->getActionState() != Frozen_Action)
	{
		//随机数
		int temp = visibleSize.width/3 * rand()/(RAND_MAX+1.0);
		hitPosition += Vec2(temp-visibleSize.width/3/2, 0);

		if(hitPosition.x < visibleSize.width* 5/8)
		{
			curNPC->moveAction();
			npcDestination = hitPosition + Vec2(visibleSize.width*2/8,0);
		}
		else if(hitPosition.x < visibleSize.width * 6/8)
		{
			curNPC->moveAction();
			if(hitPosition.x < curNPC->getPosition().x)
				npcDestination = hitPosition + Vec2(visibleSize.width*2/8,0);
			else
				npcDestination = hitPosition - Vec2(visibleSize.width/8,0);
		}
		else if(hitPosition.x < visibleSize.width * 7/8)
		{
			curNPC->moveAction();
			if(hitPosition.x < curNPC->getPosition().x)
				npcDestination = hitPosition + Vec2(visibleSize.width/8,0);
			else
				npcDestination = hitPosition - Vec2(visibleSize.width*2/8,0);
		}
		else if(hitPosition.x < visibleSize.width)
		{
			curNPC->moveAction();
			npcDestination = hitPosition - Vec2(visibleSize.width*3/8,0);
		}
	}
}