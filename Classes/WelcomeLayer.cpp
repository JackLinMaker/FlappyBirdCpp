//
//  WelcomeLayer.cpp
//  FlappyBirdCpp
//
//  Created by 林光海 on 14-11-21.
//
//

#include "WelcomeLayer.h"
#include "AtlasLoader.h"

WelcomeLayer::WelcomeLayer()
{

}

WelcomeLayer::~WelcomeLayer()
{
    
}

bool WelcomeLayer::init()
{
    if(!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    time_t t = time(NULL);
    tm* lt = localtime(&t);
    int hour = lt->tm_hour;
    
    Sprite* background;
    if(hour >= 6 && hour <= 17) {
        background = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameNyName("bg_day"));
    }else {
        background = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameNyName("bg_day"));
    }
    background->setAnchorPoint(Point::ZERO);
    background->setPosition(Point::ZERO);
    this->addChild(background);
    
    // add the word game-title to the curent scene
    Sprite* title = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameNyName("title"));
    title->setPosition(Point(origin.x + visibleSize.width / 2, (visibleSize.height * 5) / 7));
    this->addChild(title);
    
    // add the start-menu to the current scene
    Sprite* startButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameNyName("button_play"));
    Sprite* activeStartButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameNyName("button_play"));
    activeStartButton->setPositionY(5);
    
    auto menuItem = MenuItemSprite::create(startButton, activeStartButton, NULL, CC_CALLBACK_1(WelcomeLayer::menuStartCallback, this));
    menuItem->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    
    auto menu = Menu::create(menuItem, NULL);
    menu->setPosition(Point(origin.x, origin.y));
    this->addChild(menu, 1);
    
    
    //create a bird and set the position in the center of the screen
    bird = BirdSprite::getInstance();
	bird->createBird();
	bird->setTag(BIRD_SPRITE_TAG);
	bird->setPosition(Point(origin.x + visibleSize.width / 2,origin.y + visibleSize.height*3/5 - 10));
	bird->idle();
	this->addChild(bird);

    
    
    // Add the land
    land1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameNyName("land"));
    land1->setAnchorPoint(Point::ZERO);
    land1->setPosition(Point::ZERO);
    this->addChild(land1);
    
    land2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameNyName("land"));
    land2->setAnchorPoint(Point::ZERO);
    land2->setPosition(Point(this->land1->getContentSize().width - 2.0f, 0));
    this->addChild(land2);
    
    this->schedule(schedule_selector(WelcomeLayer::scrollLand), 0.01f);
    
	//add the copyright-text to the current scne
	Sprite *copyright = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameNyName("brand_copyright"));
	copyright->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height/6));
	this->addChild(copyright, 10);

    
    return true;
}

void WelcomeLayer::scrollLand(float dt)
{
    this->land1->setPositionX(land1->getPositionX() - 2.0f);
    this->land2->setPositionX(land1->getPositionX() + this->land1->getContentSize().width - 2.0f);
    
    if(this->land2->getPositionX() == 0) {
        this->land1->setPositionX(0);
    }
}

void WelcomeLayer::menuStartCallback(cocos2d::Ref *sender)
{
    SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	this->removeChildByTag(BIRD_SPRITE_TAG);
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);

}