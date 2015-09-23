//
//  UIManager.cpp
//  WaterQuiz
//
//  Created by bibi-apple on 8/1/15.
//
//

#include "UILockManager.h"

#include "Defines.h"

#include "EventCustomMapped.h"

USE_NS

using namespace std;

UILockManager *UILockManager::getInstance()
{
    static UILockManager *instance;
    if (instance == NULL)
    {
        instance = new UILockManager();
    }
    
    return instance;
}

UILockManager::UILockManager()
{
    
}

void UILockManager::setLockLevel(std::string context, std::uint8_t level)
{
    _uiLockLevelMap[context] = level;
    
    auto eventDispatcher = Director::getInstance()->getEventDispatcher();
    
    EventCustomMapped *event = new EventCustomMapped(EVENT_LOCK_LEVEL_CHANGED);
    ValueMap info;
    info["context"] = context;
    info["lock_level"] = level;
    
    event->setInfo(info);
    
    eventDispatcher->dispatchEvent(event);
}

std::uint8_t UILockManager::getLockLevel(std::string context)
{
    std::uint8_t retVal = 0;
    if (_uiLockLevelMap.find(context) != _uiLockLevelMap.end()) {
        retVal =  _uiLockLevelMap[context];
    }
    
    return retVal;
}

std::uint8_t UILockManager::changeLockLevel(std::string context, int change)
{
    std::uint8_t lockLevel = MAX(0, ((int)getLockLevel(context)) + change);
    setLockLevel(context, lockLevel);
    
    return lockLevel;
}

bool UILockManager::isLocked(std::string context, std::uint8_t lockLevel)
{
    return getLockLevel(context) >= lockLevel;
}
