//
//  ObserverManager.h
//  WaterQuiz
//
//  Created by bibi-apple on 29/12/14.
//
//

#ifndef __WaterQuiz__ObserverManager__
#define __WaterQuiz__ObserverManager__

#include "cocos2d.h"

#include "Defines.h"

#define OBSERVE(ref, name, callback) \
ObserverManager::getInstance()->addObserver(ref, name, callback)

#define UNOBSERVE(ref) \
ObserverManager::getInstance()->removeObservers(ref)

class ObserverManager
{
public:
    static ObserverManager *getInstance();
    
    void addObserver(cocos2d::Ref *ref, std::string name, const std::function<void (cocos2d::EventCustom *)> &callback);
    
    void removeObservers(cocos2d::Ref *ref);
    
    static std::uintptr_t getObjectPointerAddress(cocos2d::Ref *ref);
    
private:
    std::map<std::uintptr_t, cocos2d::Vector<cocos2d::EventListenerCustom*>> _observers;
};

#endif /* defined(__WaterQuiz__ObserverManager__) */
