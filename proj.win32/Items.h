#ifndef __ITEMS_H__
#define __ITEMS_H__

// Ice item on call
void iceCall (int& freezetime, float& speedMultipler, bool& isFreeze){
	freezetime = 60*4;
	speedMultipler = 0;
	isFreeze = true;
}

// Ice item on updating
void iceUpdate (int& freezetime, float& speedMultipler, bool& isFreeze){
	if (isFreeze) {
		freezetime--;
		if(freezetime == 0) {
			isFreeze = false;
			speedMultipler = 1;
		}
	}
}


// Slow item on call
void slowCall (int& slowtime, float& speedMultipler, bool& isSlow){
	slowtime = 60*4;
	speedMultipler = 0.25;
	isSlow = true;
}

// Slow item on update
void slowUpdate (int& slowtime, float& speedMultipler, bool& isSlow){
	if (isSlow){
		slowtime--;
		if(slowtime == 0){
			isSlow = false;
			speedMultipler = 1;
		}
	}
}


// SuperDamage item on call
void superDamageCall (int& damagetime, int& rHP, bool& isDamage){
	damagetime = 60*4;
	rHP = 100;
	isDamage = true;
}

void superDamageUpdate (int& damagetime, int& rHP, bool& isDamage){
	if (isDamage) {
		damagetime--;
		if(damagetime == 0){
			isDamage = false;
			rHP = 1;
		}
	}
}


#endif // __ITEMS_H__