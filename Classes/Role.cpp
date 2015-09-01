#include "Role.h"
USING_NS_CC;

//Role1
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

Role1::Role1()
{
	strcpy(roleName, "Role1");

	char plistFileName[100];
	sprintf(plistFileName,"character/%s.plist", roleName);  
	cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(plistFileName);
}

Role1::~Role1()
{

}

bool Role1::init()
{
	do 
	{

		CC_BREAK_IF(!Person::initWithSpriteFrameName("Role1Normal1.png"));

		CallFunc *callbackNormal = CallFunc::create(std::bind(&Role1::normalAction, this));

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

		//跳跃状态下动画
		auto actionBy = JumpBy::create(2, Vec2(0,0), visibleSize.height/4, 1);
		//auto actionByBack = actionBy->reverse();
		setJumpAction(Sequence::create(actionBy, callbackNormal, NULL));

		return true;
	}while(0);

	return false;
}


//Role2
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------Role1

Role2::Role2()
{
	strcpy(roleName, "Role2");

	char plistFileName[100];
	sprintf(plistFileName,"character/%s.plist", roleName);  
	cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(plistFileName);
}

Role2::~Role2()
{

}

bool Role2::init()
{
	do 
	{

		CC_BREAK_IF(!Person::initWithSpriteFrameName("Role2Normal1.png"));

		CallFunc *callbackNormal = CallFunc::create(std::bind(&Role2::normalAction, this));

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
		Animation* fireAnimation = createAnimation(firePng,2,20);
		setFireAction(Sequence::create(Animate::create(fireAnimation), callbackNormal, NULL));

		//受到攻击状态下动画
		const char* attackedPng = String::createWithFormat("%s%s", roleName, "Attacked")->getCString();
		Animation* attackedAnimation = createAnimation(attackedPng,3,12);
		setAttackedAction(Sequence::create(Animate::create(attackedAnimation), callbackNormal, NULL));

		return true;
	}while(0);

	return false;
}
//Role3
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

Role3::Role3()
{
	strcpy(roleName, "Role3");

	char plistFileName[100];
	
	sprintf(plistFileName,"character/%s.plist", roleName);

	cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(plistFileName);
}

Role3::~Role3()
{

}

bool Role3::init()
{
	do 
	{

		CC_BREAK_IF(!Person::initWithSpriteFrameName("Role3Normal1.png"));

		CallFunc *callbackNormal = CallFunc::create(std::bind(&Role3::normalAction, this));

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
		Animation* fireAnimation = createAnimation(firePng,2,20);
		setFireAction(Sequence::create(Animate::create(fireAnimation), callbackNormal, NULL));

		//受到攻击状态下动画
		const char* attackedPng = String::createWithFormat("%s%s", roleName, "Attacked")->getCString();
		Animation* attackedAnimation = createAnimation(attackedPng,3,12);
		setAttackedAction(Sequence::create(Animate::create(attackedAnimation), callbackNormal, NULL));

		return true;
	}while(0);

	return false;
}

//Role4
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

Role4::Role4()
{
	strcpy(roleName, "Role4");

	char plistFileName[100];
	
	sprintf(plistFileName,"character/%s.plist", roleName);

	cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(plistFileName);
}

Role4::~Role4()
{

}

bool Role4::init()
{
	do 
	{

		CC_BREAK_IF(!Person::initWithSpriteFrameName("Role4Normal1.png"));

		CallFunc *callbackNormal = CallFunc::create(std::bind(&Role4::normalAction, this));

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
		Animation* fireAnimation = createAnimation(firePng,2,20);
		setFireAction(Sequence::create(Animate::create(fireAnimation), callbackNormal, NULL));

		//受到攻击状态下动画
		const char* attackedPng = String::createWithFormat("%s%s", roleName, "Attacked")->getCString();
		Animation* attackedAnimation = createAnimation(attackedPng,3,12);
		setAttackedAction(Sequence::create(Animate::create(attackedAnimation), callbackNormal, NULL));

		return true;
	}while(0);

	return false;
}