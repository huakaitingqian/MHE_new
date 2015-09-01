#pragma once

#include "cocos2d.h"
#include "Bullet.h"
#include "PropManager.h"



class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	static BulletManager* create(GameSceneType gamescenetype, cocos2d::Layer* curLayer, cocos2d::Vector<cocos2d::Sprite*>* pSpriteVector, cocos2d::Vec2 g);	/* init bullet manager */
	void update(float deltaTime);												/* return true delete bullet */
	void shoot(bulletType type, Owner owner, cocos2d::Point pos, cocos2d::Vec2 velocity);
	void deleteBullet(Bullet* pBullet);
	void bulletExplode(Bullet* pBullet);
	cocos2d::Vector<Bullet*>* getBulletVector();
	cocos2d::Vector<cocos2d::Sprite*>* getSpriteVector();
	cocos2d::Layer* getLayer();
	PropManager* getPropManager();

	void clean();
	GameSceneType SceneType;

	CC_SYNTHESIZE_RETAIN(cocos2d::Animation*, m_normalAnimation, NormalAnimation);
	CC_SYNTHESIZE_RETAIN(cocos2d::Animation*, m_specialAnimation, SpecialAnimation);
	CC_SYNTHESIZE_RETAIN(cocos2d::Animation*, m_stunAnimation, StunlAnimation);

private:
	
	cocos2d::Layer*					m_layer;
	cocos2d::Vector<Bullet*>		m_BulletVector;
	cocos2d::Vector<Bullet*>		m_BulletDeleteVector;
	cocos2d::Vec2					m_g;
	cocos2d::Vector<cocos2d::Sprite*>*		m_pSpriteVector;
	void  shootByCita(float cita, float module);

	PropManager* m_propManager;
};
