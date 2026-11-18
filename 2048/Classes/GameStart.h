#ifndef __GAMESTART_SCENE_H__
#define __GAMESTART_SCENE_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

class GameStart : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	
	virtual void menuCallback(cocos2d::Ref* pSender);
	virtual void rescoreCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(GameStart);
};

#endif // __HELLOWORLD_SCENE_H__

