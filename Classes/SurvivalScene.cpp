#include "SurvivalScene.h"
#include "PauseLayer.h"
#include "FailureLayer.h"

USING_NS_CC;
extern bool OpenMusicEffect;

SurvivalScene::SurvivalScene():
	skillCoolDownNeedTime(0),skillCoolDownTime(1)
{
	curScene = GameScene4;
	curBlood = 3;
	playerScores = 0;
	gameover = false;
}

SurvivalScene::~SurvivalScene()
{
}

Scene* SurvivalScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	
	// 'layer' is an autorelease object
	auto layer = SurvivalScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool SurvivalScene::init()
{
	visibleSize = Director::sharedDirector()->getVisibleSize();
	origin = Director::sharedDirector()->getVisibleOrigin();

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(SurvivalScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(SurvivalScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(SurvivalScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto bg = Sprite::create("background/bg_survival.png");
	bg->setScale(visibleSize.width/bg->getContentSize().width,
		visibleSize.height/bg->getContentSize().height);
	bg->setPosition(Director::sharedDirector()->getVisibleSize()/2);
	addChild(bg);

	//设置分数
	char string[15] = {0};
	sprintf(string, "%d", (int)playerScores);
	playerScoresLabel = Label::createWithBMFont("fonts/bitmapFontTest.fnt",string);
	playerScoresLabel->setPosition(visibleSize.width/8,visibleSize.height*7/8);
	addChild(playerScoresLabel,2);

	setSkillCoolDownBar();
	setMenu();
	setPowerBar();

	//设置血条
	blood1 = Sprite::create("button/OneBlood.png");
	blood1->setScale(visibleSize.height/8/blood1->getContentSize().height);
	blood1->setPosition(blood1->getContentSize().width/2,
		visibleSize.height - blood1->getContentSize().height/2);
	addChild(blood1,2);
	blood1->setVisible(true);

	//设置血条
	blood2 = Sprite::create("button/TwoBlood.png");
	blood2->setScale(visibleSize.height/8/blood2->getContentSize().height);
	blood2->setPosition(blood1->getPosition().x + blood2->getContentSize().width/2,
		visibleSize.height - blood2->getContentSize().height/2);
	addChild(blood2,2);
	blood2->setVisible(true);

	//设置血条
	blood3 = Sprite::create("button/ThreeBlood.png");
	blood3->setScale(visibleSize.height/8/blood3->getContentSize().height);
	blood3->setPosition(blood2->getPosition().x + blood3->getContentSize().width/2,
		visibleSize.height - blood3->getContentSize().height/2);
	addChild(blood3,2);
	blood3->setVisible(true);

	//设置player
	_curPlayer = Player::create();
	_curPlayer->setPosition(visibleSize.width/8,visibleSize.height*3/16);
	_curPlayer->setScale((visibleSize.height*3/16)/_curPlayer->getContentSize().height);
	_curPlayer->setFlipX(-1);
	_curPlayer->setTag(1);
	addChild(_curPlayer,1);
	_curPlayer->normalAction();
	_curPlayer->setHP(3);

	//将player添加到spriteVector中
	spritesVector.pushBack(_curPlayer);

	//设置重力以及初始化BulletManager
	g = Vec2(0, -800);
	g_BulletManager = BulletManager::create(curScene,(Layer*)this, &spritesVector, g);

	this->scheduleUpdate();
	
	return true;
}

void SurvivalScene::setSkillCoolDownBar()
{
	auto skillCoolDownBg = Sprite::create("skill/survivalSkill.png");
	skillCoolDownBg->setPosition(40,40);
	addChild(skillCoolDownBg, 2);

	auto skill1CoolSprite = Sprite::create("skill/survivalSkill_disabled.png");
	skillCoolDownBar = ProgressTimer::create(skill1CoolSprite);

	skillCoolDownBar->setType(kCCProgressTimerTypeBar);
	skillCoolDownBar->setMidpoint(ccp(0.5,0));
	skillCoolDownBar->setBarChangeRate(ccp(0,1));
	skillCoolDownBar->setPercentage(0);
	skillCoolDownBar->setPosition(40,40);
	addChild(skillCoolDownBar,3);
}

void SurvivalScene::setPowerBar()
{
	//力度条
	powerBarBg = Sprite::create("power_bg.png");
	powerBarBg->setAnchorPoint(Vec2(0,0.5));
	addChild(powerBarBg,1);

	auto temp = Sprite::create("power.png");
	powerBar = ProgressTimer::create(temp);
	powerBar->setAnchorPoint(Vec2(0, 0.5));
	powerBar->setType(kCCProgressTimerTypeBar);
	powerBar->setMidpoint(ccp(0,0.5));
	powerBar->setBarChangeRate(ccp(1,0));

	powerBar->setPercentage(10);

	addChild(powerBar,1);

	powerBar->setVisible(false);
	powerBarBg->setVisible(false);
}

void SurvivalScene::setMenu()
{
	//暂停按钮
	auto pauseItem = MenuItemImage::create(
										"button/pause.png",
										"button/pause_selected.png",
										CC_CALLBACK_1(SurvivalScene::doPause, this));
	pauseItem->setScale(visibleSize.width/20/pauseItem->getContentSize().width);

	pauseItem->setPosition(Vec2(visibleSize.width - visibleSize.width/12/2,
		visibleSize.height - visibleSize.height/12/2));

	//退出按钮
	auto closeItem = MenuItemImage::create(
										   "CloseNormal.png",
										   "CloseSelected.png",
										   CC_CALLBACK_1(SurvivalScene::menuCloseCallback, this));
	
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
								origin.y + closeItem->getContentSize().height/2));

	auto menu = Menu::create(pauseItem, closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void SurvivalScene::doPause(Ref* pSender)
{
	CCDirector::sharedDirector()->pause();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();  
	Scene *pauseLayer = PauseLayer::createScene(curScene);  
	addChild(pauseLayer,999);
}

void SurvivalScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}

void SurvivalScene::update(float dt)
{
	g_BulletManager->update(dt);

	if(_curPlayer->getActionState() == Move_Action)
	{
		if(playerDestination.x > _curPlayer->getPosition().x+1 && _curPlayer->getBoundingBox().getMaxX()+2 < visibleSize.width-30)
		{
			if(! _curPlayer->getFaceDirection())
			{
				_curPlayer->setFaceDirection(true);
				_curPlayer->setFlippedX(true);
			}
			_curPlayer->setPosition(_curPlayer->getPosition() + Vec2(2,0));
		}
		else if(playerDestination.x < _curPlayer->getPosition().x-1 && _curPlayer->getBoundingBox().getMinX()-2 > 10)
		{
			if(_curPlayer->getFaceDirection())
			{
				_curPlayer->setFaceDirection(false);
				_curPlayer->setFlippedX(false);
			}
			_curPlayer->setPosition(_curPlayer->getPosition() - Vec2(2,0));
		}

		startPosition = _curPlayer->getPosition();
		powerBarBg->setPosition(startPosition);
		powerBar->setPosition(startPosition);
	}

	//更新技能冷却时间
	if(skillCoolDownNeedTime - dt> 0)
	{
		skillCoolDownNeedTime -= dt;
		skillCoolDownBar->setPercentage(skillCoolDownNeedTime/skillCoolDownTime * 100);
	}
	else
	{
		skillCoolDownNeedTime = 0.0f;
		skillCoolDownBar->setPercentage(0);
	}

	//update blood
	switch (_curPlayer->getHP())
	{
	case 3:
		break;
	case 2:
		blood3->setVisible(false);
		break;
	case 1:
		blood3->setVisible(false);
		blood2->setVisible(false);
		break;
	case 0:
		blood3->setVisible(false);
		blood2->setVisible(false);
		blood1->setVisible(false);
		if(!gameover)
			failure();
		break;
	default:
		break;
	}
}

bool SurvivalScene::contaiinsTouchLocation(cocos2d::Touch* touch)
{
	return _curPlayer->getBoundingBox().containsPoint(convertTouchToNodeSpace(touch));
}

bool SurvivalScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event)
{
	if ( !contaiinsTouchLocation(touch) )
	{
		playerDestination = touch->getLocation();
		if(playerDestination.y < visibleSize.height/2)
			_curPlayer->moveAction();
		else
			_curPlayer->jumpAction();
		return false;
	}

	startPosition = touch->getLocation();
	return true;
}

void SurvivalScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event)
{
	powerBarBg->setPosition(startPosition);
	powerBar->setPosition(startPosition);
	powerBarBg->setVisible(true);
	powerBar->setVisible(true);

	Vec2 position = touch->getLocation();
	Vec2 direction = position - startPosition;

	//旋转
	if(direction.x == 0)
	{
		if(direction.y>0)
		{
			powerBarBg->setRotation(270);
			powerBar->setRotation(270);
		}
		else if(direction.y<0)
		{
			powerBarBg->setRotation(90);
			powerBar->setRotation(90);
		}
	}
	else if( direction.x > 0)
	{
		float cita = atan(direction.y/direction.x);
		powerBarBg->setRotation(-cita*180/3.14);
		powerBar->setRotation(-cita*180/3.14);
	}
	else if (direction.x < 0)
	{
		float cita = atan(direction.y/direction.x);
		powerBarBg->setRotation(-cita*180/3.14 + 180);
		powerBar->setRotation(-cita*180/3.14 + 180);
	}

	//设置进度
	float lineDirection = sqrt(direction.x * direction.x + direction.y * direction.y);
	float powerBarLengthWidth = (powerBarBg->getBoundingBox().getMaxX()
		-powerBarBg->getBoundingBox().getMinX());
	float powerBarLengthHeight = (powerBarBg->getBoundingBox().getMaxY()
		-powerBarBg->getBoundingBox().getMinY());
	float powerBarLength = powerBarLengthWidth > powerBarLengthHeight 
		? powerBarLengthWidth : powerBarLengthHeight;
	if(lineDirection < powerBarLength)
	{
		powerBar->setPercentage(lineDirection*100 / powerBarLength);
	}
	else
	{
		powerBar->setPercentage(100);
	}
}

void SurvivalScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event)
{
	endPosition = touch->getLocation();
	powerBarBg->setVisible(false);
	powerBar->setVisible(false);
	dealEndTouch();
}

void SurvivalScene::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event  *event)
{

}

void SurvivalScene::dealEndTouch()
{
	if(skillCoolDownNeedTime > 0)
	{
		CCLOG("cd time");
	}
	else
	{
		skillCoolDownNeedTime = skillCoolDownTime;

		Vec2 pos = _curPlayer->getPosition();
		Vec2 velocity;
		velocity.x= (endPosition.x - startPosition.x) / visibleSize.height * 3000 ;
		velocity.y= (endPosition.y - startPosition.y) /visibleSize.height * 3000;
		
		if((velocity.x>0 && !_curPlayer->getFaceDirection()) || (velocity.x < 0 && _curPlayer->getFaceDirection()))
		{
			_curPlayer->setFaceDirection(!_curPlayer->getFaceDirection());
			_curPlayer->setFlippedX(_curPlayer->getFaceDirection());
		}

		g_BulletManager->shoot(NormalBullet, player, pos, velocity);
		if(OpenMusicEffect)
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/Attack.wav");
		_curPlayer->fireAction();
	}

}

void SurvivalScene::addPlayerMark(int mark)
{
	playerScores += mark;
	
	char string[15] = {0};
	sprintf(string, "%d", (int)playerScores);
	playerScoresLabel->setString(string);
}

void SurvivalScene::failure()
{
	gameover = true;
	CCDirector::sharedDirector()->pause();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();  
	FailureLayer *failureLayer = FailureLayer::create(curScene);  
	addChild(failureLayer,999); 
}