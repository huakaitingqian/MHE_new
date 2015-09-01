#include "FailureLayer.h"
USING_NS_CC;

FailureLayer::FailureLayer()
{
}

FailureLayer::~FailureLayer()
{
}

FailureLayer* FailureLayer::create(GameSceneType type)
{
	FailureLayer* failureLayer = new FailureLayer();
	failureLayer->curType = type;

	if(failureLayer->init())
	{
		return failureLayer;
	}
	return NULL;
}

bool FailureLayer::init()
{
	auto listener1 = EventListenerTouchOneByOne::create();//创建一个触摸监听    
	listener1->setSwallowTouches(true);//设置是否想下传递触摸 

	listener1->onTouchBegan = CC_CALLBACK_2(FailureLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);


	auto failure_background = Sprite::create("background/pause_background.png");
	failure_background->setPosition(Director::sharedDirector()->getVisibleSize()/2);
	addChild(failure_background,10);

	auto failure_sprite = Sprite::create("background/failure.png");
	failure_sprite->setPosition(Director::sharedDirector()->getVisibleSize()/2 + Size(0,100));
	addChild(failure_sprite, 11);

	auto reBeginItem = MenuItemImage::create(
		"button/rebegin.png",
		"button/rebegin_selected.png",
		CC_CALLBACK_1(FailureLayer::reBegin, this));
	reBeginItem->setPosition(Director::sharedDirector()->getVisibleSize()/2 +Size(-50,-40));

	auto goChapterItem = MenuItemImage::create(
		"button/goChapter.png",
		"button/goChapter_selected.png",
		CC_CALLBACK_1(FailureLayer::goChapter, this));
	goChapterItem->setPosition(Director::sharedDirector()->getVisibleSize()/2 + Size(50,-40));

	auto menu = Menu::create(reBeginItem, goChapterItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 11);

	return true;
}

void FailureLayer::reBegin(Ref* pSender)
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

void FailureLayer::goChapter(Ref* pSender)
{
	CCDirector::sharedDirector()->resume();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();

	Scene* pScene ;
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

bool FailureLayer::onTouchBegan(Touch* touch, Event  *event)
{
	return true;
}