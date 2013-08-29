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
        // Create a "back" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pBackItem = CCMenuItemImage::create(
            "BackArrow.png",
            "BackArrowSelected.png",
            this,
            menu_selector(Preferences::menuBackCallback));
        CC_BREAK_IF(! pBackItem);

        // Place the menu item top-left conner.
		pBackItem->setPosition(ccp(0.07*size.width, 0.92*size.height));

        // Create a menu with the "back" menu item, it's an auto release object.
        CCMenu* pBack = CCMenu::create(pBackItem, NULL);
        pBack->setPosition(CCPointZero);
        CC_BREAK_IF(! pBack);

        // Add the menu to Preferences layer as a child layer.
        this->addChild(pBack, 1);
		//////////////////*****END OF MENU ITEMS***********/////////////////////

        // Create a label and initialize with string "Preferences".
		CCLabelTTF* pPrefMainTitle = CCLabelTTF::create("Choose up to 2 items", "Verdana", (int)(size.height/10));
		ccColor3B PrefMainTitleColor = {255,255,0};
		pPrefMainTitle->setColor(PrefMainTitleColor);

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

		pSlowItem->setPosition(ccp(0.1*size.width, 0.68*size.height));

		CCMenu* pSlow = CCMenu::create(pSlowItem,NULL);
		pSlow->setPosition(CCPointZero);
		CC_BREAK_IF(! pSlow);

		this->addChild(pSlow, 4);

		pFirstItem = CCLabelTTF::create("Makes the ghosts moving slower\nfor a while", "Calibri", (int)(size.height/16));
        CC_BREAK_IF(! pFirstItem);
        // place the label upper.
		pFirstItem->setAnchorPoint(ccp(0,0.5));
		pFirstItem->setPosition(ccp(0.2*size.width, 0.68*size.height));

        // Add the label to GamePlay layer as a child layer.
        this->addChild(pFirstItem, 6);


		if(first_item == 1 || second_item == 1){
			pSlowItem->setOpacity(100);
			numItemsSelected++;
		}

		// Create a Super Damage Item
		psuperDamageItem = CCMenuItemImage::create("superDamage.png","superDamage.png",
			this,
			menu_selector(Preferences::superDamageCallback));
		CC_BREAK_IF(! psuperDamageItem);

		psuperDamageItem->setPosition(ccp(0.1*size.width , 0.44*size.height));

		CCMenu* psuperDamage = CCMenu::create(psuperDamageItem,NULL);
		psuperDamage->setPosition(CCPointZero);
		CC_BREAK_IF(! psuperDamage);

		this->addChild(psuperDamage, 4);

		pSecondItem = CCLabelTTF::create("Lets you have the highest\nattack damage ever for a while", "Calibri", (int)(size.height/16));
        CC_BREAK_IF(! pSecondItem);
        // place the label upper.
		pSecondItem->setAnchorPoint(ccp(0,0.5));
		pSecondItem->setPosition(ccp(0.2*size.width, 0.44*size.height));

        // Add the label to GamePlay layer as a child layer.
        this->addChild(pSecondItem, 6);



		if(first_item == 2 || second_item == 2){
			psuperDamageItem->setOpacity(100);
			numItemsSelected++;
		}

		// Create ice item
		pIceItem = CCMenuItemImage::create("ice.png","ice.png",
			this,
			menu_selector(Preferences::iceEffectCallback));
		CC_BREAK_IF(! pIceItem);

		pIceItem->setPosition(ccp(0.1*size.width, 0.19*size.height));

		CCMenu* pIce = CCMenu::create(pIceItem,NULL);
		pIce->setPosition(CCPointZero);
		CC_BREAK_IF(! pIce);

		this->addChild(pIce, 4);

		pThirdItem = CCLabelTTF::create("Freezes all ghosts on the screen\nfor a while", "Calibri", (int)(size.height/16));
        CC_BREAK_IF(! pThirdItem);
        // place the label upper.
		pThirdItem->setAnchorPoint(ccp(0,0.5));
		pThirdItem->setPosition(ccp(0.2*size.width, 0.19*size.height));

        // Add the label to GamePlay layer as a child layer.
        this->addChild(pThirdItem, 6);


		if(first_item == 3 || second_item == 3){
			pIceItem->setOpacity(100); 
			numItemsSelected++;
		}

        // 3. Add add a splash screen
        CCSprite* pSprite = CCSprite::create("OptionSprite.png");
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

void Preferences::menuBackCallback(CCObject* pSender){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("click.wav");
	CCTransitionCrossFade* trans = CCTransitionCrossFade::create(0.4f, StartScreen::scene());
	CCDirector::sharedDirector()->replaceScene(trans);
}

void Preferences::SlowCallback(CCObject* pSender){
	first_item = effectUserDefault->getIntegerForKey("first_item", 0);
	second_item = effectUserDefault->getIntegerForKey("second_item", 0);
	
	if(first_item == 1 || second_item == 1){
		if (first_item == 1) effectUserDefault->setIntegerForKey("first_item", 0);
		if (second_item == 1) effectUserDefault->setIntegerForKey("second_item", 0);
		
		numItemsSelected--;
		pSlowItem->setOpacity(255);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("tick.wav");
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
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("tick.wav");
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
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("tick.wav");
	}
	else if(numItemsSelected < 2){
		if (first_item == 0) effectUserDefault->setIntegerForKey("first_item",3);
		else if (second_item == 0) effectUserDefault->setIntegerForKey("second_item",3);
		
		numItemsSelected ++;
		pIceItem->setOpacity(100);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("ItemSelect.wav");
	}
}
