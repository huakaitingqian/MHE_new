#pragma once

#include "cocos2d.h"
#include "TypeDefine.h"

class PropManager;

class Prop : public cocos2d::Sprite
{
public:
	Prop();
	~Prop();

	static Prop* createProp(GameSceneType sceneType, PropType propType);
	PropType getType();

	CREATE_FUNC(Prop);

private:
	PropType		m_type;
};

