#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    CREATE_FUNC(HelloWorld);
    
    HelloWorld();
    
    virtual bool init();
    
    virtual ~HelloWorld();
};

#endif // __HELLOWORLD_SCENE_H__
