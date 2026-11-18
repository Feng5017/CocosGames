#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d;

#include "ContactListener.h"

typedef enum{	//…Ë÷√±Í«©
	ARRAY_TAG = 10,
	VECTOR_TAG,
	DICT_TAG,
	MAP_TAG,
	VALUE_TAG,
	VALUEMAP_TAG
}RefTag;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	
	virtual void menuCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
