#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__
//MAIN GAME PLAY SCENE

#include <math.h>
#include "cocos2d.h"
#include "Characters.h"
#include "StartScreenScene.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;

class GamePlay : public cocos2d::CCLayer
{
	ghost1 ghost1;
	ghost2 ghost2;
	House House;
	angel angel;
	short touchingState; //1: just slided into the sprite's frame, 2: sliding in the sprite's frame, 3: sliding outside

	CCSprite *PauseDialogBox;
	CCSprite *GameOverBox;

protected:
	CCMotionStreak *streak;

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    //void menuCloseCallback(CCObject* pSender);
	void menuPauseCallback(CCObject* pSender);
	void menuResumeInPauseBoxCallback(CCObject* pSender);
	void menuMainMenuInPauseBoxCallback(CCObject* pSender);

    // implement the "static node()" method manually
	CREATE_FUNC(GamePlay);

	//void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

	void update (float pDt);

};

#endif  // __GAMEPLAY_SCENE_H__