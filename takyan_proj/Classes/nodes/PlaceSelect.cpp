#include "PlaceSelect.h"

#include "BattleInfoMenu.h"
#include "MainMenuScene.h"
#include "PlayerSelect.h"
#include "SinglePlayerScene.h"

#include "managers_caches/AssortedUtils.h"


USE_NS

PlaceSelect *PlaceSelect::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("PlaceSelect", PlaceSelectLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<PlaceSelect*>(ccbReader->readNodeGraphFromFile("PlaceSelect.ccbi"));
}

PlaceSelect::PlaceSelect() : cocos2d::Layer()
, _labelTitle(NULL)
, _borderPlace1(NULL)
, _buttonPlace1(NULL)
, _labelPlaceName1(NULL)
, _borderPlace2(NULL)
, _buttonPlace2(NULL)
, _labelPlaceName2(NULL)
, _borderPlace3(NULL)
, _buttonPlace3(NULL)
, _labelPlaceName3(NULL)
, _buttonOk(NULL)
, _buttonBack(NULL)
, _buttonHome(NULL)

, _singleGameData(nullptr)
, _versusConfig(nullptr)
{

}

PlaceSelect::~PlaceSelect()
{
	CC_SAFE_RELEASE(_labelTitle);
	CC_SAFE_RELEASE(_borderPlace1);
	CC_SAFE_RELEASE(_buttonPlace1);
	CC_SAFE_RELEASE(_labelPlaceName1);
	CC_SAFE_RELEASE(_borderPlace2);
	CC_SAFE_RELEASE(_buttonPlace2);
	CC_SAFE_RELEASE(_labelPlaceName2);
	CC_SAFE_RELEASE(_borderPlace3);
	CC_SAFE_RELEASE(_buttonPlace3);
	CC_SAFE_RELEASE(_labelPlaceName3);
	CC_SAFE_RELEASE(_buttonOk);
	CC_SAFE_RELEASE(_buttonBack);
	CC_SAFE_RELEASE(_buttonHome);
}

void PlaceSelect::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	setKeyboardEnabled(true);
    
    int level = 0;
    if (isForVersus())
    {
        level = _versusConfig->getHighestLevel();
    }
    else
    {
        level = _singleGameData->getPlayer()->getLevel();
    }
    
    ControlButton *bgButtons[] = { _buttonPlace1, _buttonPlace2, _buttonPlace3 };
    
    for (int x = 1; x < 3; x++)
    {
        bgButtons[x]->setEnabled(x <= level);
    }
    _buttonPlace1->setEnabled(true);
    _borderPlace1->setColor(Color3B::WHITE);
    _selectedBackground = "battle places/bg_lvl1_morning.png";
    
    UI_LOCK_MANAGER_INCREASE();
}

void PlaceSelect::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);
    
    UI_LOCK_MANAGER_DECREASE();
}

void PlaceSelect::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if ((keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) && !IS_LOCKED) {
    	this->runAction(CallFunc::create([&](){
    		onPressBack(_buttonBack, Control::EventType::TOUCH_UP_INSIDE);
    	}));
    }
}

void PlaceSelect::clearSelection()
{
    _borderPlace1->setColor(Color3B::BLACK);
    _borderPlace2->setColor(Color3B::BLACK);
    _borderPlace3->setColor(Color3B::BLACK);
}

void PlaceSelect::onPressPlace(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        clearSelection();
        if (sender == _buttonPlace1)
        {
            _selectedBackground = "battle places/bg_lvl1_morning.png";
            _borderPlace1->setColor(Color3B::WHITE);
        }
        else if (sender == _buttonPlace2)
        {
            _selectedBackground = "battle places/bg_lvl2_sunset.png";
            _borderPlace2->setColor(Color3B::WHITE);
        }
        else if (sender == _buttonPlace3)
        {
            _selectedBackground = "battle places/bg_lvl3_night.png";
            _borderPlace3->setColor(Color3B::WHITE);
        }
	}
}

void PlaceSelect::onPressOk(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        if (!_selectedBackground.empty())
        {
            if (isForVersus())
            {
                _versusConfig->setBackground(_selectedBackground);
                BattleInfoMenu *d = BattleInfoMenu::createFromCCB();
                d->setVersusGameConfig(_versusConfig);
                
                this->removeFromParent();
                Director::getInstance()->getRunningScene()->addChild(d, 1000);
            }
            else
            {
                _singleGameData->setBackground(_selectedBackground);
                
                SinglePlayerScene *layer = SinglePlayerScene::createFromCCB();
                layer->setGameData(_singleGameData);
                
                Scene *scene = Scene::createWithPhysics();
                scene->addChild(layer);
                
                Director::getInstance()->replaceScene(scene);
            }
        }
	}
}

void PlaceSelect::onPressBack(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
        PlayerSelect *d = PlayerSelect::createFromCCB();
        
        if (isForVersus())
        {
            _versusConfig->setPlayer2(nullptr);
            
            d->setVersusGameConfig(_versusConfig);
        }
        
        this->removeFromParent();
        Director::getInstance()->getRunningScene()->addChild(d, 1000);
	}
}

void PlaceSelect::onPressHome(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
        MainMenuScene *l = MainMenuScene::createFromCCB();
        Scene *s = Scene::create();
        s->addChild(l);
        Director::getInstance()->replaceScene(s);
	}
}


#pragma mark - CCBMemberVariableAssigner functions

bool PlaceSelect::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelTitle", cocos2d::Label*, _labelTitle);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_borderPlace1", cocos2d::LayerColor*, _borderPlace1);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonPlace1", cocos2d::extension::ControlButton*, _buttonPlace1);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelPlaceName1", cocos2d::Label*, _labelPlaceName1);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_borderPlace2", cocos2d::LayerColor*, _borderPlace2);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonPlace2", cocos2d::extension::ControlButton*, _buttonPlace2);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelPlaceName2", cocos2d::Label*, _labelPlaceName2);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_borderPlace3", cocos2d::LayerColor*, _borderPlace3);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonPlace3", cocos2d::extension::ControlButton*, _buttonPlace3);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelPlaceName3", cocos2d::Label*, _labelPlaceName3);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonOk", cocos2d::extension::ControlButton*, _buttonOk);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBack", cocos2d::extension::ControlButton*, _buttonBack);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonHome", cocos2d::extension::ControlButton*, _buttonHome);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler PlaceSelect::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressPlace", PlaceSelect::onPressPlace);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressOk", PlaceSelect::onPressOk);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressBack", PlaceSelect::onPressBack);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressHome", PlaceSelect::onPressHome);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void PlaceSelect::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
    auto children = this->getChildren().front()->getChildren();
    for (auto child : children)
    {
        child->setLocalZOrder(1);
    }
    
    AssortedUtils::unifyButtonSprites(_buttonOk, "single_player/btn_ok.png");
    AssortedUtils::unifyButtonSprites(_buttonBack, "single_player/btn_back.png");
    AssortedUtils::unifyButtonSprites(_buttonHome, "single_player/btn_home.png");
}


#pragma mark - CCBAnimationManagerDelegate functions

void PlaceSelect::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


