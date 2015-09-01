#include "ChapterScene.h"
#include "SceneManager.h"
#include "FirstScene.h"
#include "SecondScene.h"
#include "ThirdScene.h"
#include "ModeSelectScene.h"

USING_NS_CC;

Scene* ChapterScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ChapterScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChapterScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto returnItem = MenuItemImage::create(
                                           "button/return.png",
                                           "button/return_selected.png",
                                           CC_CALLBACK_1(ChapterScene::doReturn, this));
    
	returnItem->setScale(visibleSize.width/20/returnItem->getContentSize().width);
	returnItem->setPosition(visibleSize.width-returnItem->getContentSize().width/2,
		visibleSize.height-returnItem->getContentSize().height/2);

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(ChapterScene::menuCloseCallback,this));

	closeItem->setScale(visibleSize.width/800);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - 0.5*(closeItem->getBoundingBox().getMaxX()-closeItem->getBoundingBox().getMinX()) ,
		origin.y + 0.5*(closeItem->getBoundingBox().getMaxY()-closeItem->getBoundingBox().getMinY())));

    // create menu, it's an autorelease object
    auto menu = Menu::create(returnItem, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    // add "ChapterScene" splash screen"
    auto background = Sprite::create("background/bg_001.png");

    // position the sprite on the center of the screen
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	background->setScaleX(visibleSize.width/background->getContentSize().width);
	background->setScaleY(visibleSize.height/background->getContentSize().height);

    // add the sprite as a child to this layer
    this->addChild(background, 0);

	// add the menu icon
	std::string images[] = {"background/bgs_002.png", "background/bgs_003.png", "background/bgs_004.png"};
	int imagesNum = 3;
	m_imageWidth = visibleSize.width * 0.6;
	m_imageHeight = visibleSize.height * 0.6;
	m_imageSpace = visibleSize.width * 0.05;
	float imageOrigin = m_imageSpace + m_imageWidth/2;
	m_xmin = 0;
	m_x = m_xmax = imagesNum*m_imageWidth + (imagesNum+1)*m_imageSpace - visibleSize.width;

	for(int i=0; i<imagesNum; i++)
	{
		std::string image = images[i];
		Sprite *pSprite = Sprite::create(image);
		pSprite->setScaleX(m_imageWidth/pSprite->getContentSize().width);
		pSprite->setScaleY(m_imageHeight/pSprite->getContentSize().height);
		float offset = imageOrigin + (m_imageWidth + m_imageSpace) * i;
		pSprite->setPosition(origin.x+offset, origin.y+visibleSize.height/2);
		pSprite->setTag(i);
		this->addChild(pSprite, 0);
		m_menuIconVector.pushBack(pSprite);
	}
    
	// register event listener
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ChapterScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ChapterScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ChapterScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void ChapterScene::doReturn(Ref* pSender)
{
	Scene* pScene = ModeSelectScene::createScene();
	SceneManager::go(pScene);
}

void ChapterScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void ChapterScene::move(float distance)
{
	Vec2 moveVec(0,0);

	if(m_x+distance >= m_xmax)
	{
		moveVec.x = m_xmax-m_x;
		m_x = m_xmax;
	}
	else if( m_x+distance <= m_xmin)
	{
		moveVec.x = m_xmin-m_x;
		m_x = m_xmin;
	}
	else
	{
		moveVec.x = distance;
		m_x = m_x+distance;
	}
	
	for(Sprite *pSprite : m_menuIconVector)
	{
		pSprite->runAction(MoveBy::create(0, moveVec));
	}
}

bool ChapterScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	m_touchBegan = this->convertTouchToNodeSpace(touch);
	m_touch		= m_touchBegan;

	return true;
}

void ChapterScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	Point touchEnded = this->convertTouchToNodeSpace(touch);
	move(touchEnded.x-m_touch.x);
	m_touch = touchEnded;
}

void ChapterScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	Point touchEnded = this->convertTouchToNodeSpace(touch);
	if(touchEnded == m_touchBegan)
	{
		for(Sprite *pSprite : m_menuIconVector)
		{
			if(pSprite->getBoundingBox().containsPoint(touchEnded))
			{
				Scene* pScene;
				switch (pSprite->getTag())
				{
				case 0:
					pScene = FirstScene::createScene();
					break;
				case 1:
					pScene = SecondScene::createScene();
					break;
				case 2:
					pScene = ThirdScene::createScene();
					break;
				default:
					break;
				}
				SceneManager::go(pScene);
			}
		}
	}
}