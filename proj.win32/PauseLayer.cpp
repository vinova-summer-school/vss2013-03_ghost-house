#include "PauseLayer.h"
#include "StartScreenScene.h"

bool PauseLayer::init(){

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	
		CCSprite* PauseDialogBox = CCSprite::create("PauseDialogBox.png");
		//CC_BREAK_IF(! PauseDialogBox);
		PauseDialogBox->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(PauseDialogBox,3);

		// A resume button as a menu item
		CCMenuItemImage *pPauseBox_ResumeItem = CCMenuItemImage::create(
			"PauseBox_ResumeButton.png",
			"PauseBox_ResumeButtonSelected.png",
			this,
			menu_selector(PauseLayer::menuResumeCallback));
		//CC_BREAK_IF(! pPauseBox_ResumeItem);

		pPauseBox_ResumeItem->setPosition(ccp(size.width/2 - 100, size.height/2 - 110));

		CCMenu *pPauseBox_Resume = CCMenu::create(pPauseBox_ResumeItem, NULL);
		pPauseBox_Resume->setPosition(CCPointZero);
		//CC_BREAK_IF(! pPauseBox_Resume);

		PauseDialogBox->addChild(pPauseBox_Resume);

		// A Back button as a menu item
		CCMenuItemImage *pPauseBox_MainMenuItem = CCMenuItemImage::create(
			"MainMenuButton.png",
			"MainMenuButtonSelected.png",
			this,
			menu_selector(PauseLayer::menuMainMenuCallback));
		//CC_BREAK_IF(! pPauseBox_MainMenuItem);

		pPauseBox_MainMenuItem->setPosition(ccp(size.width - 200, size.height - 200));

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
	CCDirector::sharedDirector()->replaceScene(StartScreen::scene());
}