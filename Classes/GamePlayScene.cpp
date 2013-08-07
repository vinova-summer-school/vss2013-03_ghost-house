//MAIN GAME PLAY SCENE

#include "GamePlayScene.h"

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

		/*
        // 2. Add a label shows "Hello World".

        // Create a label and initialize with string "Hello World".
        CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
        CC_BREAK_IF(! pLabel);

        // Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to GamePlay layer as a child layer.
        this->addChild(pLabel, 1);
		*/

		// 3. Add add a splash screen, show the cocos2d splash image.
        CCSprite* pSprite = CCSprite::create("GamePlayBackground.png");
        CC_BREAK_IF(! pSprite);

        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to GamePlay layer as a child layer.
        this->addChild(pSprite, 0);

		//////////*** Some in-game items ***////////////////////

		// 4. Add some sprites
		// a ghost
		this->addChild(ghost1.getSprite(),2);

		// a second ghost ^^
		this->addChild(ghost2.getSprite(),2);

		// an angel
		this->addChild(angel.getSprite(),0);

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
		streak = CCMotionStreak::create(0.4, 3, 10, ccWHITE, "streak.png" );
		this->addChild(streak);
		//streak->setPosition( ccp(size.width/2, size.height/2) );
		streak->setZOrder (4);

		
        bRet = true;
		
    } while (0);

	setTouchEnabled (true);
	scheduleUpdate ();

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
	if (ghost1.getSprite()->boundingBox().containsPoint(pointTouched)){
		if (touchingState == 3) touchingState = 1;
		else touchingState = 2;
		if (touchingState == 1) ghost1.reduceHPBy (1);
	}
	else if (ghost2.getSprite()->boundingBox().containsPoint(pointTouched)){
		if (touchingState == 3) touchingState = 1;
		else touchingState = 2;
		if (touchingState == 1) ghost2.reduceHPBy (1);
	}
	else if (angel.getSprite()->boundingBox().containsPoint(pointTouched)){
		if (touchingState == 3) touchingState = 1;
		else touchingState = 2;
		if (touchingState == 1) angel.reduceHPBy (1);
	}
	else touchingState = 3;

	CCLog ("Moved");
}

void GamePlay::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
	CCTouch *touch = (CCTouch *)pTouches->anyObject();
	CCPoint pointTouched = touch->getLocationInView();
	pointTouched = CCDirector::sharedDirector()->convertToGL(pointTouched);

	CCLog ("Ended");
}

///////////////////////////////////////////////////////////////////////////

//Using *update* to sprites
void GamePlay::update (float pDt){
	angel.move();

	if (ghost1.getSprite()->getPositionX() >= 80) ghost1.move();
	else House.reduceHPBy (1);
	
	if (ghost2.getSprite()->getPositionX() >= 80) ghost2.move();
	else House.reduceHPBy (1);

	if (angel.isDead()) House.reduceHPBy (1);
	
	if (House.isDead()){
		GameOverBox->setVisible(true);
		CCDirector::sharedDirector()->pause();
	}
}

// When the Pause button is clicked
void GamePlay::menuPauseCallback(CCObject* pSender){
	//"pause" menu item clicked
	PauseDialogBox->setVisible(true);
	CCDirector::sharedDirector()->pause();
}

void GamePlay::menuResumeInPauseBoxCallback(CCObject *pSender){
	PauseDialogBox->setVisible(false);
	CCDirector::sharedDirector()->resume();
}

void GamePlay::menuMainMenuInPauseBoxCallback(CCObject *pSender){
	PauseDialogBox->setVisible(false);
	CCDirector::sharedDirector()->replaceScene(StartScreen::scene());
}