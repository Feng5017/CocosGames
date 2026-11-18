#ifndef __Bullet_H__
#define __Bullet_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d;

class Bullet :public cocos2d::Sprite
{
public:
	Bullet();
	~Bullet();
public:
	virtual bool init();

	void update(float delta);
	void onEnterTransitionDidFinish();
	void onExit();
	void initBullet(char* bullet_name);//³õÊ¼»¯×Óµ¯

	CREATE_FUNC(Bullet);
};

#endif 
#pragma once
