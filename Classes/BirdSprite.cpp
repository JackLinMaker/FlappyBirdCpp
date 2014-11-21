//
//  BirdSprite.cpp
//  FlappyBirdCpp
//
//  Created by 林光海 on 14-11-21.
//
//

#include "BirdSprite.h"

BirdSprite* BirdSprite::sharedBirdSprite = nullptr;

BirdSprite* BirdSprite::getInstance()
{
    if(sharedBirdSprite == NULL) {
        sharedBirdSprite = new BirdSprite();
        if(!sharedBirdSprite->init()) {
            delete sharedBirdSprite;
            sharedBirdSprite = NULL;
            CCLOG("ERROR: Could not init shareBirdSprite");
        }
    }
    
    return sharedBirdSprite;
}

BirdSprite::BirdSprite()
{

}

BirdSprite::~BirdSprite()
{

}

bool BirdSprite::init()
{
    this->isFirstTime = 3;
    return true;
}

bool BirdSprite::createBird()
{
    this->createBirdByRandom();
    if(Sprite::initWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameNyName(birdName))) {
        Animation* animation = this->createAnimation(birdNameFormat.c_str(), 3, 10);
        Animate* animate = Animate::create(animation);
        idleAction = RepeatForever::create(animate);
        
        ActionInterval *up = CCMoveBy::create(0.4f, Point(0, 8));
        ActionInterval *down = up->reverse();
        swingAction = RepeatForever::create(Sequence::create(up, down, NULL));
        return true;
    }else {
        return false;
    }
}

void BirdSprite::idle()
{
    if(changeState(ACTION_STATE_IDLE)) {
        this->runAction(idleAction);
        this->runAction(swingAction);
    }
}

void BirdSprite::fly()
{
    if(changeState(ACTION_STATE_FLY)) {
        this->stopAction(swingAction);
        this->getPhysicsBody()->setGravityEnable(true);
    }
}

void BirdSprite::die()
{
    if(changeState(ACTION_STATE_DIE)) {
        this->stopAllActions();
    }
}

Animation* BirdSprite::createAnimation(const char *fmt, int count, float fps)
{
    Animation* animation = Animation::create();
    animation->setDelayPerUnit(1 / fps);
    for (int i = 0; i < count; i++) {
        const char* filename = String::createWithFormat(fmt, i)->getCString();
        SpriteFrame* frame = AtlasLoader::getInstance()->getSpriteFrameNyName(filename);
        animation->addSpriteFrame(frame);
    }
    
    return animation;
}

bool BirdSprite::changeState(ActionState state)
{
    currentState = state;
    return true;
}

void BirdSprite::createBirdByRandom()
{
    if(isFirstTime & 1) {
        isFirstTime &= 2;
    }else if(isFirstTime & 2) {
        isFirstTime &= 1;
        return;
    }
    
    srand((unsigned)time(NULL));
    int type = ((int)rand()) % 3;
    switch (type) {
        case 0:
            this->birdName = "bird0_0";
            this->birdNameFormat = "bird0_%d";
            break;
        case 1:
            this->birdName = "bird1_0";
            this->birdNameFormat = "bird1_%d";
            break;
        case 2:
            this->birdName = "bird2_0";
            this->birdNameFormat = "bird2_%d";
            break;
        default:
            this->birdName = "bird2_0";
            this->birdNameFormat = "bird2_%d";
            break;
    }
}
