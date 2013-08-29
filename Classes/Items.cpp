#include "GamePlayScene.h"

// Ice item on call
void GamePlay::iceEffectCallback(CCObject* pSender){
	if (freezeRefreshTime <= 0){
		freezeRefreshTime = 22;			// Set ice item refresh time here (seconds)
		pIceItem->setOpacity (100);
		freezetime = 3;					// Set ice item effect time here (seconds)
		speedMultipler = 0;
		for (int i = 0; i<ghost1Count; i++) ghost1[i].getSprite()->setColor(ccc3(50,50,255));
		for (int i = 0; i<ghost2Count; i++) ghost2[i].getSprite()->setColor(ccc3(50,50,255));
		isFreeze = true;
	}
}

// Ice item on updating
void GamePlay::iceUpdate (float dt){
	if (isFreeze) {
		freezetime -= dt;
		if(freezetime <= 0){
			for (int i = 0; i<ghost1Count; i++) ghost1[i].getSprite()->setColor(ccc3(255,255,255));
			for (int i = 0; i<ghost2Count; i++) ghost2[i].getSprite()->setColor(ccc3(255,255,255));
			speedMultipler = 1;
			isFreeze = false;
		}
	}
	else {
		if (freezeRefreshTime > 0) freezeRefreshTime -= dt;
		else pIceItem->setOpacity (255);
	}
}

// Slow item on call
void GamePlay::SlowCallback(CCObject* pSender){
	if (slowRefreshTime <= 0){
		slowRefreshTime = 24;				// Set slow item refresh time here (seconds)
		pSlowItem->setOpacity (100);
		slowtime = 5;						// Set slow item effect time here (seconds)
		speedMultipler *= 0.25;
		for (int i = 0; i<ghost1Count; i++) ghost1[i].getSprite()->setColor(ccc3(100,100,255));
		for (int i = 0; i<ghost2Count; i++) ghost2[i].getSprite()->setColor(ccc3(100,100,255));
		isSlow = true;
	}
}

// Slow item on update
void GamePlay::slowUpdate (float dt){
	if (isSlow){
		slowtime -= dt;
		if(slowtime <= 0){
			for (int i = 0; i<ghost1Count; i++) ghost1[i].getSprite()->setColor(ccc3(255,255,255));
			for (int i = 0; i<ghost2Count; i++) ghost2[i].getSprite()->setColor(ccc3(255,255,255));
			isSlow = false;
		}
	}
	else {
		if (slowRefreshTime > 0) slowRefreshTime -= dt;
		else pSlowItem->setOpacity (255);
	}
}

// Super Damage item on call
void GamePlay::superDamageCallback(CCObject* pSender){
	if (damageRefreshTime <= 0){
		damageRefreshTime = 22;				// Set super damage item refresh time here (seconds)
		psuperDamageItem->setOpacity (100);
		damagetime = 4;						// Set super damage item effect time here (seconds)
        
		rHP = 100;
        speedMultipler *= 0.5;
        
        streak->setColor(ccc3(255,50,50));
		isDamage = true;
	}
}

// Super Damage item on update
void GamePlay::superDamageUpdate (float dt){
	if (isDamage) {
		damagetime -= dt;
		if(damagetime <= 0){
            streak->setColor(ccc3(255,255,255));
			rHP = 1;
			isDamage = false;
		}
	}
	else {
		if (damageRefreshTime > 0) damageRefreshTime -= dt;
		else psuperDamageItem->setOpacity (255);
	}
}
