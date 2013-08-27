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

		/////////////////////////******MENU ITEMS********/////////////////////////

		// 1** Add a menu item with options image, which is clicked to go to the Back
		// Create a "Options" menu item with the "options" icon, it's an auto release object
		CCMenuItemImage *pBackItem = CCMenuItemImage::create(
			"BackArrow@2x.png",
			"BackArrowSelected@2x.png",
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
		CCLabelTTF* pLabel = CCLabelTTF::create("Ghost House\nTesting Build\n\n\nCreated by Khanh, Ngoc, Khoa\n\n\nA product of VSS2013", "Calibri", size.height/16);
        CC_BREAK_IF(! pLabel);

        // Get window size and place the label upper. 
        //CCSize size = CCDirector::sharedDirector()->getWinSize();
        pLabel->setPosition(ccp(size.width / 2, size.height /2));

        // Add the label to Credits layer as a child layer.
        this->addChild(pLabel, 1);

        bRet = true;
		
    } while (0);

	setTouchEnabled (true);

    return bRet;
}


//////////////***MENU CALLBACK***////////////////////////////////////////
void Credits::menuBackCallback(CCObject *pSender){
	CCDirector::sharedDirector()->replaceScene(StartScreen::scene());
}