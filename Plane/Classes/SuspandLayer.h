#ifndef __SUSPAND_LAYER_H__
#define __SUSPAND_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d;

class SuspandLayer :public cocos2d::Layer
{
public:
	SuspandLayer();
	~SuspandLayer();
public:
	virtual bool init();
	void back_game(cocos2d::Ref* pSender);
	CREATE_FUNC(SuspandLayer);
};

#endif 
#pragma once
