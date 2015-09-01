#include "PauseLayer.h"
#include "FirstScene.h"
#include "SecondScene.h"
#include "ThirdScene.h"
#include "SurvivalScene.h"
#include "CompeteScene.h"
#include "ModeSelectScene.h"

USING_NS_CC;

PauseLayer::PauseLayer()
{
}

PauseLayer::~PauseLayer()
{
}

Scene* PauseLayer::createScene(GameSceneType type)
{
	Scene* scene = Scene::create();
	Size size = Director::sharedDirector()->getVisibleSize();

	PauseLayer* layer = PauseLayer::create();
	layer->curType = type;
	scene->addChild(layer, 111);
	return scene;
}

bool PauseLayer::init()
{
	auto listener1 = EventListenerTouchOneByOne::create();//创建一个触摸监听    
	listener1->setSwallowTouches(true);//设置是否想下传递触摸 

	listener1->onTouchBegan = CC_CALLBACK_2(PauseLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	auto pause_background = Sprite::create("background/pause_background.png");
	pause_background->setPosition(Director::sharedDirector()->getVisibleSize()/2);
	addChild(pause_background,10);

	auto reBeginItem = MenuItemImage::create(
		"button/rebegin.png",
		"button/rebegin_selected.png",
		CC_CALLBACK_1(PauseLayer::reBegin, this));
	reBeginItem->setPosition(Vec2(Director::sharedDirector()->getVisibleSize()/2));

	auto goBackItem = MenuItemImage::create(
		"button/begin.png",
		"button/begin_selected.png",
		CC_CALLBACK_1(PauseLayer::goBack, this));
	goBackItem->setPosition(Director::sharedDirector()->getVisibleSize()/2 - Size(70,0));


	auto goChapterItem = MenuItemImage::create(
		"button/goChapter.png",
		"button/goChapter_selected.png",
		CC_CALLBACK_1(PauseLayer::goChapter, this));
	goChapterItem->setPosition(Director::sharedDirector()->getVisibleSize()/2 + Size(70,0));

	auto menu = Menu::create(reBeginItem, goBackItem, goChapterItem,NULL);

	menu->setPosition(Vec2::ZERO);
	
	this->addChild(menu, 999);

	return true;
}

void PauseLayer::reBegin(Ref* pSender)
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

void PauseLayer::goBack(Ref* pSender)
{
	CCDirector::sharedDirector()->resume();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();  
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
	removeFromParent();
}

void PauseLayer::goChapter(Ref* pSender)
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

bool PauseLayer::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}