//
//  BackgroundLayer.cpp
//  FlappyBirdCpp
//
//  Created by 林光海 on 14-11-21.
//
//

#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer()
{

}

BackgroundLayer::~BackgroundLayer()
{

}

bool BackgroundLayer::init()
{
    if(!Layer::init()) {
        return false;
    }
    
    time_t t = time(NULL);
    tm* lt = localtime(&t);
    int hour = lt->tm_hour;
    
    Sprite *background;
    if(hour >= 6 && hour <= 17) {
        background = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameNyName("bg_day"));
    }else {
        background = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameNyName("bg_night"));
    }
    background->setAnchorPoint(Point::ZERO);
    background->setPosition(Point::ZERO);
    this->addChild(background);
    return true;
}

float BackgroundLayer::getLandHeight()
{
    return Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameNyName("land"))->getContentSize().height;
}