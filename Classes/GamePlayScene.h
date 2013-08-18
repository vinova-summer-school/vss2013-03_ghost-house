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

	int HouseHP;
	float IntervalMultipler;
	int time, stt;
	int freezetime, slowtime, rHP, damagetime, freezeRefreshTime, slowRefreshTime, damageRefreshTime;
	int score, HighScore;
	float speedMultipler;
	short touchingState; //1: just slided into the sprite's frame, 2: sliding in the sprite's frame, 3: sliding outside
	char ScoreString[10], HighScoreString[10], HPString[3]; // Score and HP in string format

	bool isFreeze, isSlow, isDamage; // If Freeze, Slow and SuperDamage item is active

	CCMenuItemImage *pIceItem;
	CCMenuItemImage *pSlowItem;
	CCMenuItemImage *psuperDamageItem;

	CCSprite *PauseDialogBox; //Pause Dialog Box
	CCSprite *GameOverBox; // Game Over dialog box
	CCUserDefault* UserHighScore;

	CCLabelTTF* pScore, *pHP, *pHighScore;

protected:
	CCMotionStreak *streak;

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // Menu items callback
	void menuPauseCallback(CCObject* pSender);				// Pause button
	void menuResumeInPauseBoxCallback(CCObject* pSender);	// Resume Button in the Pause Dialog box
	void menuMainMenuInPauseBoxCallback(CCObject* pSender);	// Main menu button in the Pause Dialog box

	void iceEffectCallback(CCObject* pSender);				// Ice item
	void SlowCallback(CCObject* pSender);					// Slow item
	void superDamageCallback(CCObject* pSender);			// Super Damage item

    // implement the "static node()" method manually
	CREATE_FUNC(GamePlay);

	//void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

	// Update on every frame
	void update (float pDt);
	void iceUpdate ();			// Controls Ice item
	void slowUpdate ();			// Controls Slow item
	void superDamageUpdate ();	// Controls Super Damage item

};

#endif  // __GAMEPLAY_SCENE_H__