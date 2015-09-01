#ifndef __COMPETE_SCENE__
#define __COMPETE_SCENE__

#include "cocos2d.h"
#include "Player.h"
#include "NPC.h"
#include "GameScene.h"
#include "CompeteStateController.h"

class CompeteScene :public cocos2d::Layer
{
public:
	CompeteScene();
	~CompeteScene();

	//创建场景
	static cocos2d::Scene* createScene();

	bool init();
	void setSkillCoolDownBar();
	void setMenu();
	void setPowerBar();

	//单点触摸函数
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event  *event);
	bool contaiinsTouchLocation(cocos2d::Touch* touch);

	void dealEndTouch();

	void doPause(Ref* pSender);
	 //退出按钮
	void menuCloseCallback(cocos2d::Ref* pSender);

	void addPlayerMark(int mark);
	void addNPCMark(int mark);

	void failure();
	void success();

	virtual void update(float dt);

	CREATE_FUNC(CompeteScene);

private:
	Player* _curPlayer;
	NPC* _curNPC;
	GameSceneType curScene;

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Vector<cocos2d::Sprite*> spritesVector;
	cocos2d::ProgressTimer* skillCoolDownBar;
	float skillCoolDownNeedTime;
	float skillCoolDownTime;
	
	cocos2d::Vec2 startPosition;
	cocos2d::Vec2 endPosition;
	cocos2d::Vec2 playerDestination;

	cocos2d::Sprite* powerBarBg;
	cocos2d::ProgressTimer* powerBar;

	BulletManager* g_BulletManager;
	cocos2d::Vec2 g;
	bool gameover;

	cocos2d::Label* playerScoresLabel;
	cocos2d::Label* npcScoresLabel;
	int playerScores;
	int npcScores;

	CompeteStateController* competeStateController;

	cocos2d::Label* timeLabel;
	float time;
};

#endif