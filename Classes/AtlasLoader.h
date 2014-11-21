//
//  AtlasLoader.h
//  FlappyBirdCpp
//
//  Created by 林光海 on 14-11-21.
//
//

#ifndef __FlappyBirdCpp__AtlasLoader__
#define __FlappyBirdCpp__AtlasLoader__

#include "cocos2d.h"
#include <string>
using namespace cocos2d;
using namespace std;

typedef struct _atlas {
    char name[255];
    int width;
    int height;
    Point start;
    Point end;
}Atlas;

class AtlasLoader {
public:
    static AtlasLoader* getInstance();
    
    static void destroyInstance();
    
    void loadAtlas(string filename);
    
    void loadAtlas(string filename, Texture2D *texture);
    
    SpriteFrame* getSpriteFrameNyName(string name);
protected:
    AtlasLoader();
    
    virtual bool init();
    
    static AtlasLoader* sharedAtlasLoader;
    
    Map<string, SpriteFrame*> _spriteFrames;
};

#endif /* defined(__FlappyBirdCpp__AtlasLoader__) */
