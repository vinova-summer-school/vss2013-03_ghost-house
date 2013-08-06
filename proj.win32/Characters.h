#ifndef __CHARACTERS_H__
#define __CHARACTERS_H__

#include "cocos2d.h"

using namespace cocos2d;

// Parent class to define some similar character types
class character {
protected:
	CCSprite *Sprite;
	short HP;

public:
	CCSprite* getSprite ();
	void reduceHPBy (short HP);
	bool isDead ();
};


/////*** DECLARE SOME CHARACTERS HERE ***////////////////////////////////
class ghost1 : public character{
public:
	ghost1 (){
		Sprite = CCSprite::create("ghost1.png");
		HP = 2;
	}
};

class ghost2 : public character{
public:
	ghost2 (){
		Sprite = CCSprite::create("ghost2.png");
		HP = 3;
	}
};

class angel : public character{
public:
	angel (){
		Sprite = CCSprite::create("angel_normal.png");
		HP = 1;
	}
};

class House : public character{
public:
	House (){
		HP = 1;
	}
};

/////*** END OF CHARACTERS DECLARATION ***////////////////////////////////

#endif  // __CHARACTERS_H__