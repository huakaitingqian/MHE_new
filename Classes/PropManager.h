#pragma once

#include "cocos2d.h"
#include "Prop.h"

class BulletManager;

class PropManager
{
public:
	PropManager(void);
	~PropManager(void);

	static PropManager* create(BulletManager* pBulletManager);
	void update(float deltaTime);
	cocos2d::Vector<Prop*>* getPropVector();
	void deleteProp(Prop* pProp);

	CC_SYNTHESIZE_RETAIN(cocos2d::Animation*, m_animation1, Animation1);
	CC_SYNTHESIZE_RETAIN(cocos2d::Animation*, m_animation2, Animation2);
	CC_SYNTHESIZE_RETAIN(cocos2d::Animation*, m_animation3, Animation3);
	CC_SYNTHESIZE_RETAIN(cocos2d::Animation*, m_animation4, Animation4);
	CC_SYNTHESIZE_RETAIN(cocos2d::Animation*, m_animation5, Animation5);
	CC_SYNTHESIZE_RETAIN(cocos2d::Animation*, m_animation6, Animation6);

private:
	BulletManager* m_bulletManager;
	cocos2d::Vector<Prop*> m_propVector;
	cocos2d::Vector<Prop*> m_propDeleteVector;

	float m_curTime;
	float m_nextTime;
	float m_time;
	float m_timeVariance;
	float m_duration;
	float m_durationVariance;

	void classicUpdate(float deltaTime);
	void survivalUpdate(float deltaTime);
	void competitionUpdate(float deltaTime);
};

