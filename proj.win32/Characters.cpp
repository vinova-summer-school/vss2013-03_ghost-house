#include "Characters.h"

////////**** METHODS AND INITIALIZERS HERE ***/////////////////////////

// For parent class
CCSprite* character::getSprite() {
	return Sprite;
}

void character::reduceHPBy (short HP) {
	this->HP -= HP;
}

bool character::isDead (){
	if (HP <= 0) return true;
	else return false;
}