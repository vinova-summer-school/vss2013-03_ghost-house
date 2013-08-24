#ifndef __PAUSE_LAYER_H__
#define __PAUSE_LAYER_H__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class PauseLayer : public CCLayer
{

public:
	CCLayer* gameLayer;

	virtual bool init();  

	void menuResumeCallback(CCObject* pSender);	// Resume Button in the Pause Dialog box
	void menuMainMenuCallback(CCObject* pSender);	// Main menu button in the Pause Dialog box

	CREATE_FUNC(PauseLayer);
};

#endif  // __PAUSE_LAYER_H__