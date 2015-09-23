//
//  ObserverManager.cpp
//  WaterQuiz
//
//  Created by bibi-apple on 29/12/14.
//
//

#include "ObserverManager.h"

USING_NS_CC;

ObserverManager *ObserverManager::getInstance()
{
    static ObserverManager* instance;
    if (instance == NULL) {
        instance = new ObserverManager();
    }
    
    return instance;
}

void ObserverManager::addObserver(cocos2d::Ref *ref, std::string name, const std::function<void (cocos2d::EventCustom *)> &callback)
{
    EventListenerCustom *customListener = Director::getInstance()->getEventDispatcher()->addCustomEventListener(name, callback);
    
    std::uintptr_t refKey = getObjectPointerAddress(ref);
    
    Vector<EventListenerCustom*> observers;
    
    if (_observers.find(refKey) != _observers.end())
    {
        observers = _observers.at(refKey);
    }
    
    observers.pushBack(customListener);
    _observers.erase(refKey);
    _observers[refKey] = observers;
}

void ObserverManager::removeObservers(cocos2d::Ref *ref)
{
    std::uintptr_t refKey = getObjectPointerAddress(ref);
    
    if (_observers.find(refKey) != _observers.end())
    {
        Vector<EventListenerCustom*> observers = _observers.at(refKey);
        
        for (int x = 0; x < observers.size(); x++)
        {
            EventListenerCustom *eventListener = observers.at(x);
            Director::getInstance()->getEventDispatcher()->removeEventListener(eventListener);
        }
        
        _observers.erase(refKey);
    }
    
    Node *node = dynamic_cast<Node *>(ref);
    if (node != nullptr)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(node, true);
    }
}

std::uintptr_t ObserverManager::getObjectPointerAddress(cocos2d::Ref *ref)
{
    return reinterpret_cast<std::uintptr_t>(ref);
}