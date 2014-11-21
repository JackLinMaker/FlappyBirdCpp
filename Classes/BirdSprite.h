//
//  BirdSprite.h
//  FlappyBirdCpp
//
//  Created by 林光海 on 14-11-21.
//
//

#ifndef __FlappyBirdCpp__BirdSprite__
#define __FlappyBirdCpp__BirdSprite__

#include "cocos2d.h"
#include "AtlasLoader.h"
using namespace cocos2d;

typedef enum {
    ACTION_STATE_IDLE,
    ACTION_STATE_FLY,
    ACTION_STATE_DIE
}ActionState;

const int BIRD_SPRITE_TAG = 10003;

class BirdSprite : public Sprite {
public:
    BirdSprite();
    
    ~BirdSprite();
    
    static BirdSprite* getInstance();
    
    virtual bool init();
    
    bool createBird();
    
    void idle();
    
    void fly();
    
    void die();
protected:
    /**
     * This method can create a frame animation with the likey name texture.
     */
    static Animation* createAnimation(const char *fmt, int count, float fps);
    /**
	 * Since this game has three different types of bird
	 * this method is just used for choosing which type of bird by random
	 */
    void createBirdByRandom();
private:
    static BirdSprite* sharedBirdSprite;
    
    bool changeState(ActionState state);
    
    Action* idleAction;
    
    Action* swingAction;
    
    ActionState currentState;
    
    string birdName;
    
    string birdNameFormat;
    
    unsigned int isFirstTime;
};

#endif /* defined(__FlappyBirdCpp__BirdSprite__) */
