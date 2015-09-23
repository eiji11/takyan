//
//  UIManager.h
//  WaterQuiz
//
//  Created by bibi-apple on 8/1/15.
//
//

#ifndef __WaterQuiz__UIManager__
#define __WaterQuiz__UIManager__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"


#define UI_LOCK_CONTEXT_DEFAULT "default"
#define UI_LOCK_CONTEXT_MAIN_MENU "main_menu"

#define VAR_LOCK_CONTEXT _uiContext
#define MAKE_CONTEXT(contextName) \
std::string VAR_LOCK_CONTEXT = contextName

#define VAR_LOCK_LEVEL _uiLockLevel
#define MAKE_LOCK_LEVEL(value) \
std::uint8_t VAR_LOCK_LEVEL = value

#define UI_LOCK_MANAGER UILockManager::getInstance()
#define IS_LOCKED UI_LOCK_MANAGER->isLocked(VAR_LOCK_CONTEXT, VAR_LOCK_LEVEL)

#define UI_LOCK_MANAGER_INCREASE() \
UI_LOCK_MANAGER->changeLockLevel(VAR_LOCK_CONTEXT, 1)

#define UI_LOCK_MANAGER_DECREASE() \
UI_LOCK_MANAGER->changeLockLevel(VAR_LOCK_CONTEXT, -1)

#define EVENT_LOCK_LEVEL_CHANGED "lock_level_changed"

class UILockManager
{
public:
    static UILockManager *getInstance();
    
    UILockManager();
    
    void setLockLevel(std::string context, std::uint8_t level);
    std::uint8_t getLockLevel(std::string context);
    std::uint8_t changeLockLevel(std::string context, int change = 1);
    bool isLocked(std::string context, std::uint8_t lockLevel);
    
private:
    std::unordered_map<std::string, std::uint8_t> _uiLockLevelMap;
    
    int a = 1;
};

#endif /* defined(__WaterQuiz__UIManager__) */
