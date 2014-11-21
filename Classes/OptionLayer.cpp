//
//  OptionLayer.cpp
//  FlappyBirdCpp
//
//  Created by 林光海 on 14-11-21.
//
//

#include "OptionLayer.h"

OptionLayer::OptionLayer()
{

}

OptionLayer::~OptionLayer()
{

}

bool OptionLayer::init()
{
    if(Layer::init()) {
        auto dispatcher = Director::getInstance()->getEventDispatcher();
        auto listenner = EventListenerTouchAllAtOnce::create();
        listenner->onTouchesBegan = CC_CALLBACK_2(OptionLayer::onTouchesBegan, this);
        dispatcher->addEventListenerWithSceneGraphPriority(listenner, this);
        
        return true;
    }else {
        return false;
    }
}

void OptionLayer::onTouchesBegan(const vector<cocos2d::Touch *> &touches, cocos2d::Event *event)
{
    this->delegator->onTouch();
}