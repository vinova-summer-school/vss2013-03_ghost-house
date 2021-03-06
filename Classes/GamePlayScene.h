#ifndef __GAMEPLAY_SCENE_H__
#define __GAMEPLAY_SCENE_H__
//MAIN GAME PLAY SCENE

#include "cocos2d.h"
#include "Characters.h"
#include "StartScreenScene.h"
#include "PauseLayer.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;

class GamePlay : public cocos2d::CCLayer
{
    CCSize size;
    
	short ghost1Count, ghost2Count, angelCount; // Numbers of sprites that will be shown
	Ghost1 ghost1[5];
	Ghost2 ghost2[5];
	Angel angel [5];

	int HouseHP;
	float IntervalMultipler, speedMultipler;
	int stt, wave;
	float IntervalTime, StarTime, SmokeTime, freezetime, slowtime, rHP, damagetime, freezeRefreshTime, slowRefreshTime, damageRefreshTime;
	float score, HighScore;
	short touchingState; //1: just slided into the sprite's frame, 2: sliding in the sprite's frame, 3: sliding outside
	char ScoreString[22], HighScoreString[13], HPString[8], WaveString[10]; // Score and HP in string format
	short first_item, second_item;

	bool isFreeze, isSlow, isDamage, isShowingStar; // If Freeze, Slow and SuperDamage item is active

	PauseLayer *pauseLayer;

	CCMenuItemImage *pRecoveryHP;

	CCMenuItemImage *pPauseItem;
	CCMenuItemImage *pIceItem;
	CCMenuItemImage *pSlowItem;
	CCMenuItemImage *psuperDamageItem;

	CCSprite *GameOverBox; // Game Over dialog box
	CCUserDefault* UserDefault;

	CCLabelTTF* pScore, *pHP, *pHighScore, *pWave, *pGameOver;

	CCMotionStreak *streak;
	CCParticleSmoke* m_emitter;

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // Menu items callback
	void setAllMenuItemsEnabled (const bool& isEnable);
	
	void menuPauseCallback(CCObject* pSender);				// Pause button

	void RecoveryHPCallback(CCObject* pSender);
	void iceEffectCallback(CCObject* pSender);				// Ice item
	void SlowCallback(CCObject* pSender);					// Slow item
	void superDamageCallback(CCObject* pSender);			// Super Damage item

    // implement the "static node()" method manually
	CREATE_FUNC(GamePlay);

	//void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

	// Update on every frame
	void update (float dt);
	void iceUpdate (float dt);			// Controls Ice item
	void slowUpdate (float dt);			// Controls Slow item
	void superDamageUpdate (float dt);	// Controls Super Damage item

};

#endif  // __GAMEPLAY_SCENE_H__