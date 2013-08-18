#include "GamePlayScene.h"

// Ice item on call
void GamePlay::iceEffectCallback(CCObject* pSender){
	if (freezeRefreshTime == 0){
		freezeRefreshTime = 60*8;
		pIceItem->setOpacity (100);
		freezetime = 60*3;
		speedMultipler = 0;
		for (int i = 0; i<ghost1Count; i++) ghost1[i].getSprite()->setColor(ccc3(50,50,255));
		for (int i = 0; i<ghost2Count; i++) ghost2[i].getSprite()->setColor(ccc3(50,50,255));
		isFreeze = true;
	}
}

// Ice item on updating
void GamePlay::iceUpdate (){
	if (isFreeze) {
		freezetime--;
		if(freezetime == 0){
			for (int i = 0; i<ghost1Count; i++) ghost1[i].getSprite()->setColor(ccc3(255,255,255));
			for (int i = 0; i<ghost2Count; i++) ghost2[i].getSprite()->setColor(ccc3(255,255,255));
			speedMultipler = 1;
			isFreeze = false;
		}
	}
	else {
		if (freezeRefreshTime > 0) freezeRefreshTime--;
		else pIceItem->setOpacity (255);
	}
}

// Slow item on call
void GamePlay::SlowCallback(CCObject* pSender){
	if (slowRefreshTime == 0){
		slowRefreshTime = 60*8;
		pSlowItem->setOpacity (100);
		slowtime = 60*4;
		speedMultipler = 0.25;
		for (int i = 0; i<ghost1Count; i++) ghost1[i].getSprite()->setColor(ccc3(100,100,255));
		for (int i = 0; i<ghost2Count; i++) ghost2[i].getSprite()->setColor(ccc3(100,100,255));
		isSlow = true;
	}
}

// Slow item on update
void GamePlay::slowUpdate (){
	if (isSlow){
		slowtime--;
		if(slowtime == 0){
			for (int i = 0; i<ghost1Count; i++) ghost1[i].getSprite()->setColor(ccc3(255,255,255));
			for (int i = 0; i<ghost2Count; i++) ghost2[i].getSprite()->setColor(ccc3(255,255,255));
			speedMultipler = 1;
			isSlow = false;
		}
	}
	else {
		if (slowRefreshTime > 0) slowRefreshTime--;
		else pSlowItem->setOpacity (255);
	}
}

// Super Damage item on call
void GamePlay::superDamageCallback(CCObject* pSender){
	if (damageRefreshTime == 0){
		damageRefreshTime = 60*8;
		psuperDamageItem->setOpacity (100);
		damagetime = 60*4;
		rHP = 100;
		for (int i = 0; i<ghost1Count; i++) ghost1[i].getSprite()->setColor(ccc3(255,100,100));
		for (int i = 0; i<ghost2Count; i++) ghost2[i].getSprite()->setColor(ccc3(255,100,100));
		isDamage = true;
	}
}

// Super Damage item on update
void GamePlay::superDamageUpdate (){
	if (isDamage) {
		damagetime--;
		if(damagetime == 0){
			for (int i = 0; i<ghost1Count; i++) ghost1[i].getSprite()->setColor(ccc3(255,255,255));
			for (int i = 0; i<ghost2Count; i++) ghost2[i].getSprite()->setColor(ccc3(255,255,255));
			rHP = 1;
			isDamage = false;
		}
	}
	else {
		if (damageRefreshTime > 0) damageRefreshTime--;
		else psuperDamageItem->setOpacity (255);
	}
}
