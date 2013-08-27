//THIS IS THE PREFERENCES SCREEN SCENE

#ifndef __PREFERENCES_SCENE_H__
#define __PREFERENCES_SCENE_H__

#include "StartScreenScene.h"

class Preferences : public cocos2d::CCLayer
{
	CCMenuItemImage *pIceItem;
	CCMenuItemImage *pSlowItem;
	CCMenuItemImage *psuperDamageItem;

	short numItemsSelected;
	short first_item, second_item;

	CCLabelTTF *pFirstItem, *pSecondItem, *pThirdItem;

	CCUserDefault *effectUserDefault;

public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();
    
	// a selector callback
	void menuBackCallback(CCObject* pSender);
	void iceEffectCallback(CCObject* pSender);
	void SlowCallback(CCObject* pSender);
	void superDamageCallback(CCObject* pSender);
    
	// implement the "static node()" method manually
	CREATE_FUNC(Preferences);
};

#endif // __PREFERENCES_SCENE_H__
