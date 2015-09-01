#ifndef __MODE_SELECT_SCENE__
#define __MODE_SELECT_SCENE__

#include "cocos2d.h"
#include "SceneManager.h"

class ModeSelectScene :public cocos2d::Layer
{
public:
	ModeSelectScene();
	~ModeSelectScene();

	static cocos2d::Scene* createScene();

	bool init();

	void goClassicalScene(Ref* pSender);
	void goSurvivalScene(Ref* pSender);
	void goCompeteScene(Ref* pSender);
	void doReturn(Ref* pSender);

	CREATE_FUNC(ModeSelectScene);

private:

};

#endif