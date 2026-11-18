#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	//按钮回调：
	void start_play(cocos2d::Ref* pSender);

	void menuMusicToggleCallback(Ref* pSender);  //音乐开关
	void menuMusicEffectCallback(Ref* pSender);  //音效开关
	bool  isopen;//音乐开关

	void menuCloseCallback(cocos2d::Ref* pSender);
	
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__