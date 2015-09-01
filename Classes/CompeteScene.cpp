#include "CompeteScene.h"
#include "PauseLayer.h"
#include "FailureLayer.h"
#include "SuccessLayer.h"
USING_NS_CC;
extern bool OpenMusicEffect;
extern bool OpenMusic;

CompeteScene::CompeteScene():
	skillCoolDownNeedTime(0),skillCoolDownTime(1),
	_curPlayer(nullptr),_curNPC(nullptr)
{
	curScene = GameScene5;
	playerScores = 0;
	npcScores = 0;
	time = 180;
	gameover = false;
}

CompeteScene::~CompeteScene()
{
}

Scene* CompeteScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	
	// 'layer' is an autorelease object
	auto layer = CompeteScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool CompeteScene::init()
{
	visibleSize = Director::sharedDirector()->getVisibleSize();

	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(CompeteScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(CompeteScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(CompeteScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	//背景
	auto bg = Sprite::create("background/bg_compete.png");
	bg->setScale(visibleSize.width/bg->getContentSize().width,
		visibleSize.height/bg->getContentSize().height);
	bg->setPosition(visibleSize/2);
	addChild(bg,0);

	//倒计时
	timeLabel = Label::createWithBMFont("fonts/bitmapFontTest.fnt","180");
	timeLabel->setPosition(visibleSize.width/2, visibleSize.height*7/8);
	addChild(timeLabel,10);

	//设置技能、菜单、力度条
	setSkillCoolDownBar();
	setMenu();
	setPowerBar();

	//设置player和npc的分数
	playerScoresLabel = Label::createWithBMFont("fonts/bitmapFontTest.fnt","0");
	playerScoresLabel->setPosition(visibleSize.width/8,visibleSize.height*7/8);
	addChild(playerScoresLabel,2);

	npcScoresLabel = Label::createWithBMFont("fonts/bitmapFontTest.fnt","0");
	npcScoresLabel->setPosition(visibleSize.width*7/8,visibleSize.height*7/8);
	addChild(npcScoresLabel,2);

	//创建人物
	_curPlayer = Player::create();
	_curPlayer->setScale((visibleSize.height*3/16)/_curPlayer->getContentSize().height);
	_curPlayer->setPosition(visibleSize.width/8,visibleSize.height*3/16+10);
	_curPlayer->setFlipX(true);
	_curPlayer->setTag(1);
	addChild(_curPlayer,1);
	_curPlayer->normalAction();

	//创建npc
	_curNPC = NPC1::create();
	_curNPC->setScale((visibleSize.height*3/16)/_curNPC->getContentSize().height);
	_curNPC->setPosition(visibleSize.width*7/8,visibleSize.height*3/16+10);
	_curNPC->setTag(2);
	addChild(_curNPC,1);
	_curNPC->normalAction();

	//将player添加到spriteVector中
	spritesVector.pushBack(_curPlayer);
	spritesVector.pushBack(_curNPC);

	//设置重力以及初始化BulletManager
	g = Vec2(0, -800);
	g_BulletManager = BulletManager::create(curScene,(Layer*)this, &spritesVector, g);
	
	competeStateController = CompeteStateController::create(_curNPC,g,g_BulletManager);

	this->scheduleUpdate();

	return true;
}

void CompeteScene::setSkillCoolDownBar()
{
	auto skillCoolDownBg = Sprite::create("skill/skill21.png");
	skillCoolDownBg->setPosition(40,40);
	addChild(skillCoolDownBg, 2);

	auto skill1CoolSprite = Sprite::create("skill/skill21_disabled.png");
	skillCoolDownBar = ProgressTimer::create(skill1CoolSprite);

	skillCoolDownBar->setType(kCCProgressTimerTypeBar);
	skillCoolDownBar->setMidpoint(ccp(0.5,0));
	skillCoolDownBar->setBarChangeRate(ccp(0,1));
	skillCoolDownBar->setPercentage(0);
	skillCoolDownBar->setPosition(40,40);
	addChild(skillCoolDownBar,3);
}

void CompeteScene::setMenu()
{
	auto visibleSize = Director::sharedDirector()->getVisibleSize();
	auto origin = Director::sharedDirector()->getVisibleOrigin();

	//暂停按钮
	auto pauseItem = MenuItemImage::create(
										"button/pause.png",
										"button/pause_selected.png",
										CC_CALLBACK_1(CompeteScene::doPause, this));
	pauseItem->setScale(visibleSize.width/20/pauseItem->getContentSize().width);

	pauseItem->setPosition(Vec2(visibleSize.width - visibleSize.width/12/2,
		visibleSize.height - visibleSize.height/12/2));

	//退出按钮
	auto closeItem = MenuItemImage::create(
										   "CloseNormal.png",
										   "CloseSelected.png",
										   CC_CALLBACK_1(CompeteScene::menuCloseCallback, this));
	
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
								origin.y + closeItem->getContentSize().height/2));

	auto menu = Menu::create(pauseItem, closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
}

void CompeteScene::setPowerBar()
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

void CompeteScene::doPause(Ref* pSender)
{
	CCDirector::sharedDirector()->pause();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();  
	Scene *pauseLayer = PauseLayer::createScene(curScene);  
	addChild(pauseLayer,999);
}

void CompeteScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}

void CompeteScene::update(float dt)
{
	g_BulletManager->update(dt);

	if(!gameover)
		competeStateController->update(dt);

	if(!gameover)
	{
		if(_curPlayer->getActionState() == Move_Action)
		{
			if(playerDestination.x > _curPlayer->getPosition().x+1 
				&& _curPlayer->getBoundingBox().getMaxX()+2 < visibleSize.width-30)
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

	//更新时间
	time -= dt;
	if(time < 0)
	{
		if(!gameover)
		{
			if(playerScores > npcScores)
			{
				gameover = true;
				CallFunc *callbackSuccess = CallFunc::create(std::bind(&CompeteScene::success, this));
				_curPlayer->victoryAction();
				_curNPC->failAction();
				if(OpenMusic)
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/success.mp3");
				runAction(Sequence::create(DelayTime::create(5),callbackSuccess,NULL));
				//success();
			}
			else
			{
				gameover = true;
				CallFunc *callbackFailure = CallFunc::create(std::bind(&CompeteScene::failure, this));
				_curPlayer->failAction();
				_curNPC->victoryAction();
				if(OpenMusic)
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/failure.mp3");
				runAction(Sequence::create(DelayTime::create(5),callbackFailure,NULL));
				//failure();
			}
		}
	}
	else
	{
		char string[15] = {0};
		sprintf(string, "%d", (int)time);
		timeLabel->setString(string);
	}
}

bool CompeteScene::contaiinsTouchLocation(cocos2d::Touch* touch)
{
	return _curPlayer->getBoundingBox().containsPoint(convertTouchToNodeSpace(touch));
}

bool CompeteScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event)
{
	if(!gameover)
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
	return false;
}

void CompeteScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event)
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

void CompeteScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event)
{
	endPosition = touch->getLocation();
	powerBarBg->setVisible(false);
	powerBar->setVisible(false);
	dealEndTouch();
}

void CompeteScene::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event  *event)
{

}

void CompeteScene::dealEndTouch()
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
		velocity.x= (endPosition.x - startPosition.x) / visibleSize.height * 2500 ;
		velocity.y= (endPosition.y - startPosition.y) /visibleSize.height * 2500;
	
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

void CompeteScene::addPlayerMark(int mark)
{
	playerScores += mark;
	
	char string[15] = {0};
	sprintf(string, "%d", (int)playerScores);
	playerScoresLabel->setString(string);
}

void CompeteScene::addNPCMark(int mark)
{
	npcScores += mark;

	char string[15] = {0};
	sprintf(string, "%d", (int)npcScores);
	npcScoresLabel->setString(string);
}

void CompeteScene::success()
{
	gameover = true;
	CCDirector::sharedDirector()->pause();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();  
	SuccessLayer *successLayer = SuccessLayer::create(curScene);  
	addChild(successLayer,999);
}

void CompeteScene::failure()
{
	gameover = true;
	CCDirector::sharedDirector()->pause();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();  
	FailureLayer *failureLayer = FailureLayer::create(curScene);  
	addChild(failureLayer,999); 
}