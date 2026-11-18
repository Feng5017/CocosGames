#pragma warning(disable:4996)
#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include "cocos2d.h"
USING_NS_CC;
class GameOver : public cocos2d::Scene
{
private:
	int bestScore;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void toSelect();
	CREATE_FUNC(GameOver);
};

#endif // __HELLOWORLD_SCENE_H__

