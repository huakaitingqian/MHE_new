#pragma once

#include "cocos2d.h"
#include "TypeDefine.h"

class BulletManager;


class Bullet: public cocos2d::Sprite
{
public:
	Bullet();
	~Bullet();
	static Bullet* createBullet(bulletType type, cocos2d::Point pos, cocos2d::Vec2 velocity, Owner owner, BulletManager* pBulletManager);
	
	/*return true to delete*/
	void update(cocos2d::Vec2 acceleration, float deltaTime);

	bulletType getType();
	cocos2d::ParticleSystemQuad* getEmitter();

	CREATE_FUNC(Bullet);

private:

	bulletType					m_type;
	cocos2d::Vec2				m_velocity;
	cocos2d::ParticleSystemQuad *m_emitter;
	BulletManager*				m_pBulletManager;
	bool						m_leave;
	Owner						m_owner;
	int							m_hit;

	void personCollision();
	void propCollision();
	void bulletCollision();
};
