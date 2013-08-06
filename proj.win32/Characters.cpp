#include "Characters.h"

////////**** METHODS AND INITIALIZERS HERE ***/////////////////////////

// For parent class
void character::init (){
	initPos = Sprite->getPosition();
	pos = initPos;
	moveStyle = rand () % 4;
}

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

void character::move (){
	switch(moveStyle){
		case 0:
			pos.x -= 1;
			break;
		case 1:
			pos.x -= 2;
			break;
		case 2:
			pos.x -= 3;
			break;
		case 3:
			pos.x -= 1;
			pos.y = initPos.y + 30*sin (0.05*pos.x);
			break;
	}
	if (pos.x <= 80) Sprite->setVisible(false);
	Sprite->setPosition(pos);
}