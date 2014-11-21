//
//  OptionLayer.h
//  FlappyBirdCpp
//
//  Created by 林光海 on 14-11-21.
//
//

#ifndef __FlappyBirdCpp__OptionLayer__
#define __FlappyBirdCpp__OptionLayer__

#include "cocos2d.h"
#include <vector>
using namespace cocos2d;
using namespace std;

class OptionDelegate
{
public:
    virtual void onTouch() = 0;
};

class OptionLayer : public Layer
{
public:
    OptionLayer();
    
    ~OptionLayer();
    
    virtual bool init();
    
    CREATE_FUNC(OptionLayer);
    
    void onTouchesBegan(const vector<Touch*>& touches, Event *event);
    
    CC_SYNTHESIZE(OptionDelegate*, delegator, Delegator);
};

#endif /* defined(__FlappyBirdCpp__OptionLayer__) */
