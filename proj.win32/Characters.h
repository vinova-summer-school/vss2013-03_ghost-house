#ifndef __CHARACTERS_H__
#define __CHARACTERS_H__

#include "cocos2d.h"
#include <ctime>

using namespace cocos2d;

// Parent class to define some similar character types
class character {
protected:
	CCSprite *Sprite;		// the image
	short initHP, HP;		// Init Health Points and the current one
	short moveStyle;		// Different move styles
	CCPoint initPos, pos;	// Init position, current position
	bool isGhost;			// Determine if the character is a ghost


public:
	//int a;
	// Character initialization
	void init(){
		Sprite->setPosition (ccp(520, rand() % 245 + 30));	// Init the position
		initPos = Sprite->getPosition();						// Get the init position
		pos = initPos;										// At first current position is the init one
		HP = initHP;										// At first current HP is the init one
		moveStyle = rand() % 5;								// Move style
		Sprite->setVisible(false);							// At first the sprite is hidden
	}

	// Get the sprite pointer
	CCSprite* getSprite (){
		return Sprite;
	}

	// Reduce its Health Points
	void reduceHPBy (const int &HP){
		if (Sprite->isVisible())
			this->HP -= HP;
	}

	// Move the sprite
	void move (int &HouseHP, const float &speedMultipler){
		if (Sprite->isVisible()){
			switch(moveStyle){
			case 0:
				pos.x -= 1*speedMultipler;
				break;
			case 1:
				pos.x -= 2*speedMultipler;
				break;
			case 2:
				pos.x -= 3*speedMultipler;
				break;
			case 3:
				pos.x -= 1*speedMultipler;
				pos.y = initPos.y + 30*sin (0.05*pos.x);
				break;
			case 4:
				pos.x -= 1*speedMultipler;
				pos.y = initPos.y + 60*sin (0.05*pos.x);
				break;
				
			}
			Sprite->setPosition(pos);
		}
		if (pos.x <= 80 ){
			init();
			if (isGhost) HouseHP--;
		}
		if (HP <= 0) init();
	}

	// Determine if the character is dead
	bool isDead (){
		if (HP <= 0) return true;
		else return false;
	}
};


/////*** DECLARE SOME CHARACTERS HERE ***////////////////////////////////
class ghost1 : public character{
public:
	ghost1 (){
		Sprite = CCSprite::create("ghost1.png");
		initHP = 2;
		init ();
		isGhost = true;
	}
};

class ghost2 : public character{
public:
	ghost2 (){
		Sprite = CCSprite::create("ghost2.png");
		initHP = 3;
		init ();
		isGhost = true;
	}
};

class angel : public character{
public:
	angel (){
		Sprite = CCSprite::create("angel_normal.png");
		initHP = 1;
		init ();
		isGhost = false;
	}
};

/////*** END OF CHARACTERS DECLARATION ***////////////////////////////////

#endif  // __CHARACTERS_H__