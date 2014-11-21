//
//  BackgroundLayer.h
//  FlappyBirdCpp
//
//  Created by 林光海 on 14-11-21.
//
//

#ifndef __FlappyBirdCpp__BackgroundLayer__
#define __FlappyBirdCpp__BackgroundLayer__

#include "cocos2d.h"
#include "AtlasLoader.h"
#include "time.h"

using namespace cocos2d;
using namespace std;

class BackgroundLayer : public Layer {
public:
    BackgroundLayer(void);
    
    ~BackgroundLayer(void);
    
    virtual bool init();
    
    CREATE_FUNC(BackgroundLayer);
    
    static float getLandHeight();
};

#endif /* defined(__FlappyBirdCpp__BackgroundLayer__) */
