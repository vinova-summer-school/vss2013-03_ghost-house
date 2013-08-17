#include "GamePlayScene.h"

// Ice item on call
void GamePlay::iceEffectCallback(CCObject* pSender){
	freezetime = 60*4;
	speedMultipler = 0;
	for (int i = 0; i<ghost1Count; i++) ghost1[i].getSprite()->setColor(ccc3(50,50,255));
	for (int i = 0; i<ghost2Count; i++) ghost2[i].getSprite()->setColor(ccc3(50,50,255));
	isFreeze = true;
}

// Ice item on updating
void GamePlay::iceUpdate (){
	if (isFreeze) {
		freezetime--;
		if(freezetime == 0) {
			for (int i = 0; i<ghost1Count; i++) ghost1[i].getSprite()->setColor(ccc3(255,255,255));
			for (int i = 0; i<ghost2Count; i++) ghost2[i].getSprite()->setColor(ccc3(255,255,255));
			speedMultipler = 1;
			isFreeze = false;
		}
	}
}

// Slow item on call
void GamePlay::SlowCallback(CCObject* pSender){
	slowtime = 60*4;
	speedMultipler = 0.25;
	for (int i = 0; i<ghost1Count; i++) ghost1[i].getSprite()->setColor(ccc3(100,100,255));
	for (int i = 0; i<ghost2Count; i++) ghost2[i].getSprite()->setColor(ccc3(100,100,255));
	isSlow = true;
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
}

// Super Damage item on call
void GamePlay::superDamageCallback(CCObject* pSender){
	for (int i = 0; i<ghost1Count; i++) ghost1[i].getSprite()->setColor(ccc3(255,100,100));
	for (int i = 0; i<ghost2Count; i++) ghost2[i].getSprite()->setColor(ccc3(255,100,100));
	for (int i = 0; i<angelCount; i++) angel[i].getSprite()->setColor(ccc3(255,100,100));
	damagetime = 60*4;
	rHP = 100;
	isDamage = true;
}

// Super Damage item on update
void GamePlay::superDamageUpdate (){
	if (isDamage) {
		damagetime--;
		if(damagetime == 0){
			for (int i = 0; i<ghost1Count; i++) ghost1[i].getSprite()->setColor(ccc3(255,255,255));
			for (int i = 0; i<ghost2Count; i++) ghost2[i].getSprite()->setColor(ccc3(255,255,255));
			for (int i = 0; i<angelCount; i++) angel[i].getSprite()->setColor(ccc3(255,255,255));
			rHP = 1;
			isDamage = false;
		}
	}
}
