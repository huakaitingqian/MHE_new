#include"Player.h"
USING_NS_CC;


Player::Player()
{
	strcpy(roleName, "Role1");
	strcpy(attackedSound, "playerAttacked.wav");

	char plistFileName[100];
	sprintf(plistFileName,"character/%s.plist", roleName);  
	cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(plistFileName);

	_faceRight = true;
}

Player::~Player()
{
}

bool Player::init()
{
	do 
	{
		CC_BREAK_IF(!Person::initWithSpriteFrameName("Role1Normal1.png"));

		CallFunc *callbackNormal = CallFunc::create(std::bind(&Player::normalAction, this));
		CallFunc *callbackJumpEnd = CallFunc::create(std::bind(&Player::jumpActionEnd, this));

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		//正常状态下动画
		const char* normalPng = String::createWithFormat("%s%s", roleName, "Normal")->getCString();
		Animation* normalAnimation = createAnimation(normalPng,6,12);
		setNormalAction(RepeatForever::create(Animate::create(normalAnimation)));

		//移动状态下
		//const char* movePng = String::createWithFormat(roleName,"Move")->getCString();
		//Animation* moveAnimation = createAnimation(movePng,6,12);
		setMoveAction(RepeatForever::create(Animate::create(normalAnimation)));

		//攻击状态下动画
		const char* firePng = String::createWithFormat("%s%s", roleName, "Fire")->getCString();
		Animation* fireAnimation = createAnimation(firePng,2,10);
		setFireAction(Sequence::create(Animate::create(fireAnimation), callbackNormal, NULL));

		//受到攻击状态下动画
		const char* attackedPng = String::createWithFormat("%s%s", roleName, "Attacked")->getCString();
		Animation* attackedAnimation = createAnimation(attackedPng,3,12);
		setAttackedAction(Sequence::create(Animate::create(attackedAnimation), callbackNormal, NULL));

		//被冻住状态下
		const char* frozenPng = String::createWithFormat("%s%s", roleName, "Frozen")->getCString();
		Animation* frozenAnimation = createAnimation(frozenPng,2,10);
		setFrozenAction(Sequence::create(Animate::create(frozenAnimation), DelayTime::create(5), callbackNormal, NULL));

		//被黑洞困住状态下
		const char* holePng = String::createWithFormat("%s%s", roleName, "Hole")->getCString();
		Animation* holeAnimation = createAnimation(holePng,2,10);
		setHoleAction(Sequence::create(Animate::create(holeAnimation), DelayTime::create(5), callbackNormal, NULL));

		//被网住状态下
		const char* netPng = String::createWithFormat("%s%s", roleName, "Net")->getCString();
		Animation* netAnimation = createAnimation(netPng,2,10);
		setNetAction(Sequence::create(Animate::create(netAnimation), DelayTime::create(5), callbackNormal, NULL));

		//跳跃状态下动画
		auto actionBy = JumpBy::create(1, Vec2(0,0), visibleSize.height/4, 1);
		//auto actionByBack = actionBy->reverse();
		setJumpAction(Sequence::create(actionBy, callbackJumpEnd, NULL));

		//胜利状态下
		const char* victoryPng = String::createWithFormat("%s%s", roleName, "Victory")->getCString();
		Animation* victoryAnimation = createAnimation(victoryPng,2,10);
		setVictoryAction(Sequence::create(Animate::create(victoryAnimation), DelayTime::create(5), NULL));

		//失败状态下
		const char* failPng = String::createWithFormat("%s%s", roleName, "Failure")->getCString();
		Animation* failAnimation = createAnimation(failPng,2,10);
		setFailAction(Sequence::create(Animate::create(failAnimation), DelayTime::create(5), NULL));

		
		setTotalHP(100);
		setTotalSP(100);

		setHP(100);
		setSP(0);

		return true;
	}while(0);

	return false;
}