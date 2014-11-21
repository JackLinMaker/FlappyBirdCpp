//
//  GameLayer.h
//  FlappyBirdCpp
//
//  Created by 林光海 on 14-11-21.
//
//

#ifndef __FlappyBirdCpp__GameLayer__
#define __FlappyBirdCpp__GameLayer__

#include "cocos2d.h"
#include "OptionLayer.h"
#include "BirdSprite.h"
#include "BackgroundLayer.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"
#include <cstdlib>

using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;

#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))

const int UP_PIP = 21;

const int DOWN_PIP = 12;

const int PIP_PASS = 30;

const int PIP_NEW = 31;

/* The radius of the bird */
const int BIRD_RADIUS = 15;

/* The height of the pips */
const int PIP_HEIGHT = 320;

/* The width of the pips */
const int PIP_WIDTH = 52;

/* Pip shift speed */
const float PIP_SHIFT_SPEED = 80.0f;

/* The distance between the down pip and up pip */
const int PIP_DISTANCE = 100;

/* The distance between the pips vertical */
const int PIP_INTERVAL = 180;

/* The number of pip pairs display in the screen in the same time */
const int PIP_COUNT = 2;

/* The distance that the pip will display in the screen, for player to ready */
const int WAIT_DISTANCE = 100;

typedef enum _game_status {
    GAME_STATUS_READY = 1,
    GAME_STATUS_START,
    GAME_STATUS_OVER
}GameStatus;

class StatusDelegate {
public:
    /**
     * When the game start, this method will be called
     */
    virtual void onGameStart(void) = 0;
    /**
     * During paying, after the score changed, this method will be called
     */
    virtual void onGamePlaying(int score) = 0;
    /**
     * When game is over, this method will be called
     */
    virtual void onGameEnd(int curScore, int bestScore) = 0;
};

class GameLayer : public Layer, public OptionDelegate {
public:
    GameLayer();
    
    ~GameLayer();
    
    virtual bool init();
    
    CREATE_FUNC(GameLayer);
    
    CC_SYNTHESIZE(StatusDelegate*, delegator, Delegator);
    
    void onTouch();
    
    void setPhyWorld(PhysicsWorld* world) { this->world = world; }
    
    void update(float delta);
private:
    /**
     * Set the rotate for the bird,let it looks like the head is very heavy.
     */
    void rotateBird();
    /**
     * create new pips and make it move from left to right then remove from parent
     */
    void createPips();
    
    int getRandomHeight();
    
    void checkHit();
    /**
	 * Since the only global bird can not be addChilded to two layers
	 * we must delete it from one layer,and then add it to another layer
	 * Here we use the fadeout animation to delete it from the gamelayer, so when the player
	 * press the restart button, the bird can be added successfully
	 */
    void birdSpriteFadeOut();
    /*
	 * After running the fadeout animation, delete the bird from current layer
	 */
    void birdSpriteRemove();
    
    PhysicsWorld *world;
    
    GameStatus gameStatus;
    
    int score;
    
    BirdSprite *bird;
    
    Node* groundNode;
    
    Vector<Node *> pips;
    
    Sprite* landSprite1, *landSprite2;
    
    SEL_SCHEDULE shiftLand;
    
    void scrollLand(float dt);
    
    bool onContactBegin(EventCustom *event, const PhysicsContact& contact);
    
    void gameOver();
};


#endif /* defined(__FlappyBirdCpp__GameLayer__) */
