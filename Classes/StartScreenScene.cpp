//THIS IS THE START SCREEN SCENE

#include "StartScreenScene.h"

using namespace cocos2d;

CCScene* StartScreen::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        StartScreen *layer = StartScreen::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScreen::init()
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

		/////////////////////////******MENU ITEMS********/////////////////////////
        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(StartScreen::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(size.width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to StartScreen layer as a child layer.
        this->addChild(pMenu, 1);

		// 1* Add a menu item with "->" image, which is clicked to go to the main game scene
		// Create a "start" menu item with start icon, it's an auto release object.
        CCMenuItemImage *pStartItem = CCMenuItemImage::create(
            "StartButton.png",
            "StartButtonSelected.png",
            this,
            menu_selector(StartScreen::menuStartCallback));
        CC_BREAK_IF(! pStartItem);

		//Place the start menu item
        pStartItem->setPosition(ccp(size.width - 260, 200));

        // Create a menu with the "start" menu item, it's an auto release object.
        CCMenu* pStart = CCMenu::create(pStartItem, NULL);
        pStart->setPosition(CCPointZero);
        CC_BREAK_IF(! pStart);

        // Add the menu to StartScreen layer as a child layer.
        this->addChild(pStart, 1);

		// 1** Add a menu item with options image, which is clicked to go to the Preferences
		// Create a "Options" menu item with the "options" icon, it's an auto release object
		CCMenuItemImage *pPreferencesItem = CCMenuItemImage::create(
			"OptionsButton.png",
			"OptionsButtonSelected.png",
			this,
			menu_selector(StartScreen::menuPreferencesCallback));

		//Place the Preferences Item
		pPreferencesItem->setPosition(ccp(size.width - 130, 150));

		//Create a menu with the "preferences" menu item, it's an auto release object
		CCMenu* pPreferences = CCMenu::create(pPreferencesItem, NULL);
		pPreferences->setPosition(CCPointZero);
		CC_BREAK_IF(! pPreferences);

		//Add the menu item to StartScreen layer as a child layer
		this->addChild(pPreferences, 1);

		//////////////////*****END OF MENU ITEMS***********/////////////////////

        // 2. Add a label shows "Hello World".

       /* // Create a label and initialize with string "Hello World".
        CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 20);
        CC_BREAK_IF(! pLabel);

        // Get window size and place the label upper. 
        //CCSize size = CCDirector::sharedDirector()->getWinSize();
        pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to StartScreen layer as a child layer.
        this->addChild(pLabel, 1);
		*/
        // 3. Add add a splash screen
        CCSprite* pSprite = CCSprite::create("Ghost_house.png");
        CC_BREAK_IF(! pSprite);

        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to StartScreen layer as a child layer.
        this->addChild(pSprite, 0);

        bRet = true;
		
    } while (0);

	setTouchEnabled (true);

    return bRet;
}


//////////////***MENU CALLBACK***////////////////////////////////////////
void StartScreen::menuStartCallback(CCObject* pSender){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("click.wav");
	CCDirector::sharedDirector()->replaceScene(GamePlay::scene());
}

void StartScreen::menuPreferencesCallback(CCObject* pSender){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("click.wav");
	CCDirector::sharedDirector()->replaceScene(Preferences::scene());
}

void StartScreen::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
	CCDirector::sharedDirector()->end();
}
