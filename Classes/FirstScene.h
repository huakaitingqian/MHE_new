#ifndef __FIRST_SCENE_H__
#define __FIRST_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"

class FirstScene : public GameScene
{
public:
	FirstScene();
	~FirstScene();

	static cocos2d::Scene* createScene();

	CREATE_FUNC(FirstScene);
private:
	cocos2d::ParticleSystemQuad* m_emitter;
};

#endif // __FirstScene_SCENE_H__
