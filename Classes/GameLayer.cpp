//
//  GameLayer.cpp
//  FlappyBirdCpp
//
//  Created by 林光海 on 14-11-21.
//
//

#include "GameLayer.h"

GameLayer::GameLayer()
{

}

GameLayer::~GameLayer()
{

}

bool GameLayer::init()
{
    if(Layer::init()) {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Point origin = Director::getInstance()->getVisibleOrigin();
        
        gameStatus = GAME_STATUS_READY;
        score = 0;
        
        // Add the bird
        bird = BirdSprite::getInstance();
        bird->createBird();
        PhysicsBody *body = PhysicsBody::create();
        body->addShape(PhysicsShapeCircle::create(BIRD_RADIUS));
        body->setDynamic(true);
        body->setLinearDamping(0.0f);
        body->setGravityEnable(false);
        bird->setPhysicsBody(body);
        bird->setPosition(origin.x + visibleSize.width / 3 - 5, origin.y + visibleSize.height * 0.5 + 5);
        bird->idle();
        this->addChild(bird);
        
        // Add the ground
        groundNode = Node::create();
        float landHeight = BackgroundLayer::getLandHeight();
        auto groundBody = PhysicsBody::create();
        groundBody->addShape(PhysicsShapeBox::create(Size(288, landHeight)));
        groundBody->setDynamic(false);
        groundBody->setLinearDamping(0.0f);
        
        this->groundNode->setPhysicsBody(groundBody);
        this->groundNode->setPosition(144, landHeight / 2);
        this->addChild(this->groundNode);
        
        // init land
        this->landSprite1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameNyName("land"));
        this->landSprite1->setAnchorPoint(Point::ZERO);
        this->landSprite1->setPosition(Point::ZERO);
        this->addChild(this->landSprite1, 30);
        
        this->landSprite2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameNyName("land"));
        this->landSprite2->setAnchorPoint(Point::ZERO);
        this->landSprite2->setPosition(this->landSprite1->getContentSize().width-2.0f,0);
        this->addChild(this->landSprite2, 30);
        
        shiftLand = schedule_selector(GameLayer::scrollLand);
        this->schedule(shiftLand, 0.01f);
        
        this->scheduleUpdate();
        
        auto contactListener = EventListenerPhysicsContact::create();
        contactListener->onContactBegin = CC_CALLBACK_2(GameLayer::onContactBegin, this);
        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
        
        return true;
    }
    
    return false;
}

bool GameLayer::onContactBegin(cocos2d::EventCustom *event, const cocos2d::PhysicsContact &contact)
{
    this->gameOver();
    return true;
}

void GameLayer::scrollLand(float dt)
{
    this->landSprite1->setPositionX(this->landSprite1->getPositionX() - 2.0f);
	this->landSprite2->setPositionX(this->landSprite1->getPositionX() + this->landSprite1->getContentSize().width - 2.0f);
    if(this->landSprite2->getPositionX() == 0) {
        this->landSprite1->setPositionX(0);
    }
    
    // move the pips
    for(auto singlePip : this->pips) {
        singlePip->setPositionX(singlePip->getPositionX() - 2);
        if(singlePip->getPositionX() < -PIP_WIDTH) {
            singlePip->setTag(PIP_NEW);
            Size visibleSize = Director::getInstance()->getVisibleSize();
            singlePip->setPositionX(visibleSize.width);
            singlePip->setPositionY(this->getRandomHeight());
        }
    }
}

void GameLayer::onTouch()
{
    if(this->gameStatus == GAME_STATUS_OVER) {
        return;
    }
    
    SimpleAudioEngine::getInstance()->playEffect("sfx_wing.ogg");
	if(this->gameStatus == GAME_STATUS_READY) {
		this->delegator->onGameStart();
		this->bird->fly();
		this->gameStatus = GAME_STATUS_START;
        this->createPips();
	}else if(this->gameStatus == GAME_STATUS_START) {
		this->bird->getPhysicsBody()->setVelocity(Vect(0, 260));
	}
}

void GameLayer::rotateBird()
{
    float verticalSpeed = this->bird->getPhysicsBody()->getVelocity().y;
    this->bird->setRotation(min(max(-90, (verticalSpeed * 0.2 + 60)), 30));
}

void GameLayer::update(float delta)
{
    if(this->gameStatus == GAME_STATUS_START) {
        this->rotateBird();
        this->checkHit();
    }
}

void GameLayer::createPips()
{
    for(int i = 0; i < PIP_COUNT; i++) {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Sprite *pipUp = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameNyName("pipe_up"));
        Sprite *pipDown = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameNyName("pipe_down"));
        Node* singlePip = Node::create();
        
        // bind to pair
        pipDown->setPosition(0, PIP_HEIGHT + PIP_DISTANCE);
        singlePip->addChild(pipDown, 0, DOWN_PIP);
        singlePip->addChild(pipUp, 0, UP_PIP);
        singlePip->setPosition(visibleSize.width + i * PIP_INTERVAL + WAIT_DISTANCE, this->getRandomHeight());
        auto body = PhysicsBody::create();
        auto shapeBoxDown = PhysicsShapeBox::create(pipDown->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT, Point(0, PIP_HEIGHT + PIP_DISTANCE));
        body->addShape(shapeBoxDown);
        body->addShape(PhysicsShapeBox::create(pipUp->getContentSize()));
        body->setDynamic(false);
        singlePip->setPhysicsBody(body);
        singlePip->setTag(PIP_NEW);
        
        this->addChild(singlePip);
        this->pips.pushBack(singlePip);
    }
}

int GameLayer::getRandomHeight()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    return rand() % (int)(2 * PIP_HEIGHT + PIP_DISTANCE - visibleSize.height);
}

void GameLayer::checkHit()
{
    for(auto pip : this->pips) {
        if(pip->getTag() == PIP_NEW) {
            if(pip->getPositionX() < bird->getPositionX()) {
                SimpleAudioEngine::getInstance()->playEffect("sfx_point.ogg");
                this->score ++;
                this->delegator->onGamePlaying(this->score);
                pip->setTag(PIP_PASS);
            }
        }
    }
}

void GameLayer::gameOver()
{
    if(this->gameStatus == GAME_STATUS_OVER) {
        return;
    }
    
    SimpleAudioEngine::getInstance()->playEffect("sfx_hit.ogg");
    
    
    this->unschedule(shiftLand);
    SimpleAudioEngine::getInstance()->playEffect("sfx_die.ogg");
    this->bird->die();
    this->bird->setRotation(-90);
    this->birdSpriteFadeOut();
    gameStatus = GAME_STATUS_OVER;
    
}

void GameLayer::birdSpriteFadeOut()
{
    FadeOut* animation = FadeOut::create(1.5f);
    CallFunc* animationDone = CallFunc::create(bind(&GameLayer::birdSpriteRemove, this));
    Sequence* sequence = Sequence::createWithTwoActions(animation, animationDone);
    bird->stopAllActions();
    bird->runAction(sequence);
}

void GameLayer::birdSpriteRemove()
{
    bird->setRotation(0);
    this->removeChild(bird);
}