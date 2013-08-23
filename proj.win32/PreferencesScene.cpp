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

		first_item = effectUserDefault->getIntegerForKey("first_item", 0);
		second_item = effectUserDefault->getIntegerForKey("second_item", 0);
		numItemsSelected = 0;
		
		// Create Slow item
		pSlowItem = CCMenuItemImage::create("Slow.png","Slow.png",
			this,
			menu_selector(Preferences::SlowCallback));
		CC_BREAK_IF(! pSlowItem);

		pSlowItem->setPosition(ccp(80, size.height - 80));

		CCMenu* pSlow = CCMenu::create(pSlowItem,NULL);
		pSlow->setPosition(CCPointZero);
		CC_BREAK_IF(! pSlow);

		this->addChild(pSlow, 4);

		if(first_item == 1 || second_item == 1){
			pSlowItem->setOpacity(100);
			numItemsSelected++;
		}

		// Create a Super Damage Item
		psuperDamageItem = CCMenuItemImage::create("superDamage.png","superDamage.png",
			this,
			menu_selector(Preferences::superDamageCallback));
		CC_BREAK_IF(! psuperDamageItem);

		psuperDamageItem->setPosition(ccp(80 , size.height - 140));

		CCMenu* psuperDamage = CCMenu::create(psuperDamageItem,NULL);
		psuperDamage->setPosition(CCPointZero);
		CC_BREAK_IF(! psuperDamage);

		this->addChild(psuperDamage, 4);

		if(first_item == 2 || second_item == 2){
			psuperDamageItem->setOpacity(100);
			numItemsSelected++;
		}

		// Create ice item
		pIceItem = CCMenuItemImage::create("ice.png","ice.png",
			this,
			menu_selector(Preferences::iceEffectCallback));
		CC_BREAK_IF(! pIceItem);

		pIceItem->setPosition(ccp(80, 130));

		CCMenu* pIce = CCMenu::create(pIceItem,NULL);
		pIce->setPosition(CCPointZero);
		CC_BREAK_IF(! pIce);

		this->addChild(pIce, 4);

		if(first_item == 3 || second_item == 3){
			pIceItem->setOpacity(100); 
			numItemsSelected++;
		}

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
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("click.wav");
	CCDirector::sharedDirector()->replaceScene(StartScreen::scene());
}

void Preferences::SlowCallback(CCObject* pSender){
	first_item = effectUserDefault->getIntegerForKey("first_item", 0);
	second_item = effectUserDefault->getIntegerForKey("second_item", 0);
	
	if(first_item == 1 || second_item == 1){
		if (first_item == 1) effectUserDefault->setIntegerForKey("first_item", 0);
		if (second_item == 1) effectUserDefault->setIntegerForKey("second_item", 0);
		
		numItemsSelected--;
		pSlowItem->setOpacity(255);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ItemDeselect.wav");
	}
	else if(numItemsSelected < 2){
		if (first_item == 0) effectUserDefault->setIntegerForKey("first_item",1); 
		else if (second_item == 0) effectUserDefault->setIntegerForKey("second_item",1);
			
		numItemsSelected ++;
		pSlowItem->setOpacity(100);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ItemSelect.wav");
	}
}

void Preferences::superDamageCallback(CCObject* pSender){
	first_item = effectUserDefault->getIntegerForKey("first_item", 0);
	second_item = effectUserDefault->getIntegerForKey("second_item", 0);
	
	if(first_item == 2 || second_item == 2){
		if (first_item == 2) effectUserDefault->setIntegerForKey("first_item", 0);
		if (second_item == 2) effectUserDefault->setIntegerForKey("second_item", 0);		
		
		numItemsSelected--;
		psuperDamageItem->setOpacity(255);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ItemDeselect.wav");
	}
	else if(numItemsSelected < 2){
		if (first_item == 0) effectUserDefault->setIntegerForKey("first_item",2);
		else if (second_item == 0) effectUserDefault->setIntegerForKey("second_item",2);
			
		numItemsSelected ++;
		psuperDamageItem->setOpacity(100);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ItemSelect.wav");
	}
}

void Preferences::iceEffectCallback(CCObject* pSender){
	first_item = effectUserDefault->getIntegerForKey("first_item", 0);
	second_item = effectUserDefault->getIntegerForKey("second_item", 0);
	
	if(first_item == 3 || second_item == 3){
		if (first_item == 3) effectUserDefault->setIntegerForKey("first_item", 0);
		if (second_item == 3) effectUserDefault->setIntegerForKey("second_item", 0);
		
		numItemsSelected--;
		pIceItem->setOpacity(255);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ItemDeselect.wav");
	}
	else if(numItemsSelected < 2){
		if (first_item == 0) effectUserDefault->setIntegerForKey("first_item",3);
		else if (second_item == 0) effectUserDefault->setIntegerForKey("second_item",3);
		
		numItemsSelected ++;
		pIceItem->setOpacity(100);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ItemSelect.wav");
	}
}
