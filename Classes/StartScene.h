#ifndef __StartScene_H__
#define __StartScene_H__

#include "cocos2d.h"

class StartScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	
	void onNewGame(cocos2d::Object* pSender);

	void onConfigure(cocos2d::Object* pSender);

	void onHelp(cocos2d::Object* pSender);

	//void onNewGame(cocos2d::Object* pSender);
	
	// implement the "static create()" method manually
	CREATE_FUNC(StartScene);
};

#endif // __StartScene_H__
