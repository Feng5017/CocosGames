#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include "cocos2d.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void toSelect();
	void toExit();
	void menuMusicToggleCallback(Ref* pSender);  //音乐开关
	void menuMusicEffectCallback(Ref* pSender);  //音效开关
	
	bool  isopen;//音乐开关
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
