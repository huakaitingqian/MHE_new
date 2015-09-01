#ifndef __HELP_SCENE__
#define __HELP_SCENE__

#include "cocos2d.h"

class HelpScene :public cocos2d::Layer
{
public:
	HelpScene();
	~HelpScene();

	static cocos2d::Scene* createScene();
	bool init();

	void doReturn(Ref* pSender);

	CREATE_FUNC(HelpScene);
private:
	cocos2d::Size visibleSize;

};

#endif