#ifndef __CHARACTERS_H__
#define __CHARACTERS_H__

#include "cocos2d.h"

using namespace cocos2d;

/////*** DECLARE SOME CHARACTERS HERE ***////////////////////////////////

class ghost1 {
	CCSprite *Sprite;
	short HP;

public:
	ghost1 (){
		Sprite = CCSprite::create("ghost1.png");
		HP = 2;
	}

	CCSprite* getSprite ();
	void reduceHPBy (short HP);
	bool isDead ();
};

class ghost2 {
	CCSprite *Sprite;
	short HP;

public:
	ghost2 (){
		Sprite = CCSprite::create("ghost2.png");
		HP = 3;
	}

	CCSprite* getSprite ();
	void reduceHPBy (short HP);
	bool isDead ();
};

class House {
	short HP;

public:
	House (){
		HP = 1;
	}
	void reduceHPBy (short HP);
	bool isDead ();
};


/////*** END OF CHARACTERS DECLARATION ***////////////////////////////////

#endif  // __CHARACTERS_H__