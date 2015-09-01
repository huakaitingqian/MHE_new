#include "Person.h"
#include <SimpleAudioEngine.h>

USING_NS_CC;

extern bool OpenMusicEffect;

Person::Person()
{
	_normalAction = NULL;
	_fireAction = NULL;
	_attackedAction = NULL;
	_frozenAction = NULL;
	_holeAction = NULL;
	_netAction = NULL;
	_moveAction = NULL;
	_jumpAction = NULL;
	_victoryAction = NULL;
	_failAction = NULL;

	isJumping =false;
	strcpy(roleName, "Role2");
	strcpy(attackedSound, "playerAttacked.wav");

	char plistFileName[100];
	sprintf(plistFileName,"character/%s.plist", roleName);  
	cache = SpriteFrameCache::sharedSpriteFrameCache();
}

Person::~Person()
{

}

Animation* Person::createAnimation(const char* fmt, int count, float fps)
{
	auto frames = Animation::create();

	for(int i = 1; i < count; i++)
	{
		const char* png = String::createWithFormat("%s%d.png", fmt, i)->getCString();
		frames->addSpriteFrame(cache->spriteFrameByName(png));
	}
	frames->setDelayPerUnit(1/fps);

	return frames;
}

void Person::normalAction()
{
	if(changeState(Normal_Action))
	{
		runAction(_normalAction);
	}
}

void Person::fireAction()
{
	if(changeState(Fire_Action))
	{
		runAction(_fireAction);
	}
}

void Person::attackedAction()
{
	if(changeState(Attacked_Action))
	{
		runAction(_attackedAction);
	}
}

void Person::moveAction()
{
	if(changeState(Move_Action))
	{
		runAction(_moveAction);
	}
}

void Person::jumpAction()
{
	if(changeState(Jump_Action))
	{
		runAction(_jumpAction);
	}
}

void Person::jumpActionEnd()
{
	isJumping = false;
	normalAction();
}

void Person::jumpToEnd()
{
	isJumping = false;
}

void Person::attacked(bulletType type, GameSceneType scenetype)
{
	if(OpenMusicEffect)
	{
		const char* string = String::createWithFormat("%s%s", "music/", attackedSound)->getCString();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(string);
	}

	if(isJumping)
	{
		personVelocity = Vec2(0,0);
	}

	int damage;
	switch (type)
	{
	case NormalBullet:
		//设置HP
		damage = 10;
		if(getHP()-damage > 0)
			setHP(getHP()-damage);
		else
			setHP(0);

		//设置SP
		if(getSP() + 20 < getTotalSP())
			setSP(getSP()+20);
		else
			setSP(getTotalSP());

		//动作
		if(changeState(Attacked_Action))
			runAction(_attackedAction);
		break;

	case SpecialBullet:
		damage = 10;
		//设置HP
		if(getHP()-damage > 0)
			setHP(getHP()-damage);
		else
			setHP(0);

		//设置SP
		if(getSP() + 20 < getTotalSP())
			setSP(getSP()+20);
		else
			setSP(getTotalSP());

		//动作
		if(changeState(Attacked_Action))
			runAction(_attackedAction);
		break;
	case StunBullet:
		//设置HP
		damage=10;
		if(getHP()-damage > 0)
			setHP(getHP()-damage);
		else
			setHP(0);

		//设置SP
		if(getSP() + 20 < getTotalSP())
			setSP(getSP() + 20);
		else
			setSP(getTotalSP());

		//动作
		if(changeState(Frozen_Action))
		{
			switch (scenetype)
			{
			case GameScene1:
				runAction(_holeAction);
				break;
			case GameScene2:
				runAction(_frozenAction);
				break;
			case GameScene3:
				runAction(_netAction);
				break;
			case GameScene4:
				break;
			case GameScene5:
				break;
			default:
				break;
			}	
		}
		break;
	default:
		break;
	}

	//char string[10]={0};
	//sprintf(string, "%d", damage);
	//auto label = Label::createWithBMFont("fonts/bitmapFontTest.fnt",string);
	//label->setPosition(getPosition()+Vec2(0,50));
	//addChild(label,4);
}

void Person::frozenAction()
{
	if(changeState(Frozen_Action))
		runAction(_frozenAction);
}

void Person::failAction()
{
	if(changeState(Fail_Action))
		runAction(_failAction);
}

void Person::victoryAction()
{
	if(changeState(Vectory_Action))
		runAction(_victoryAction);
}

void Person::getProp(GameSceneType scene, PropType type)
{
	switch (type)
	{
	case normal:
		switch (scene)
		{
		case GameScene1:
		case GameScene2:
		case GameScene3:
			if(getHP()+10 < getTotalHP())
				setHP(getHP()+10);
			else
				setHP(getTotalHP());
			break;
		default:
			break;
		}
		break;
	case bomb:
		setHP(0);
		break;
	default:
		break;
	}
}

void Person::getProp()
{
	if(getHP()+10 < getTotalHP())
		setHP(getHP()+10);
	else
		setHP(getTotalHP());
}

void Person::notHit()
{                                     
	switch ((int)(getHP()))
	{
	case 1:
		setHP(0);
		break;
	case 2:
		setHP(1);
		break;
	case 3:
		setHP(2);
		break;
	default:
		break;
	}
}

bool Person::changeState(ActionState state)
{
	// 已经胜利，就不能再出发其他动作了！
	if (_currentState == Vectory_Action) 
		return false;

	// 已经失败，就不能再出发其他动作了！
	if(_currentState == Fail_Action)
		return false;

	// 被冻住，就不能再出发其他动作了！时间到了正常状态可以触发
	//if(state != Normal_Action)
	//	if (_currentState == Frozen_Action)
	//		return false;
	
	if (_currentState == Frozen_Action)
	{
		if(state != Normal_Action && state!=Vectory_Action && state!=Fail_Action)
			return false;
	}

	//处于跳跃状态时，不执行动作
	if(_currentState == Jump_Action)
		if(state != Attacked_Action && state!=Vectory_Action && state!=Fail_Action && state!=Normal_Action)
			return false;

	// 已经处于要改变的状态，就没必要在改变了！
	if (_currentState == state) 
	{
		return false;
	}

	// 改变动作之前，先停止所有动作
	this->stopAllActions();

	_currentState = state;
	return true;
}

void Person::jumpTo(Vec2 velocity, Size visibleSize, float boundingX, float boundingY)
{
	if(_currentState!=Jump_Action && !isJumping && _currentState!=Attacked_Action)
	{
		isJumping = true;
		this->boundingX = boundingX;
		this->boundingY = boundingY;

		if(changeState(Jump_Action))
		{
			if(fabs(velocity.x) < visibleSize.width/8)

				personVelocity = Vec2(0,visibleSize.height);
			else if(velocity.x > 0)
				personVelocity = Vec2(100,visibleSize.height);
			else if(velocity.x < 0)
				personVelocity = Vec2(-100,visibleSize.height);
		}
	}
}

void Person::update(float dt, Vec2 g)
{
	if(isJumping)
	{
		Point pos = this->getPosition();
		if(boundingX-(this->getBoundingBox().getMaxX()-this->getBoundingBox().getMinX())/2 < pos.x+personVelocity.x*dt 
			|| pos.x+personVelocity.x*dt < 0+(this->getBoundingBox().getMaxX()-this->getBoundingBox().getMinX())/2)
			personVelocity = Vec2(0,personVelocity.y);
		if(boundingY > pos.y+personVelocity.y*dt+g.y*dt*dt/2)
		{
			personVelocity = Vec2(0,0);
			jumpToEnd();
			normalAction();
		}
		pos += personVelocity*dt+g*dt*dt/2;
		setPosition(pos);
		personVelocity += g*dt;
	}
}