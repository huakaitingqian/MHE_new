#include "ConfigureScene.h"
#include "StartScene.h"
#include "SceneManager.h"
#include <SimpleAudioEngine.h>

USING_NS_CC;
using namespace ui;

extern bool OpenMusic;
extern bool OpenMusicEffect;

ConfigureScene::ConfigureScene()
{
}

ConfigureScene::~ConfigureScene()
{
}

Scene* ConfigureScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	
	// 'layer' is an autorelease object
	auto layer = ConfigureScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool ConfigureScene::init()
{
	visibleSize = Director::sharedDirector()->getVisibleSize();

	auto bg = Sprite::create("background/bg_configure.png");
	bg->setScale(visibleSize.width/bg->getContentSize().width,
		visibleSize.height/bg->getContentSize().height);
	bg->setPosition(visibleSize/2);
	addChild(bg);

	auto musicSetLabel =  Sprite::create("button/music_text.png");
	musicSetLabel->setPosition(visibleSize.width*2/5,
		visibleSize.height*2/3);
	addChild(musicSetLabel,1);

	CheckBox* musicCheckBox = CheckBox::create("button/check_box_normal.png",
											  "button/check_box_normal_press.png",
											  "button/check_box_active.png",
											  "button/check_box_normal_disable.png",
											  "button/check_box_active_disable.png");
	if(OpenMusic)
		musicCheckBox->setSelectedState(true);
	musicCheckBox->setPosition(Vec2(visibleSize.width*3/5, visibleSize.height*2/3));	
	musicCheckBox->addEventListener(CC_CALLBACK_2(ConfigureScene::selectedMusicEvent, this));
	addChild(musicCheckBox,1);

	auto* musicEffectSetLabel =  Sprite::create("button/musicEffect_text.png");
	musicEffectSetLabel->setPosition(visibleSize.width*2/5,
		visibleSize.height/3);
	addChild(musicEffectSetLabel,1);

	CheckBox* musicEffectCheckBox = CheckBox::create("button/check_box_normal.png",
											  "button/check_box_normal_press.png",
											  "button/check_box_active.png",
											  "button/check_box_normal_disable.png",
											  "button/check_box_active_disable.png");
	if(OpenMusicEffect)
		musicEffectCheckBox->setSelectedState(true);
	musicEffectCheckBox->setPosition(Vec2(visibleSize.width*3/5, visibleSize.height/3));	
	musicEffectCheckBox->addEventListener(CC_CALLBACK_2(ConfigureScene::selectedMusicEffectEvent, this));
	addChild(musicEffectCheckBox,1);

	//·µ»Ø°´Å¥
	auto returnItem = MenuItemImage::create(
										"button/return.png",
										"button/return_selected.png",
										CC_CALLBACK_1(ConfigureScene::doReturn, this));
	returnItem->setScale(visibleSize.width/20/returnItem->getContentSize().width);

	returnItem->setPosition(Vec2(visibleSize.width - visibleSize.width/12/2,
		visibleSize.height - visibleSize.height/12/2));

	auto menu = Menu::create(returnItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void ConfigureScene::selectedMusicEvent(Ref* pSender, CheckBox::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::CheckBox::EventType::SELECTED:
		OpenMusic = true;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/background.mp3", true);
		break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
		OpenMusic = false;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
		break;
	default:
		break;
	}
}

void ConfigureScene::selectedMusicEffectEvent(Ref* pSender, CheckBox::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::CheckBox::EventType::SELECTED:
		OpenMusicEffect = true;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/background.mp3", true);
		break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
		OpenMusicEffect = false;
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
		break;
	default:
		break;
	}
}

void ConfigureScene::doReturn(Ref* pSender)
{
	Scene* pScene = StartScene::createScene();
	SceneManager::go(pScene);
}

