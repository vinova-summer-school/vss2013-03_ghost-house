#include "PauseLayer.h"
#include "StartScreenScene.h"

bool PauseLayer::init(){

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	
		CCSprite* PauseDialogBox = CCSprite::create("PauseDialogBox@2x.png");
		//CC_BREAK_IF(! PauseDialogBox);
		PauseDialogBox->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(PauseDialogBox,3);

		// A resume button as a menu item
		CCMenuItemImage *pPauseBox_ResumeItem = CCMenuItemImage::create(
			"PauseBox_ResumeButton@2x.png",
			"PauseBox_ResumeButtonSelected@2x.png",
			this,
			menu_selector(PauseLayer::menuResumeCallback));
		//CC_BREAK_IF(! pPauseBox_ResumeItem);

		pPauseBox_ResumeItem->setPosition(ccp(0.3*PauseDialogBox->getContentSize().width, 0.3*PauseDialogBox->getContentSize().height));

		CCMenu *pPauseBox_Resume = CCMenu::create(pPauseBox_ResumeItem, NULL);
		pPauseBox_Resume->setPosition(CCPointZero);
		//CC_BREAK_IF(! pPauseBox_Resume);

		PauseDialogBox->addChild(pPauseBox_Resume);

		// A Back button as a menu item
		CCMenuItemImage *pPauseBox_MainMenuItem = CCMenuItemImage::create(
			"MainMenuButton@2x.png",
			"MainMenuButtonSelected@2x.png",
			this,
			menu_selector(PauseLayer::menuMainMenuCallback));
		//CC_BREAK_IF(! pPauseBox_MainMenuItem);

		pPauseBox_MainMenuItem->setPosition(ccp(0.7*PauseDialogBox->getContentSize().width, 0.3*PauseDialogBox->getContentSize().height));

		CCMenu *pPauseBox_MainMenu = CCMenu::create(pPauseBox_MainMenuItem, NULL);
		pPauseBox_MainMenu->setPosition(CCPointZero);
		//CC_BREAK_IF(! pPauseBox_MainMenu);

		PauseDialogBox->addChild(pPauseBox_MainMenu);

	

	return true;
}

void PauseLayer::menuResumeCallback(CCObject* pSender){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("click.wav");
	setVisible (false);
	gameLayer->setVisible (true);
	gameLayer->resumeSchedulerAndActions();
	gameLayer->setTouchEnabled (true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void PauseLayer::menuMainMenuCallback(CCObject* pSender){
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("click.wav");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CCDirector::sharedDirector()->replaceScene(StartScreen::scene());
}