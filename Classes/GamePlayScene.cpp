//MAIN GAME PLAY SCENE

#include "GamePlayScene.h"

#include <stdlib.h>
#include <cstring>

using namespace cocos2d;

CCScene* GamePlay::scene()
{
    CCScene * scene = NULL;

    // 'scene' is an autorelease object
    scene = CCScene::create();
        
    // 'layer' is an autorelease object
    GamePlay *layer = GamePlay::create();
	layer->pauseLayer = PauseLayer::create();
	layer->pauseLayer->setVisible(false);
    
	layer->pauseLayer->gameLayer = layer;
	//layer->pauseLayer->pauseLayer = layer->pauseLayer;

    // add layer as a child to scene
    scene->addChild(layer,0);
	scene->addChild(layer->pauseLayer,7);

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
		"music.wav",true);
		

		////////////////*** Outline Background ***///////////////////////
		// 1. Create some menu items
		// Create the "pause" menu item with a pause icon, it's an auto release object
		pPauseItem = CCMenuItemImage::create("PauseButton.png",
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
		sprintf(ScoreString, "Score : %d", score);

		pScore = CCLabelTTF::create(ScoreString, "Calibri", 20);
        CC_BREAK_IF(! pScore);
        // place the label upper.
		pScore->setPosition(ccp(size.width - 110, size.height - 40));

        // Add the label to GamePlay layer as a child layer.
        this->addChild(pScore, 6);

		// High Score label
		HighScore = UserDefault->getIntegerForKey("high_score", 0);
		sprintf (HighScoreString, "High: %d", HighScore);

		pHighScore = CCLabelTTF::create(HighScoreString, "Calibri", 18);
		CC_BREAK_IF(! pHighScore);
		pHighScore->setPosition(ccp(size.width - 110, size.height - 20));
		this->addChild(pHighScore, 4);

        // House Health Points
		HouseHP = 10;
		sprintf (HPString, "HP: %d", HouseHP);

		pHP = CCLabelTTF::create(HPString, "Calibri", 20);
		pHP->setPosition(ccp(50, size.height / 1.3));
		this->addChild(pHP, 6);

		// Wave
		wave = 0;
		sprintf (WaveString, "Wave: %d", wave);

		pWave = CCLabelTTF::create(WaveString, "Calibri", 18);
		pWave->setPosition(ccp(size.width - 40, 20));
		this->addChild(pWave, 6);
		
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
	
		first_item = UserDefault->getIntegerForKey("first_item", 0);
		second_item = UserDefault->getIntegerForKey("second_item", 0);

		//"star"
		pRecoveryHP = CCMenuItemImage::create("Powerstar.png", "Powerstar.png",
			this,
			menu_selector(GamePlay::RecoveryHPCallback));
		CC_BREAK_IF (!pRecoveryHP);
		pRecoveryHP->setVisible (false);
		CCMenu *pRecovery = CCMenu::create(pRecoveryHP,NULL);
		pRecovery->setPosition(CCPointZero);
		CC_BREAK_IF(!pRecovery);
		this->addChild(pRecovery,4);

		if (first_item == 3 || second_item == 3){
			// Create ice item
			pIceItem = CCMenuItemImage::create("ice.png","ice.png",
				this,
				menu_selector(GamePlay::iceEffectCallback));
			CC_BREAK_IF(! pIceItem);

			if (first_item == 3) pIceItem->setPosition(ccp(40, size.height - 20));
			else if (second_item == 3) pIceItem->setPosition(ccp(90, size.height - 20));

			CCMenu* pIce = CCMenu::create(pIceItem,NULL);
			pIce->setPosition(CCPointZero);
			CC_BREAK_IF(! pIce);

			this->addChild(pIce, 4);
		}

		if (first_item == 1 || second_item == 1){
			// Create Slow item
			pSlowItem = CCMenuItemImage::create("Slow.png","Slow.png",
				this,
				menu_selector(GamePlay::SlowCallback));
			CC_BREAK_IF(! pSlowItem);

			if (first_item == 1) pSlowItem->setPosition(ccp(40, size.height - 20));
			else if (second_item == 1) pSlowItem->setPosition(ccp(90, size.height - 20));

			CCMenu* pSlow = CCMenu::create(pSlowItem,NULL);
			pSlow->setPosition(CCPointZero);
			CC_BREAK_IF(! pSlow);

			this->addChild(pSlow, 4);
		}

		if (first_item == 2 || second_item == 2){
			// Create a Super Damage Item
			psuperDamageItem = CCMenuItemImage::create("superDamage.png","superDamage.png",
				this,
				menu_selector(GamePlay::superDamageCallback));
			CC_BREAK_IF(! psuperDamageItem);

			if (first_item == 2) psuperDamageItem->setPosition(ccp(40, size.height - 20));
			else if (second_item == 2) psuperDamageItem->setPosition(ccp(90, size.height - 20));

			CCMenu* psuperDamage = CCMenu::create(psuperDamageItem,NULL);
			psuperDamage->setPosition(CCPointZero);
			CC_BREAK_IF(! psuperDamage);

			this->addChild(psuperDamage, 4);
		}

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
			menu_selector(PauseLayer::menuMainMenuCallback));
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

	UserDefault = CCUserDefault::sharedUserDefault();

	time = stt = 0;
	tmpWave = 0;
	isFreeze = false;
	freezeRefreshTime = 0;
	isSlow = false;
	slowRefreshTime = 0;
	isDamage = false;
	damageRefreshTime = 0;

	speedMultipler = rHP = 1;
	IntervalMultipler = 2;


    return bRet;
}

/////////////////////////////////////////////////////////////////////////
//Using touch-related functions applied to sprites

void GamePlay::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
	////******* Get the touching point
	CCTouch *touch = (CCTouch *)pTouches->anyObject();
	CCPoint pointTouched = touch->getLocationInView();
	pointTouched = CCDirector::sharedDirector()->convertToGL(pointTouched);
	
	///*********** Apply the streak
	streak->setPosition( pointTouched );

	////// if a sprite contains the touching point
	bool touching = false;
	if (touching == false) 
		for (int i=0; i<ghost1Count; i++) 
			if (ghost1[i].getSprite()->boundingBox().containsPoint(pointTouched)){
				touching = true;
				if (touchingState == 3) touchingState = 1;
				else touchingState = 2;
				if (touchingState == 1){
					ghost1[i].reduceHPBy (rHP);
					if (ghost1[i].isDead()) score += 20;
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hit.wav");
				}
			}
	if (touching == false)
		for (int i=0; i<ghost2Count; i++)
			if (ghost2[i].getSprite()->boundingBox().containsPoint(pointTouched)){
				touching = true;
				if (touchingState == 3) touchingState = 1;
				else touchingState = 2;
				if (touchingState == 1) {
					ghost2[i].reduceHPBy (rHP);
					if (ghost2[i].isDead()) score += 30;
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hit.wav");
				}
			}
	if (touching == false)
		for (int i=0; i<angelCount; i++)
			if (angel[i].getSprite()->boundingBox().containsPoint(pointTouched)){
				touching = true;
				if (touchingState == 3) touchingState = 1;
				else touchingState = 2;
				if (touchingState == 1) {
					angel[i].reduceHPBy (rHP);
					if (angel[i].isDead()) score -= 20;
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hit.wav");
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
	//setAllButtonsEnabled (true);
	// Number's strings
	sprintf (HPString, "HP: %d", HouseHP);
	sprintf (ScoreString, "Score: %d", score);
	sprintf (WaveString, "Wave: %d", wave);
	pHP->setString(HPString);
	pScore->setString(ScoreString);
	pWave->setString(WaveString);

	// Effect of in-game items
	if (first_item == 1 || second_item == 1) slowUpdate ();
	if (first_item == 2 || second_item == 2) superDamageUpdate ();
	if (first_item == 3 || second_item == 3) iceUpdate ();

	if (!isFreeze) {
		if (time == 0){
			int random = rand() % 100 + 1; // get a random number from 1 to 100
			// set the chance rate for each character to be summonned
			if (random >= 1 && random <= 50) ghost1[stt].getSprite()->setVisible(true);
			if (random >= 31 && random <= 80) ghost2[stt].getSprite()->setVisible(true);
			if (random >= 81 && random <= 100) angel[stt].getSprite()->setVisible(true);
			if (random == 1 || random == 49 || random == 100) {
				pRecoveryHP->setPosition(rand()%200+100, rand()%260+25);
				pRecoveryHP->setVisible(true);
				tmpWave = wave;
			}
			if (wave - tmpWave == 2) pRecoveryHP->setVisible(false);
			if (IntervalMultipler >= 0.5) IntervalMultipler -= (float) 0.02;
			time = 60*IntervalMultipler;
			stt++;
			wave++;
			score += 5;
			if (speedMultipler <= 2.5) speedMultipler += (float) 0.025;
			if (stt == 5) stt = 0;
		}
		time--;
	}
	// NO WAY TO ACCESS THAT FUCKING HOUSEHP OUTSIDE CLASS SO WE HAVE TO PASS THESE PARAMETERS
	for (int i=0; i<angelCount; i++) angel[i].move(HouseHP,1);
	for (int i=0; i<ghost1Count; i++) ghost1[i].move(HouseHP,speedMultipler);
	for (int i=0; i<ghost2Count; i++) ghost2[i].move(HouseHP,speedMultipler);
	
	if (HouseHP <= 0){
		GameOverBox->setVisible(true);
		if (score > HighScore) UserDefault->setIntegerForKey("high_score", score);
		pauseSchedulerAndActions();
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	}
}


// When the Pause button is clicked
void GamePlay::menuPauseCallback(CCObject* pSender){
	//"pause" menu item clicked
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("click.wav");
	setTouchEnabled(false);
	pauseSchedulerAndActions();
	setVisible (false);
	pauseLayer->setVisible(true);
	
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();	
}

void GamePlay::RecoveryHPCallback(CCObject* pSender){
<<<<<<< HEAD
	HouseHP += 5;
=======
	HouseHP += rand() % 2 + 2;
>>>>>>> Transferred to new Cocos2d-x version
	pRecoveryHP->setVisible(false);
}
