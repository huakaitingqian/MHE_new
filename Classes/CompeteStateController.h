#ifndef __COMPETE_STATE_CONTROLLER__
#define __COMPETE_STATE_CONTROLLER__

#include "cocos2d.h"
#include "NPC.h"
#include "BulletManager.h"

class CompeteStateController
{
public:
	CompeteStateController();
	~CompeteStateController();

	static CompeteStateController* create(NPC* curNPC, cocos2d::Vec2 gravity, BulletManager* m_pBulletManger);

	void update(float dt);

	void fire();
private:
	NPC* curNPC;
	cocos2d::Vec2 hitPosition;
	cocos2d::Vec2 gravity;
	BulletManager* bulletManager;
	float time;

	cocos2d::Size visibleSize;
};

#endif