#ifndef __PAUSE_LAYER__
#define __PAUSE_LAYER__

#include "cocos2d.h"
#include "SceneManager.h"
#include "GameScene.h"
#include "ChapterScene.h"

class PauseLayer :public cocos2d::Layer
{
public:
	PauseLayer();
	~PauseLayer();
	bool init();
	
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event);

	void goBack(Ref* pSender);
	void reBegin(Ref* pSender);
	void goChapter(Ref* pSender);
	void goReturn(Ref* pSender);

	static cocos2d::Scene* createScene(GameSceneType type);

	CREATE_FUNC(PauseLayer);
private:
	GameSceneType curType;
};

#endif