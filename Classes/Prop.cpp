#include "cocos2d.h"
#include "Prop.h"

USING_NS_CC;

Prop::Prop(void)
{
}


Prop::~Prop(void)
{
}

Prop* Prop::createProp(GameSceneType sceneType, PropType propType)
{
	Prop* newProp = Prop::create();
	int type = sceneType*5+propType;
	char str[100];
	int random;
	switch (type)
	{
	case 15:
		random = CCRANDOM_0_1()*8+1;
		sprintf(str, "prop/ppd_0%d.png", random);
		newProp->initWithFile(str);
		newProp->m_type = normal;
		break;
	case 16:
		newProp->initWithFile("prop/ppd_00.png");
		newProp->m_type = bomb;
		break;
	case 18:
		newProp->m_type = normal;
	default:
		newProp->initWithFile("prop/pp_000.png");
		newProp->m_type = normal;
		break;
	}
	return newProp;
}

PropType Prop::getType()
{
	return m_type;
}