#ifndef __ChapterScene_SCENE_H__
#define __ChapterScene_SCENE_H__

#include "cocos2d.h"

class ChapterScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    //virtual void update(float delta);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void doReturn(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(ChapterScene);

	// func
	void move(float distance);

	// callback func
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	cocos2d::Sprite *m_background;
	cocos2d::Vector<cocos2d::Sprite *> m_menuIconVector;

	cocos2d::Point m_touchBegan;
	cocos2d::Point m_touch;

	float m_imageSpace;	
	float m_imageWidth;
	float m_imageHeight;
	float m_x;
	float m_xmax;
	float m_xmin;

};

#endif // __ChapterScene_SCENE_H__
