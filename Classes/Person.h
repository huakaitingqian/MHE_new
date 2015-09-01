#ifndef __PERSON_H__
#define __PERSON_H__

#include "cocos2d.h"
#include "Bullet.h"

typedef enum {
	Normal_Action = 0,
	Move_Action,
	Jump_Action,
	Fire_Action,
	Attacked_Action,
	Vectory_Action,
	Fail_Action,
	Frozen_Action,
} ActionState;

class Person: public cocos2d::Sprite
{
public:
	Person();
	~Person();

	void normalAction();
	void fireAction();
	void attackedAction();
	void frozenAction();
	void moveAction();
	void jumpAction();
	void jumpTo(cocos2d::Vec2 v, cocos2d::Size visibleSize, float boundingX, float boundingY);
	void jumpToEnd();
	void victoryAction();
	void failAction();
	void jumpActionEnd();
	void attacked(bulletType type, GameSceneType scenetype);
	void getProp(GameSceneType scene,PropType type);
	void getProp();
	void notHit();

	 // ����ÿ��״̬������get/set����
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _normalAction, NormalAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _attackedAction, AttackedAction);

	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _frozenAction, FrozenAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _holeAction, HoleAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _netAction, NetAction);
	
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _fireAction, FireAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _moveAction, MoveAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _jumpAction, JumpAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _victoryAction, VictoryAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _failAction, FailAction);

	// ����ĵ�ǰ״̬
	CC_SYNTHESIZE(ActionState, _currentState, ActionState);

	//����ĳ���
	CC_SYNTHESIZE(bool, _faceRight, FaceDirection);

	// ����Ѫ����ŭ����
	CC_SYNTHESIZE(int, _hp, HP); // ����ֵ
	CC_SYNTHESIZE(int, _sp, SP); // ŭ��ֵ

	CC_SYNTHESIZE(int, _totalHp, TotalHP); // ����ֵ
	CC_SYNTHESIZE(int, _totalSp, TotalSP); // ŭ��ֵ

	void update(float dt, cocos2d::Vec2 g);

protected:
	cocos2d::Animation* createAnimation(const char* fmt, int count, float fps);

	char roleName[100];
	char attackedSound[100];
	cocos2d::SpriteFrameCache* cache;
	bool changeState(ActionState state);
	cocos2d::Vec2 personVelocity;
	float boundingX;
	float boundingY;
private:
	
	bool isJumping;
};

#endif