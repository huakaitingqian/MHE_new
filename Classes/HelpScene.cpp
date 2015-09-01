#include "HelpScene.h"
#include "StartScene.h"
#include "SceneManager.h"

USING_NS_CC;

HelpScene::HelpScene()
{
}

HelpScene::~HelpScene()
{
}

Scene* HelpScene::createScene()
{
	Scene* scene = Scene::create();

	auto layer = HelpScene::create();

	scene->addChild(layer,0);

	return scene;
}

bool HelpScene::init()
{
	visibleSize = Director::sharedDirector()->getVisibleSize();

	//auto bg = Sprite::create("background/bg_configure.png");
	//bg->setScale(visibleSize.width/bg->getContentSize().width,
	//	visibleSize.height/bg->getContentSize().height);
	//bg->setPosition(visibleSize/2);
	//addChild(bg,0);

	auto help = Sprite::create("background/help.png");
	help->setScale(visibleSize.width/help->getContentSize().width,
		visibleSize.height/help->getContentSize().height);
	help->setPosition(visibleSize/2);
	addChild(help,0);

	//·µ»Ø°´Å¥
	auto returnItem = MenuItemImage::create(
										"button/return.png",
										"button/return_selected.png",
										CC_CALLBACK_1(HelpScene::doReturn, this));
	returnItem->setScale(visibleSize.width/20/returnItem->getContentSize().width);

	returnItem->setPosition(Vec2(visibleSize.width - visibleSize.width/12/2,
		visibleSize.height - visibleSize.height/12/2));

	auto menu = Menu::create(returnItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void HelpScene::doReturn(Ref* pSender)
{
	Scene* pScene = StartScene::createScene();
	SceneManager::go(pScene);
}

