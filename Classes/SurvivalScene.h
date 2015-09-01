#ifndef __SURVIVAL_SCENE__
#define __SURVIVAL_SCENE__

#include "cocos2d.h"
#include "Player.h"
#include "BulletManager.h"

class SurvivalScene :public cocos2d::Layer
{
public:
	SurvivalScene();
	~SurvivalScene();

	//创建场景
	static cocos2d::Scene* createScene();

	bool init();
	void setPowerBar();
	void setSkillCoolDownBar();
	void setMenu();

	//单点触摸函数
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event  *event);
	bool contaiinsTouchLocation(cocos2d::Touch* touch);

	void dealEndTouch();

	//暂停按钮
	void doPause(Ref* pSender);
	 //退出按钮
	void menuCloseCallback(cocos2d::Ref* pSender);

	virtual void update(float dt);

	void addPlayerMark(int mark);

	void failure();
	
	CREATE_FUNC(SurvivalScene);	
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Vector<cocos2d::Sprite*> spritesVector;
	GameSceneType curScene;
	Player* _curPlayer;
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

	int curBlood;
	cocos2d::Sprite* blood3;
	cocos2d::Sprite* blood2;
	cocos2d::Sprite* blood1;

	cocos2d::Label* playerScoresLabel;
	int playerScores;
};

#endif