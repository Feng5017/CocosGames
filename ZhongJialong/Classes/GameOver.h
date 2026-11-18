#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d;

class GameOver :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menu_play(cocos2d::Ref* pSender);

	CREATE_FUNC(GameOver);
};

#endif 
#pragma once
