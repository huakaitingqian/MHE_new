#ifndef __FAILURE_LAYER_H__
#define __FAILURE_LAYER_H__

#include "cocos2d.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "ChapterScene.h"
#include "FirstScene.h"
#include "SecondScene.h"
#include "ThirdScene.h"
#include "SurvivalScene.h"
#include "CompeteScene.h"
#include "ModeSelectScene.h"

class FailureLayer :public cocos2d::Layer
{
public:
	FailureLayer();
	~FailureLayer();
	bool init();
	
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event);

	void reBegin(Ref* pSender);
	void goChapter(Ref* pSender);

	static FailureLayer* create(GameSceneType type); 
private:
	GameSceneType curType;
};

#endif