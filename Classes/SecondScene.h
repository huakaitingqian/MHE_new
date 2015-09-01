#ifndef __SECOND_SCENE__
#define __SECOND_SCENE__

#include "cocos2d.h"
#include "GameScene.h"

class SecondScene : public GameScene
{
public:
	SecondScene();
	~SecondScene();

	static cocos2d::Scene* createScene();

	CREATE_FUNC(SecondScene);

private:
	cocos2d::ParticleSystemQuad* m_emitter;

};

#endif 