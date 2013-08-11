#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__
//MAIN GAME PLAY SCENE

#include "cocos2d.h"
#include "Characters.h"
#include "StartScreenScene.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;

class GamePlay : public cocos2d::CCLayer
{
	short ghost1Count, ghost2Count, angelCount; // Numbers of sprites that will be shown
	ghost1 ghost1[5];
	ghost2 ghost2[5];
	angel angel [5];

	int time, stt, freezetime, slowtime, rHP, damagetime;
	int score;
	float speedMultipler;
	short touchingState; //1: just slided into the sprite's frame, 2: sliding in the sprite's frame, 3: sliding outside
	char Score[10], HHP[3];
	bool isFreeze, isSlow, isDamage;

	CCSprite *PauseDialogBox;
	CCSprite *GameOverBox;

	CCLabelTTF* pScore, *pHHP;

protected:
	CCMotionStreak *streak;

public:
	int HouseHP;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    //void menuCloseCallback(CCObject* pSender);
	void menuPauseCallback(CCObject* pSender);
	void menuResumeInPauseBoxCallback(CCObject* pSender);
	void menuMainMenuInPauseBoxCallback(CCObject* pSender);
	void iceEffectCallback(CCObject* pSender);
	void SlowCallback(CCObject* pSender);
	void superDamageCallback(CCObject* pSender);
    // implement the "static node()" method manually
	CREATE_FUNC(GamePlay);

	//void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

	void update (float pDt);

};

#endif  // __GAMEPLAY_SCENE_H__