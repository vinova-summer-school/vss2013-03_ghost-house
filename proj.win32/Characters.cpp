#include "Characters.h"

////////**** METHODS AND INITIALIZERS HERE ***/////////////////////////


// For ghost1
CCSprite* ghost1::getSprite() {
	return Sprite;
}

void ghost1::reduceHPBy (short HP) {
	this->HP -= HP;
}

bool ghost1::isDead (){
	if (HP <= 0) return true;
	else return false;
}

// For ghost2
CCSprite* ghost2::getSprite() {
	return Sprite;
}

void ghost2::reduceHPBy (short HP) {
	this->HP -= HP;
}

bool ghost2::isDead() {
	if (HP <= 0) return true;
	else return false;
}

//House

void House::reduceHPBy (short HP) {
	this->HP -= HP;
}

bool House::isDead() {
	if (HP <= 0) return true;
	else return false;
}