//MAIN GAME PLAY SCENE

#include "GamePlayScene.h"

#include <stdlib.h>
#include <cstring>
#include "SimpleAudioEngine.h"

using namespace cocos2d;

CCScene* GamePlay::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GamePlay *layer = GamePlay::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GamePlay::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

		//Get the sizes
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		//Game soundtrack
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		"fallen army.wav",true);
		

		////////////////*** Outline Background ***///////////////////////
		// 1. Create some menu items
		// Create the "pause" menu item with a pause icon, it's an auto release object
		CCMenuItemImage *pPauseItem = CCMenuItemImage::create("PauseButton.png",
			"PauseButtonSelected.png",
			this,
			menu_selector(GamePlay::menuPauseCallback));
		CC_BREAK_IF(! pPauseItem);
		
		// Place the pause button on top right corner
		pPauseItem->setPosition(ccp(size.width - 20, size.height - 20));

		// Create a menu with the "pause" menu item, it's an auto release object
		CCMenu* pPause = CCMenu::create(pPauseItem, NULL);
		pPause->setPosition(CCPointZero);
		CC_BREAK_IF(! pPause);

		// Add the menu to GamePlay layer as a child layer
		this->addChild(pPause, 1);

		// 2. Add a score label.
		score = 0;
		_itoa(score, ScoreString, 10);
		pScore = CCLabelTTF::create(ScoreString, "Arial", 24);
        CC_BREAK_IF(! pScore);
        // place the label upper.
        pScore->setPosition(ccp(400, 280));

        // Add the label to GamePlay layer as a child layer.
        this->addChild(pScore, 6);

		// High Score label
		HighScore = UserHighScore->getIntegerForKey("high_score", 0);
		_itoa(HighScore, HighScoreString, 10);

		pHighScore = CCLabelTTF::create(HighScoreString, "Verdana", 20);
		CC_BREAK_IF(! pHighScore);
		pHighScore->setPosition(ccp(400, 300));
		this->addChild(pHighScore, 4);

        // House Health Points
		HouseHP = 10;
		_itoa(HouseHP, HPString, 10);
		pHP = CCLabelTTF::create(HPString, "Arial", 30);
		pHP->setPosition(ccp(50, 250));
		this->addChild(pHP, 6);
		
		// 3. Add add a splash screen, show the cocos2d splash image.
        CCSprite* pSprite = CCSprite::create("GamePlayBackground.png");
        CC_BREAK_IF(! pSprite);

        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to GamePlay layer as a child layer.
        this->addChild(pSprite, 0);

		//////////*** Some in-game items ***////////////////////
		// 4. Add some sprites
		ghost1Count = 5;
		ghost2Count = 5;
		angelCount = 5;
		// ghosts
		for (int i=0; i<ghost1Count; i++) this->addChild(ghost1[i].getSprite(),2);
		for (int i=0; i<ghost2Count; i++) this->addChild(ghost2[i].getSprite(),2);
		// angels
		for (int i=0; i<angelCount; i++) this->addChild(angel[i].getSprite(),1);

		// Create ice item
		pIceItem = CCMenuItemImage::create("ice.png","ice.png",
			this,
			menu_selector(GamePlay::iceEffectCallback));
		CC_BREAK_IF(! pIceItem);

		pIceItem->setPosition(ccp(140 , 300));

		CCMenu* pIce = CCMenu::create(pIceItem,NULL);
		pIce->setPosition(CCPointZero);
		CC_BREAK_IF(! pIce);

		this->addChild(pIce, 4);

		// Create Slow item
		pSlowItem = CCMenuItemImage::create("Slow.png","Slow.png",
			this,
			menu_selector(GamePlay::SlowCallback));
		CC_BREAK_IF(! pSlowItem);

		pSlowItem->setPosition(ccp(40 , 300));

		CCMenu* pSlow = CCMenu::create(pSlowItem,NULL);
		pSlow->setPosition(CCPointZero);
		CC_BREAK_IF(! pSlow);

		this->addChild(pSlow, 4);
		// Create a Super Damage Item
		psuperDamageItem = CCMenuItemImage::create("superDamage.png","superDamage.png",
			this,
			menu_selector(GamePlay::superDamageCallback));
		CC_BREAK_IF(! psuperDamageItem);

		psuperDamageItem->setPosition(ccp(90 , 300));

		CCMenu* psuperDamage = CCMenu::create(psuperDamageItem,NULL);
		psuperDamage->setPosition(CCPointZero);
		CC_BREAK_IF(! psuperDamage);

		this->addChild(psuperDamage, 4);

		//////////////////*** Pause Dialog Box ***////////////////////////
		// Dialog box
		PauseDialogBox = CCSprite::create("PauseDialogBox.png");
		CC_BREAK_IF(! PauseDialogBox);
		PauseDialogBox->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(PauseDialogBox,3);
		PauseDialogBox->setVisible(false);

		// A resume button as a menu item
		CCMenuItemImage *pPauseBox_ResumeItem = CCMenuItemImage::create(
			"PauseBox_ResumeButton.png",
			"PauseBox_ResumeButtonSelected.png",
			this,
			menu_selector(GamePlay::menuResumeInPauseBoxCallback));
		CC_BREAK_IF(! pPauseBox_ResumeItem);

		pPauseBox_ResumeItem->setPosition(ccp(size.width/2 - 100, size.height/2 - 110));

		CCMenu *pPauseBox_Resume = CCMenu::create(pPauseBox_ResumeItem, NULL);
		pPauseBox_Resume->setPosition(CCPointZero);
		CC_BREAK_IF(! pPauseBox_Resume);

		PauseDialogBox->addChild(pPauseBox_Resume);

		// A Back button as a menu item
		CCMenuItemImage *pPauseBox_MainMenuItem = CCMenuItemImage::create(
			"MainMenuButton.png",
			"MainMenuButtonSelected.png",
			this,
			menu_selector(GamePlay::menuMainMenuInPauseBoxCallback));
		CC_BREAK_IF(! pPauseBox_MainMenuItem);

		pPauseBox_MainMenuItem->setPosition(ccp(size.width - 200, size.height - 200));

		CCMenu *pPauseBox_MainMenu = CCMenu::create(pPauseBox_MainMenuItem, NULL);
		pPauseBox_MainMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pPauseBox_MainMenu);

		PauseDialogBox->addChild(pPauseBox_MainMenu);

		////////*** END OF PAUSE DIALOG BOX ***////////////////////////////


		/////////////*** GAME OVER BOX ***/////////////////////
		GameOverBox = CCSprite::create("GameOverBox.png");
		CC_BREAK_IF(! GameOverBox);
		GameOverBox->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(GameOverBox,3);
		GameOverBox->setVisible(false);
		// A Main Menu button as a menu item
		CCMenuItemImage *pOverBox_MainMenuItem = CCMenuItemImage::create(
			"MainMenuButton.png",
			"MainMenuButtonSelected.png",
			this,
			menu_selector(GamePlay::menuMainMenuInPauseBoxCallback));
		CC_BREAK_IF(! pOverBox_MainMenuItem);

		pOverBox_MainMenuItem->setPosition(ccp(size.width - 300, size.height - 250));

		CCMenu *pOverBox_MainMenu = CCMenu::create(pOverBox_MainMenuItem, NULL);
		pOverBox_MainMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pOverBox_MainMenu);

		GameOverBox->addChild(pOverBox_MainMenu);

		// Text: GAME OVER
		CCLabelTTF* pGameOverLabel = CCLabelTTF::create("Game Over !!!", "Arial", 24);
		ccColor3B GameOverLabelColor = {255,255,0};
		pGameOverLabel->setColor(GameOverLabelColor);
        CC_BREAK_IF(! pGameOverLabel);

        // Place the label upper.
        pGameOverLabel->setPosition(ccp(size.width - 300 , size.height - 175));

        // Add the label to GamePlay layer as a child layer.
        GameOverBox->addChild(pGameOverLabel, 4);

		///////**** END OF GAME OVER BOX ***//////////////
		

		///******* This is the streak
		streak = CCMotionStreak::create(0.5, 10, 30, ccWHITE, "thunder.png" );
		this->addChild(streak);
		//streak->setPosition( ccp(size.width/2, size.height/2) );
		streak->setZOrder (4);

		
        bRet = true;
		
    } while (0);

	setTouchEnabled (true);
	scheduleUpdate ();

	UserHighScore = CCUserDefault::sharedUserDefault();

	time = stt = 0;
	isFreeze = 0;
	isSlow = false;
	isDamage = false;
	speedMultipler = rHP = 1;
	SpeedLevel = 3;
	freezeRefreshTime = 0;

    return bRet;
}

/////////////////////////////////////////////////////////////////////////
//Using touch-related functions applied to sprites

void GamePlay::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
	
	///*********** Apply the streak
	CCSetIterator it = pTouches->begin();
    CCTouch* _touch = (CCTouch*)(*it);
    CCPoint touchLocation = _touch->getLocation();
    streak->setPosition( touchLocation );
	
	////******* Get the touching point
	CCTouch *touch = (CCTouch *)pTouches->anyObject();
	CCPoint pointTouched = touch->getLocationInView();
	pointTouched = CCDirector::sharedDirector()->convertToGL(pointTouched);

	////// if a sprite contains the touching point
	bool touching = false;
	if (touching == false) for (int i=0; i<ghost1Count; i++) if (ghost1[i].getSprite()->boundingBox().containsPoint(pointTouched)){
			touching = true;
			if (touchingState == 3) touchingState = 1;
			else touchingState = 2;
			if (touchingState == 1)
				ghost1[i].reduceHPBy (rHP);
			if (ghost1[i].isDead()) 
				score += 20;
		}
	if (touching == false) for (int i=0; i<ghost2Count; i++) if (ghost2[i].getSprite()->boundingBox().containsPoint(pointTouched)){
			touching = true;
			if (touchingState == 3) touchingState = 1;
			else touchingState = 2;
			if (touchingState == 1) {
				ghost2[i].reduceHPBy (rHP);
			if (ghost2[i].isDead()) score += 30;
		
			}
		}
	if (touching == false) for (int i=0; i<angelCount; i++) if (angel[i].getSprite()->boundingBox().containsPoint(pointTouched)){
			touching = true;
			if (touchingState == 3) touchingState = 1;
			else touchingState = 2;
			if (touchingState == 1) {
				angel[i].reduceHPBy (rHP);
				if (angel[i].isDead()){
					score -= 20;
					HouseHP--;
				}		
			}
		}
	if (touching == false) touchingState = 3;

}

void GamePlay::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
	CCTouch *touch = (CCTouch *)pTouches->anyObject();
	CCPoint pointTouched = touch->getLocationInView();
	pointTouched = CCDirector::sharedDirector()->convertToGL(pointTouched);

}

///////////////////////////////////////////////////////////////////////////

//Using *update* to sprites
void GamePlay::update (float pDt){
	// Number's strings
	_itoa(HouseHP, HPString, 10);
	_itoa(score,ScoreString,10);
	pHP->setString(HPString);
	pScore->setString(ScoreString);

	// Effect of in-game items
	iceUpdate ();
	slowUpdate ();
	superDamageUpdate ();
	

	if (!isFreeze) {
		if (time == 0){
			ghost1[stt].getSprite()->setVisible(true);
			ghost2[stt].getSprite()->setVisible(true);
			angel[stt].getSprite()->setVisible(true);
			
			if (SpeedLevel > 0.5) SpeedLevel -= 0.075;
			time = 60*SpeedLevel;
			stt++;
			speedMultipler += (float) 0.05;
			if (stt == 5) stt = 0;
		}
		time--;
	}

	for (int i=0; i<angelCount; i++) angel[i].move(HouseHP,1);
	for (int i=0; i<ghost1Count; i++) ghost1[i].move(HouseHP,speedMultipler);
	for (int i=0; i<ghost2Count; i++) ghost2[i].move(HouseHP,speedMultipler);
	

	if (HouseHP <= 0){
		GameOverBox->setVisible(true);
		if (score > HighScore) UserHighScore->setIntegerForKey("high_score", score);
		CCDirector::sharedDirector()->pause();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	}
}

// When the Pause button is clicked
void GamePlay::menuPauseCallback(CCObject* pSender){
	//"pause" menu item clicked
	PauseDialogBox->setVisible(true);
	CCDirector::sharedDirector()->pause();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();	
}

void GamePlay::menuResumeInPauseBoxCallback(CCObject *pSender){
	PauseDialogBox->setVisible(false);
	CCDirector::sharedDirector()->resume();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void GamePlay::menuMainMenuInPauseBoxCallback(CCObject *pSender){
	PauseDialogBox->setVisible(false);
	CCDirector::sharedDirector()->replaceScene(StartScreen::scene());
}
