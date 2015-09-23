//
//  EventCustomMapped.cpp
//  WaterQuiz
//
//  Created by bibi-apple on 30/12/14.
//
//

#include "EventCustomMapped.h"

#include "Defines.h"

USING_NS_CC;

EventCustomMapped::EventCustomMapped(const std::string& eventName) : EventCustom(eventName)
{
    
}

void EventCustomMapped::setInfo(ValueMap &info)
{
    _info = info;
}

ValueMap &EventCustomMapped::getInfo()
{
    return _info;
}