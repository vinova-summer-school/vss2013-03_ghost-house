#ifndef __CHARACTERS_H__
#define __CHARACTERS_H__

#include "cocos2d.h"
#include <ctime>

using namespace cocos2d;

// Parent class to define some similar character types
class character {
protected:
	CCSprite *Sprite;
	short HP;
	short moveStyle;
	CCPoint initPos, pos;

public:
	void init();

	CCSprite* getSprite ();
	void reduceHPBy (short HP);
	void move ();
	bool isDead ();
};


/////*** DECLARE SOME CHARACTERS HERE ***////////////////////////////////
class ghost1 : public character{
public:
	ghost1 (){
		Sprite = CCSprite::create("ghost1.png");
		Sprite->setPosition (ccp(480, rand() % 245 + 30));
		HP = 2;
		init ();
	}
};

class ghost2 : public character{
public:
	ghost2 (){
		Sprite = CCSprite::create("ghost2.png");
		Sprite->setPosition (ccp(480, rand() % 245 + 30));
		HP = 3;
		init ();
	}
};

class angel : public character{
public:
	angel (){
		Sprite = CCSprite::create("angel_normal.png");
		Sprite->setPosition (ccp(480, rand() % 245 + 30));
		HP = 1;
		init ();
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