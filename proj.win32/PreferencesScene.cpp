//THIS IS THE PREFERENCES SCENE

#include "PreferencesScene.h"

using namespace cocos2d;

CCScene* Preferences::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
		Preferences *layer = Preferences::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Preferences::init()
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
        // 1. Add a menu item with "back" arrow, which is clicked to return to the main menu

        // Create a "back" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pBackItem = CCMenuItemImage::create(
            "BackArrow.png",
            "BackArrowSelected.png",
            this,
            menu_selector(Preferences::menuBackCallback));
        CC_BREAK_IF(! pBackItem);

        // Place the menu item top-left conner.
		pBackItem->setPosition(ccp(40, size.height - 40));

        // Create a menu with the "back" menu item, it's an auto release object.
        CCMenu* pBack = CCMenu::create(pBackItem, NULL);
        pBack->setPosition(CCPointZero);
        CC_BREAK_IF(! pBack);

        // Add the menu to Preferences layer as a child layer.
        this->addChild(pBack, 1);
		//////////////////*****END OF MENU ITEMS***********/////////////////////

        // 2. Add a label shows "Hello World".

        // Create a label and initialize with string "Preferences".
        CCLabelTTF* pPrefMainTitle = CCLabelTTF::create("Preferences", "Verdana", 24);
		ccColor3B PrefMainTitleColor = {255,255,0};
		pPrefMainTitle->setColor(PrefMainTitleColor);
        CC_BREAK_IF(! pPrefMainTitle);

        // place the label upper. 
        //CCSize size = CCDirector::sharedDirector()->getWinSize();
        pPrefMainTitle->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to Preferences layer as a child layer.
        this->addChild(pPrefMainTitle, 1);

        // 3. Add add a splash screen
        CCSprite* pSprite = CCSprite::create("PreferencesBackground.png");
        CC_BREAK_IF(! pSprite);

        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to Preferences layer as a child layer.
        this->addChild(pSprite, 0);

        bRet = true;
		
    } while (0);

	setTouchEnabled (true);

    return bRet;
}

void Preferences::menuBackCallback(CCObject* pSender)
{
    // "back" menu item clicked
	CCDirector::sharedDirector()->replaceScene(StartScreen::scene());
}
