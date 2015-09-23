#include "MainMenuScene.h"

#include "SinglePlayerScene.h"
#include "VersusScene.h"
#include "PlayerSelect.h"
#include "RecordsDialog.h"
#include "InstructionsDialog.h"
#include "TriviaDialog.h"
#include "ConfirmDialog.h"

#include "objects/PlayerData.h"
#include "objects/PlayerManager.h"
#include "objects/SingleGameData.h"

#include "managers_caches/AssortedUtils.h"

#define COCOS2D_DEBUG 1

USE_NS

MainMenuScene*MainMenuScene::createFromCCB() {
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("MainMenuScene", MainMenuSceneLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<MainMenuScene*>(ccbReader->readNodeGraphFromFile("MainMenuScene.ccbi"));
}

MainMenuScene::MainMenuScene() : cocos2d::Layer()
, _buttonSingle(NULL)
, _buttonVersus(NULL)
, _buttonPractice(NULL)
, _buttonRecords(NULL)
, _buttonInstructions(NULL)
{

}

MainMenuScene::~MainMenuScene() {
	CC_SAFE_RELEASE(_buttonSingle);
	CC_SAFE_RELEASE(_buttonVersus);
	CC_SAFE_RELEASE(_buttonPractice);
	CC_SAFE_RELEASE(_buttonRecords);
	CC_SAFE_RELEASE(_buttonInstructions);
}

void MainMenuScene::onEnter() {
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	setKeyboardEnabled(true);
    
    if (!TriviaDialog::shown)
    {
        this->runAction(CallFunc::create([&](){
            TriviaDialog *d = TriviaDialog::createFromCCB();
            
            Director::getInstance()->getRunningScene()->addChild(d, 1000);
        }));
        TriviaDialog::shown = true;
    }
}

void MainMenuScene::onExit() {
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

}

void MainMenuScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	cocos2d::log("MAIN MENU BACK: %d", UI_LOCK_MANAGER->getLockLevel(VAR_LOCK_CONTEXT));
    if ((keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) && !IS_LOCKED) {
    	this->runAction(CallFunc::create([&](){
            ConfirmDialog *d = ConfirmDialog::createFromCCB();
            d->setOkCallback([&](){
            	Director::getInstance()->end();
            });
            Director::getInstance()->getRunningScene()->addChild(d, 1000);
    	}));
    }
}

void MainMenuScene::onPressSingle(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent) {
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
	{
		cocos2d::log("---------SINGLE-----------");
		auto layer = PlayerSelect::createFromCCB();
		Director::getInstance()->getRunningScene()->addChild(layer, 1000);
	}
}

void MainMenuScene::onPressVersus(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent) {
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
	{
		auto layer = PlayerSelect::createFromCCB();
		layer->setForVersus(true);

		Director::getInstance()->getRunningScene()->addChild(layer, 1000);
	}
}

void MainMenuScene::onPressPractice(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent) {
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
	{
		auto layer = PlayerSelect::createFromCCB();
		layer->setForPractice(true);

		Director::getInstance()->getRunningScene()->addChild(layer, 1000);
	}
}

void MainMenuScene::onPressBattleRecords(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent) {
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED) {
		auto layer = RecordsDialog::createFromCCB();
		Director::getInstance()->getRunningScene()->addChild(layer, 1000);
	}
}

void MainMenuScene::onPressInstructions(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent) {
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED) {
		InstructionsDialog *d = InstructionsDialog::createFromCCB();
		Director::getInstance()->getRunningScene()->addChild(d, 1000);
	}
}

#pragma mark - CCBMemberVariableAssigner functions

bool MainMenuScene::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode) {
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonSingle", cocos2d::extension::ControlButton*, _buttonSingle);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonVersus", cocos2d::extension::ControlButton*, _buttonVersus);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonPractice", cocos2d::extension::ControlButton*, _buttonPractice);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonRecords", cocos2d::extension::ControlButton*, _buttonRecords);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonInstructions", cocos2d::extension::ControlButton*, _buttonInstructions);

	return false;
}

#pragma mark - CCBSelectorResolver functions

Control::Handler MainMenuScene::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName) {
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressSingle", MainMenuScene::onPressSingle);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressVersus", MainMenuScene::onPressVersus);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressPractice", MainMenuScene::onPressPractice);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressBattleRecords", MainMenuScene::onPressBattleRecords);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressInstructions", MainMenuScene::onPressInstructions);

	return NULL;
}

#pragma mark - NodeLoaderListener functions

void MainMenuScene::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader) {
	AssortedUtils::unifyButtonSprites(_buttonSingle, "main_menu/button_single_game.png");
	AssortedUtils::unifyButtonSprites(_buttonVersus, "main_menu/button_versus_game.png");
	AssortedUtils::unifyButtonSprites(_buttonPractice, "main_menu/button_practice_game.png");
	AssortedUtils::unifyButtonSprites(_buttonRecords, "main_menu/button_records_single.png");
}

#pragma mark - CCBAnimationManagerDelegate functions

void MainMenuScene::completedAnimationSequenceNamed(const char *name) {
	if (strcmp(name, "Default Timeline") == 0) {

	}

}
