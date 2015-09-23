#include "BattleInfoMenu.h"

#include "MainMenuScene.h"
#include "VersusScene.h"
#include "PlaceSelect.h"

#include "managers_caches/AssortedUtils.h"
#include "objects/VersusGameData.h"


USE_NS

using namespace ui;

BattleInfoMenu *BattleInfoMenu::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("BattleInfoMenu", BattleInfoMenuLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<BattleInfoMenu*>(ccbReader->readNodeGraphFromFile("BattleInfoMenu.ccbi"));
}

BattleInfoMenu::BattleInfoMenu() : cocos2d::Layer()
, _labelTitle(NULL)
, _buttonOk(NULL)
, _buttonBack(NULL)
, _buttonHome(NULL)
, _labelRounds(NULL)
, _buttonBestOf1(NULL)
, _buttonBestOf3(NULL)
, _buttonBestOf5(NULL)
, _labelHits(NULL)
, _placeHolderInputHits(NULL)
, _textfieldBG(NULL)

, _inputHits(NULL)
, _versusConfig(nullptr)
, _sets(1)
{

}

BattleInfoMenu::~BattleInfoMenu()
{
	CC_SAFE_RELEASE(_labelTitle);
	CC_SAFE_RELEASE(_buttonOk);
	CC_SAFE_RELEASE(_buttonBack);
	CC_SAFE_RELEASE(_buttonHome);
    CC_SAFE_RELEASE(_labelRounds);
    CC_SAFE_RELEASE(_buttonBestOf1);
    CC_SAFE_RELEASE(_buttonBestOf3);
    CC_SAFE_RELEASE(_buttonBestOf5);
    CC_SAFE_RELEASE(_labelHits);
    CC_SAFE_RELEASE(_placeHolderInputHits);
    CC_SAFE_RELEASE(_textfieldBG);
}

void BattleInfoMenu::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    animationManager->setDelegate(this);

	setKeyboardEnabled(true);
    
    _inputHits->setString("3");
    
    UI_LOCK_MANAGER_INCREASE();
}

void BattleInfoMenu::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    animationManager->setDelegate(NULL);
    
    UI_LOCK_MANAGER_DECREASE();
}

void BattleInfoMenu::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if ((keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) && !IS_LOCKED) {
    	this->runAction(CallFunc::create([&](){
    		onPressOk(_buttonBack, Control::EventType::TOUCH_UP_INSIDE);
    	}));
    }
}

void BattleInfoMenu::onPressOk(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
        std::string hitsString = _inputHits->getString();
        auto isNumericOnly = [&](const std::string& s)
        {
            std::string::const_iterator it = s.begin();
            while (it != s.end() && std::isdigit(*it)) ++it;
            return !s.empty() && it == s.end();
        };

        if (!isNumericOnly(hitsString))
        {
        	return;
        }
        int hits = Value(hitsString).asInt();
        
        _versusConfig->setSets(_sets);
        _versusConfig->setHitsPerRound(hits);
        
        VersusGameData *game = VersusGameData::create(_versusConfig);
        
        float randomF = AssortedUtils::random01() * 2.f;
        cocos2d::log("RANDOM: %.2f", randomF);
        game->setCurrentPlayerIndex((int)(randomF));
        
        VersusScene *layer = VersusScene::createFromCCB();
        layer->setGameData(game);
        
        Scene *scene = Scene::createWithPhysics();
        scene->addChild(layer);
        
        Director::getInstance()->replaceScene(scene);
	}
}

void BattleInfoMenu::onPressBack(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        PlaceSelect *d = PlaceSelect::createFromCCB();
        d->setVersusGameConfig(_versusConfig);
        
        Director::getInstance()->getRunningScene()->addChild(d, 1000);
        this->removeFromParent();
	}
}

void BattleInfoMenu::onPressHome(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
        MainMenuScene *l = MainMenuScene::createFromCCB();
        Scene *s = Scene::create();
        s->addChild(l);
        Director::getInstance()->replaceScene(s);
    }
}

void BattleInfoMenu::onPressBestOf(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
        _buttonBestOf1->setHighlighted(sender == _buttonBestOf1);
        _buttonBestOf3->setHighlighted(sender == _buttonBestOf3);
        _buttonBestOf5->setHighlighted(sender == _buttonBestOf5);
        
        if (sender == _buttonBestOf1)
        {
            _sets = 1;
        }
        else if (sender == _buttonBestOf3)
        {
            _sets = 3;
        }
        else if (sender == _buttonBestOf5)
        {
            _sets = 5;
        }
    }
}


#pragma mark - CCBMemberVariableAssigner functions

bool BattleInfoMenu::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelTitle", cocos2d::Label*, _labelTitle);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonOk", cocos2d::extension::ControlButton*, _buttonOk);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBack", cocos2d::extension::ControlButton*, _buttonBack);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonHome", cocos2d::extension::ControlButton*, _buttonHome);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelRounds", cocos2d::Label*, _labelRounds);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBestOf1", cocos2d::extension::ControlButton*, _buttonBestOf1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBestOf3", cocos2d::extension::ControlButton*, _buttonBestOf3);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBestOf5", cocos2d::extension::ControlButton*, _buttonBestOf5);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelHits", cocos2d::Label*, _labelHits);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_placeHolderInputHits", cocos2d::Node*, _placeHolderInputHits);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_textfieldBG", cocos2d::LayerColor*, _textfieldBG);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler BattleInfoMenu::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressOk", BattleInfoMenu::onPressOk);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressBack", BattleInfoMenu::onPressBack);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressHome", BattleInfoMenu::onPressHome);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressBestOf", BattleInfoMenu::onPressBestOf);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void BattleInfoMenu::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
    _buttonBestOf1->setHighlighted(true);
    
    /*
    _inputHits = EditBox::create(_placeHolderInputHits->getContentSize(), "ccbResources/ccbTextField.png", Widget::TextureResType::PLIST);
    _inputHits->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _inputHits->setFontColor(Color3B::BLACK);
    _inputHits->setInputMode(EditBox::InputMode::NUMERIC);
    _inputHits->setReturnType(EditBox::KeyboardReturnType::DONE);
    _placeHolderInputHits->addChild(_inputHits);
    */

    _inputHits = TextField::create();
    _inputHits->setColor(Color3B::BLACK);
    _inputHits->setMaxLengthEnabled(true);
    _inputHits->setMaxLength(2);

	Size tSize = _textfieldBG->getContentSize();
	_inputHits->setPosition(Vec2(tSize.width * 0.5f, tSize.height * 0.5f));
	_inputHits->setSize(tSize);

    _textfieldBG->addChild(_inputHits);
}


#pragma mark - CCBAnimationManagerDelegate functions

void BattleInfoMenu::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


