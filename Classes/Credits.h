//THIS IS THE START SCREEN SCENE

#ifndef __CREDITS_H__
#define __CREDITS_H__

#include "cocos2d.h"
#include "StartScreenScene.h"

class Credits : public cocos2d::CCLayer
{
	CCMenuItemImage* pResetScoreItem;
	short clicksRemainingToConfirm;

	CCUserDefault* UserDefault;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuBackCallback(CCObject* pSender);
	void menuResetScoreCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
	CREATE_FUNC(Credits);
};

#endif 