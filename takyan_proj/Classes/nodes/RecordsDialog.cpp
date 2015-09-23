#include "RecordsDialog.h"

#include "RecordsDialogEntry.h"


USE_NS

static Size CELL_SIZE(390, 30);

RecordsDialog *RecordsDialog::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("RecordsDialog", RecordsDialogLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<RecordsDialog*>(ccbReader->readNodeGraphFromFile("RecordsDialog.ccbi"));
}

RecordsDialog::RecordsDialog() : cocos2d::Layer()
, _containerRecordsTable(NULL)
, _labelTitle(NULL)
, _buttonOk(NULL)
{

}

RecordsDialog::~RecordsDialog()
{
	CC_SAFE_RELEASE(_containerRecordsTable);
	CC_SAFE_RELEASE(_labelTitle);
	CC_SAFE_RELEASE(_buttonOk);
}

void RecordsDialog::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	setKeyboardEnabled(true);
    
    loadPlayers();
    
    _tableView = TableView::create(this, _containerRecordsTable->getContentSize());
    
    _containerRecordsTable->addChild(_tableView);
    
    UI_LOCK_MANAGER_INCREASE();
}

void RecordsDialog::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

	_tableView->setDelegate(nullptr);
	_tableView->setDataSource(nullptr);
    
    UI_LOCK_MANAGER_DECREASE();
}

void RecordsDialog::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
    	this->runAction(CallFunc::create([&](){
    		this->removeFromParent();
    	}));
    }
    
}

void RecordsDialog::loadPlayers()
{
    Map<std::string, PlayerData *> playersMap = PlayerManager::getInstance()->getPlayers();
    
    _players.clear();
    for (auto itr : playersMap)
    {
        _players.pushBack(itr.second);
    }
    
    std::sort(_players.begin(), _players.end(), [&](PlayerData *first, PlayerData *second){
        return first->getLevel() < second->getLevel();
    });
}

void RecordsDialog::onPressOk(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        this->removeFromParent();
	}
}


#pragma mark - CCTableView methods

Size RecordsDialog::cellSizeForTable(cocos2d::extension::TableView *table)
{
    return CELL_SIZE;
}

TableViewCell* RecordsDialog::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    PlayerData *player = _players.at(idx);
    
    TableViewCell *cell = TableViewCell::create();
    
    RecordsDialogEntry *entry = RecordsDialogEntry::createFromCCB();
    
    entry->setPlayer(player);
    
    cell->addChild(entry);
    
    return cell;
}

ssize_t RecordsDialog::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return _players.size();
}



#pragma mark - CCBMemberVariableAssigner functions

bool RecordsDialog::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerRecordsTable", cocos2d::Node*, _containerRecordsTable);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelTitle", cocos2d::Label*, _labelTitle);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonOk", cocos2d::extension::ControlButton*, _buttonOk);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler RecordsDialog::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressOk", RecordsDialog::onPressOk);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void RecordsDialog::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void RecordsDialog::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


