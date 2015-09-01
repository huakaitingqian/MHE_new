#ifndef __SUCCESS_LAYER_H__
#define __SUCCESS_LAYER_H__

#include "cocos2d.h"
#include "SceneManager.h"
#include "ChapterScene.h"
#include "FirstScene.h"
#include "SecondScene.h"
#include "ThirdScene.h"
#include "ModeSelectScene.h"
#include "SurvivalScene.h"
#include "CompeteScene.h"

class SuccessLayer :public cocos2d::Layer
{
public:
	SuccessLayer();
	~SuccessLayer();

	bool init();

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event);

	static SuccessLayer* create(GameSceneType type);

	void reBegin(cocos2d::Ref* pSender);
	void goChapter(cocos2d::Ref* pSender);

private:
	GameSceneType curType;
};

#endif