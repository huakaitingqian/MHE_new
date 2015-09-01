#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Person.h"
#include "Bullet.h"
#include "Player.h"
#include "NPC.h"
#include "BulletManager.h"
#include "StateController.h"

class GameScene : public cocos2d::Layer
{
public:
	GameScene();
	
	//��������
	static cocos2d::Scene* createScene();

	//��ʼ��
	virtual bool init();  
	
	//�˳���ť
	void menuCloseCallback(cocos2d::Ref* pSender);
	//��Ծ��ť
	void jump(Ref* pSender);
	//��ͣ
	void doPause(Ref* pSender);


	//Ѫ����ŭ������������ȴ������
	void setRoleProgressBar();
	void setNpcProgressBar();
	void setRoleHp(unsigned int roleCurrentHp);
	void setRoleRage(unsigned int roleCurrentRage);
	void setNpcHp(unsigned int npcCurrentHp);
	void setNpcRage(unsigned int npcCurrrentRage);
	
	//����������
	void setMenu(GameSceneType curScene);
	void selectedDeafult();
	void selectedSkill1(cocos2d::Ref* pSender);
	void selectedSkill2(cocos2d::Ref* pSender);
	void selectedSkill3(cocos2d::Ref* pSender);

	void setPowerBar();

	////����������
	//void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* unused_event);

	//���㴥������
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event  *event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event  *event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event  *event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event  *event);
	bool contaiinsTouchLocation(cocos2d::Touch* touch);

	//�������������¼�
	void dealEndTouch();

	//����Ѫ����ŭ����
	void updateHPandSP();
	void updateSkill3State();

	void success();
	void failure();

	//����
	virtual void update(float deltaTime);

protected:
	GameSceneType curScene;

	cocos2d::Vector<cocos2d::Sprite*> spritesVector;
	cocos2d::Sprite* background;
	cocos2d::Sprite* powerBarBg;
	cocos2d::ProgressTimer* powerBar;
	Player* _player;
	NPC1* _npc1;
	NPC2* _npc2;
	NPC3* _npc3;
	NPC* _curNPC;
	cocos2d::Sprite* obstacle;
	cocos2d::Vec2 g;
	StateController* stateController;
	bool gameover;
	bool nearFinal;
	cocos2d::Label* timeLabel;
	float time;

	//�����Ѫ����ŭ����
	cocos2d::ProgressTimer* roleHPProgressTimer;
	cocos2d::ProgressTimer* roleSPProgressTimer;
	cocos2d::ProgressTimer* npcHPProgressTimer;
	cocos2d::ProgressTimer* npcSPProgressTimer;

	//3�����ܵİ�ť
	cocos2d::MenuItemSprite* skill1Item;
	cocos2d::MenuItemSprite* skill2Item;
	cocos2d::MenuItemSprite* skill3Item;

	cocos2d::Sprite* skill1CoolSprite;
	cocos2d::Sprite* skill2CoolSprite;
	cocos2d::Sprite* skill3CoolSprite;

	//3�����ܵ���ȴ��
	cocos2d::ProgressTimer* skill1CoolBar;
	cocos2d::ProgressTimer* skill2CoolBar;
	cocos2d::ProgressTimer* skill3CoolBar;

	//3�ּ���Ĭ�ϵ���ȴʱ��
	float skill1CoolDownTime;
	float skill2CoolDownTime;
	float skill3CoolDownTime;

	//3�ּ��ܵ�ǰ�������ȴʱ��
	float skill1NeedTime;
	float skill2NeedTime;
	float skill3NeedTime;

	//��ǰѡ����ӵ�����
	unsigned int currentBulletState;

	//��ɫ���ڵ�Ѫ����ŭ��ֵ
	unsigned int roleCurrentHP;
	unsigned int roleCurrentSP;

	//npc��ǰѪ����ŭ��ֵ
	unsigned int npcCurrentHP;
	unsigned int npcCurrrentSP;

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	float boundingY;

	//�����Ŀ�ʼ��ͽ�����
	cocos2d::Vec2 startPosition;
	cocos2d::Vec2 endPosition;
	cocos2d::Vec2 playerDestination;

	CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
