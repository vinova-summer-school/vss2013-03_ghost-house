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
		size = CCDirector::sharedDirector()->getWinSize();

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
		pPauseItem->setPosition(ccp(0.95*size.width, 0.93*size.height));

		// Create a menu with the "pause" menu item, it's an auto release object
		CCMenu* pPause = CCMenu::create(pPauseItem, NULL);
		pPause->setPosition(CCPointZero);
		CC_BREAK_IF(! pPause);

		// Add the menu to GamePlay layer as a child layer
		this->addChild(pPause, 1);

		// 2. Add a score label.
		score = 0;
		sprintf(ScoreString, "Score : %.1f", score);

		pScore = CCLabelTTF::create(ScoreString, "Calibri", (int)size.height/16);
        CC_BREAK_IF(! pScore);
        // place the label upper.
		pScore->setAnchorPoint(ccp(0,0.5));
		pScore->setPosition(ccp(0.6*size.width, 0.92*size.height));

        // Add the label to GamePlay layer as a child layer.
        this->addChild(pScore, 6);

		// High Score label
		HighScore = UserDefault->getFloatForKey("high_score", 0);
		sprintf (HighScoreString, "High: %.1f", HighScore);

		pHighScore = CCLabelTTF::create(HighScoreString, "Calibri", (int)size.height/18);
		CC_BREAK_IF(! pHighScore);
		pHighScore->setAnchorPoint(ccp(0,0.5));
		pHighScore->setPosition(ccp(0.6*size.width, 0.97*size.height));
		this->addChild(pHighScore, 4);

        // House Health Points
		HouseHP = 10;
		sprintf (HPString, "HP: %d", HouseHP);

		pHP = CCLabelTTF::create(HPString, "Calibri", (int)size.height/16);
		pHP->setPosition(ccp(0.1*size.width, 0.77*size.height));
		this->addChild(pHP, 3);

		// Wave
		wave = 0;
		sprintf (WaveString, "Wave: %d", wave);

		pWave = CCLabelTTF::create(WaveString, "Calibri", (int)size.height/20);
		pWave->setAnchorPoint(ccp(1,0));
		pWave->setPosition(ccp(size.width - 10, 10));
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

		m_emitter = CCParticleSmoke::create();
		this->addChild(m_emitter, 1);
		m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("fire.png") );

		//"star"
		pRecoveryHP = CCMenuItemImage::create("PowerStar.png", "PowerStar.png",
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

			if (first_item == 3) pIceItem->setPosition(ccp(0.08*size.width, 0.9*size.height));
			else if (second_item == 3) pIceItem->setPosition(ccp(0.2*size.width, 0.9*size.height));

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

			if (first_item == 1) pSlowItem->setPosition(ccp(0.08*size.width, 0.9*size.height));
			else if (second_item == 1) pSlowItem->setPosition(ccp(0.2*size.width, 0.9*size.height));

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

			if (first_item == 2) psuperDamageItem->setPosition(ccp(0.08*size.width, 0.9*size.height));
			else if (second_item == 2) psuperDamageItem->setPosition(ccp(0.2*size.width, 0.9*size.height));

			CCMenu* psuperDamage = CCMenu::create(psuperDamageItem,NULL);
			psuperDamage->setPosition(CCPointZero);
			CC_BREAK_IF(! psuperDamage);

			this->addChild(psuperDamage, 4);
		}

		/////////////*** GAME OVER BOX ***/////////////////////
		GameOverBox = CCSprite::create("PauseDialogBox.png");
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

		pOverBox_MainMenuItem->setPosition(ccp(GameOverBox->getContentSize().width/2, 0.35*GameOverBox->getContentSize().height));

		CCMenu *pOverBox_MainMenu = CCMenu::create(pOverBox_MainMenuItem, NULL);
		pOverBox_MainMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pOverBox_MainMenu);

		GameOverBox->addChild(pOverBox_MainMenu);

		// Text: GAME OVER
		pGameOver = CCLabelTTF::create("", "Arial", (int)size.height/13);
		ccColor3B GameOverLabelColor = {255,255,0};
		pGameOver->setColor(GameOverLabelColor);
        CC_BREAK_IF(! pGameOver);

        // Place the label upper.
        pGameOver->setPosition(ccp(GameOverBox->getContentSize().width/2 , 0.75*GameOverBox->getContentSize().height));

        // Add the label to GamePlay layer as a child layer.
        GameOverBox->addChild(pGameOver, 4);

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

	IntervalTime = StarTime = SmokeTime = stt = 0;
	isFreeze = false;
	freezeRefreshTime = 0;
	isSlow = false;
	slowRefreshTime = 0;
	isDamage = false;
	damageRefreshTime = 0;

	speedMultipler = rHP = 1;
	IntervalMultipler = 1.6f;


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
					if (ghost1[i].isDead()){
						score += 20;
						m_emitter->setPosition(ghost1[i].getSprite()->getPosition());
					}
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hit.Wav");
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
					if (ghost2[i].isDead()){
						score += 30;
						m_emitter->setPosition(ghost2[i].getSprite()->getPosition());
					}
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hit.Wav");
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
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hit.Wav");
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
void GamePlay::update (float dt){
	// Number's strings
	sprintf (HPString, "HP: %d", HouseHP);
	sprintf (ScoreString, "Score: %.1f", score);
	sprintf (WaveString, "Wave: %d", wave);
	pHP->setString(HPString);
	pScore->setString(ScoreString);
	pWave->setString(WaveString);
	
	score+=dt;
	
	// Effect of in-game items
	if (first_item == 1 || second_item == 1) slowUpdate (dt);
	if (first_item == 2 || second_item == 2) superDamageUpdate (dt);
	if (first_item == 3 || second_item == 3) iceUpdate (dt);
    
    /////////////**** TIME HANDLER ****/////////////////
	if (!isFreeze) {
		if (IntervalTime <= 0){
			int random = rand() % 100 + 1; // get a random number from 1 to 100
			// set the chance rate for each character to be summonned
			if (random >= 1 && random <= 50) ghost1[stt].getSprite()->setVisible(true);
			if (random >= 31 && random <= 80) ghost2[stt].getSprite()->setVisible(true);
			if (random >= 81 && random <= 100) angel[stt].getSprite()->setVisible(true);
            
			if (IntervalMultipler >= 0.4) IntervalMultipler -= 0.02f;
			IntervalTime = 60*IntervalMultipler;
			stt++;
			wave++;
			if (speedMultipler <= 2.5){
                if (wave >= 150){
                    ccColor3B pWaveColor = {255,100,100};
                    pWave->setColor(pWaveColor);
                    speedMultipler += 0.03f;
                }
                else speedMultipler += 0.015f;
            }
			if (stt == 5) stt = 0;
		}
		IntervalTime--;
	}
    
    if (StarTime <= 0){
        if (isShowingStar == true){
            isShowingStar = false;
            pRecoveryHP->setVisible(false);
        }
        else if (rand()%100 == 1 || rand()%100 == 99){
            isShowingStar = true;
            pRecoveryHP->setPosition(rand()%(int)((0.95-0.2)*size.width) + 0.2*size.width, rand()%(int)((0.8-0.05)*size.height) + 0.05*size.height);
            pRecoveryHP->setVisible(true);
        }
        StarTime = 1.5;
    }
	StarTime -= dt;

	if (SmokeTime <= 0){
		m_emitter->setPosition(ccp(size.width + 100, 0));
		SmokeTime = 1;
	}
	SmokeTime -= dt;

    ///////////////**** END OF TIME HANDLER ****////////////////////////////////
    
	// NO WAY TO ACCESS THAT FUCKING HOUSEHP OUTSIDE CLASS SO WE HAVE TO PASS THESE PARAMETERS
	for (int i=0; i<angelCount; i++) angel[i].move(HouseHP,1);
	for (int i=0; i<ghost1Count; i++) ghost1[i].move(HouseHP,speedMultipler);
	for (int i=0; i<ghost2Count; i++) ghost2[i].move(HouseHP,speedMultipler);
	
	if (HouseHP <= 0){
        sprintf(ScoreString, "Your Score is: %.1f", score);
        pGameOver->setString(ScoreString);
		GameOverBox->setVisible(true);
		if (score > HighScore) UserDefault->setFloatForKey("high_score", score);
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
	HouseHP += rand() % 2 + 2;
	pRecoveryHP->setVisible(false);
}
