#ifndef __THIRD_SCENE__
#define __THIRD_SCENE__

#include "cocos2d.h"
#include "GameScene.h"

class ThirdScene : public GameScene
{
public:
	ThirdScene();
	~ThirdScene();

	static cocos2d::Scene* createScene();

	CREATE_FUNC(ThirdScene);
private:
	cocos2d::ParticleSystemQuad* m_emitter;
};

#endif 