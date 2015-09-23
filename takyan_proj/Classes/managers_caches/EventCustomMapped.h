//
//  EventCustomMapped.h
//  WaterQuiz
//
//  Created by bibi-apple on 30/12/14.
//
//

#ifndef __WaterQuiz__EventCustomMapped__
#define __WaterQuiz__EventCustomMapped__

#include "cocos2d.h"

NS_CC_BEGIN

class EventCustomMapped : public EventCustom
{
public:
    EventCustomMapped(const std::string& eventName);
    
    void setInfo(ValueMap &info);
    ValueMap &getInfo();
    
protected:
    ValueMap _info;
    
};

NS_CC_END

#endif /* defined(__WaterQuiz__EventCustomMapped__) */
