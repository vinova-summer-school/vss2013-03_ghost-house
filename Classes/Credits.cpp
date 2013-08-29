#include "StartScreenScene.h"

using namespace cocos2d;

CCScene* Credits::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        Credits *layer = Credits::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Credits::init()
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

		// Load User Default
		UserDefault = CCUserDefault::sharedUserDefault();

		/////////////////////////******MENU ITEMS********/////////////////////////

		// 1** Add a menu item with options image, which is clicked to go to the Back
		// Create a "Options" menu item with the "options" icon, it's an auto release object
		CCMenuItemImage *pBackItem = CCMenuItemImage::create(
			"BackArrow.png",
			"BackArrowSelected.png",
			this,
			menu_selector(Credits::menuBackCallback));

		//Place the Back Item
		pBackItem->setPosition(ccp(0.07*size.width, 0.92*size.height));

		//Create a menu with the "Back" menu item, it's an auto release object
		CCMenu* pBack = CCMenu::create(pBackItem, NULL);
		pBack->setPosition(CCPointZero);
		CC_BREAK_IF(! pBack);

		//Add the menu item to Credits layer as a child layer
		this->addChild(pBack, 1);

		//////////////////*****END OF MENU ITEMS***********/////////////////////

        // Create a label and initialize with string "Hello World".
		CCLabelTTF* pLabel = CCLabelTTF::create("Ghost House (Testing Build)\nCreated by Khanh, Ngoc, Khoa\nA product of VSS2013", "Noteworthy", size.height/16);
        pLabel->setPosition(ccp(size.width/2, 0.7*size.height));
        this->addChild(pLabel, 1);

		// Credit for cocos2d-x
		CCLabelTTF* pCredits = CCLabelTTF::create("Powered by Cocos2d-x game engine", "Calibri", size.height/16);
		pCredits->setPosition(ccp(size.width/2, 0.3*size.height));
		this->addChild(pCredits, 1);

		CCSprite* cocos2dxLogo = CCSprite::create("cocos2dx_landscape.png");
		cocos2dxLogo->setPosition(ccp(size.width/2, 0.18*size.height));
		this->addChild(cocos2dxLogo, 1);

		// A button to reset high score
		pResetScoreItem = CCMenuItemImage::create("reset_highscore.png", "reset_highscore.png",
			this, menu_selector(Credits::menuResetScoreCallback));
		pResetScoreItem->setAnchorPoint(ccp(1,0));
		pResetScoreItem->setPosition(size.width - 10, 10);

		if (UserDefault->getFloatForKey("high_score", 0) < 100) pResetScoreItem->setVisible(false);

		CCMenu* pResetScore = CCMenu::create(pResetScoreItem, NULL);
		pResetScore->setPosition(CCPointZero);
		CC_BREAK_IF(! pResetScore);
		this->addChild(pResetScore, 1);

        bRet = true;
		
    } while (0);

	clicksRemainingToConfirm = 3;

    return bRet;
}


//////////////***MENU CALLBACK***////////////////////////////////////////
void Credits::menuBackCallback(CCObject *pSender){
	CCDirector::sharedDirector()->replaceScene(StartScreen::scene());
}

void Credits::menuResetScoreCallback(CCObject* pSender){
	// Requires 3 clicks on this menu to reset the high score
	clicksRemainingToConfirm--;
	if (clicksRemainingToConfirm == 0){
		UserDefault->setFloatForKey("high_score", 0);
		pResetScoreItem->setVisible(false);
	}
}