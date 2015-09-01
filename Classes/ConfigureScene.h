#ifndef __CONFIGURE_SCENE_H__
#define __CONFIGURE_SCENE_H__

#include "cocos2d.h"
#include "ui/UICheckBox.h"


class ConfigureScene :public cocos2d::Layer
{
public:
	ConfigureScene();
	~ConfigureScene();

	static cocos2d::Scene* createScene();

	bool init();

	void selectedMusicEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type);
	void selectedMusicEffectEvent(Ref* pSender, cocos2d::ui::CheckBox::EventType type);

	void doReturn(Ref* pSender);

	CREATE_FUNC(ConfigureScene);

private:
	cocos2d::Size visibleSize;
};

#endif