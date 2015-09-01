#include "SuccessLayer.h"
USING_NS_CC;

SuccessLayer::SuccessLayer()
{
}

SuccessLayer::~SuccessLayer()
{
}

SuccessLayer* SuccessLayer::create(GameSceneType type)
{
	SuccessLayer* successLayer = new SuccessLayer();
	successLayer->curType = type;

	if(successLayer->init())
	{
		successLayer->autorelease();
		return successLayer;
	}
	return NULL;
}

bool SuccessLayer::init()
{
	auto listener1 = EventListenerTouchOneByOne::create();//创建一个触摸监听    
	listener1->setSwallowTouches(true);//设置是否想下传递触摸 

	listener1->onTouchBegan = CC_CALLBACK_2(SuccessLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	auto success_background = Sprite::create("background/pause_background.png");
	success_background->setPosition(Director::sharedDirector()->getVisibleSize()/2);
	addChild(success_background,10);

	auto success_sprite = Sprite::create("background/success.png");
	success_sprite->setPosition(Director::sharedDirector()->getVisibleSize()/2 + Size(0,100));
	addChild(success_sprite, 999);

	auto reBeginItem = MenuItemImage::create(
		"button/rebegin.png",
		"button/rebegin_selected.png",
		CC_CALLBACK_1(SuccessLayer::reBegin, this));
	reBeginItem->setPosition(Director::sharedDirector()->getVisibleSize()/2 + Size(-50, -40));

	auto goChapterItem = MenuItemImage::create(
		"button/goChapter.png",
		"button/goChapter_selected.png",
		CC_CALLBACK_1(SuccessLayer::goChapter, this));
	goChapterItem->setPosition(Director::sharedDirector()->getVisibleSize()/2 + Size(50, -40));

	auto menu = Menu::create(reBeginItem, goChapterItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 999);

	return true;
}

void SuccessLayer::reBegin(Ref* pSender)
{
	CCDirector::sharedDirector()->resume();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
	Scene* pScene;

	switch (curType)
	{
	case GameScene1:
		pScene = FirstScene::createScene();
		break;
	case GameScene2:
		pScene = SecondScene::createScene();
		break;
	case GameScene3:
		pScene = ThirdScene::createScene();
		break;
	case GameScene4:
		pScene = SurvivalScene::createScene();
		break;
	case GameScene5:
		pScene = CompeteScene::createScene();
		break;
	default:
		break;
	}
	SceneManager::go(pScene);
}

void SuccessLayer::goChapter(Ref* pSender)
{
	CCDirector::sharedDirector()->resume();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();

	Scene* pScene;
	switch (curType)
	{
	case GameScene1:
	case GameScene2:
	case GameScene3:
		pScene = ChapterScene::createScene();
		break;
	case GameScene4:
	case GameScene5:
		pScene = ModeSelectScene::createScene();
		break;
	default:
		break;
	}

	SceneManager::go(pScene);
}

bool SuccessLayer::onTouchBegan(Touch* touch, Event  *event)
{
	return true;
}