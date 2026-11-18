#ifndef __PLANE_SUPPORT_H__
#define __PLANE_SUPPORT_H__
#include "cocos2d.h"

USING_NS_CC;

class PlaneSupport :public cocos2d::Sprite
{
public:
	PlaneSupport();
	~PlaneSupport();
public:
	virtual bool init();
	CREATE_FUNC(PlaneSupport);

	int sup_index;
public:
	//初始化
	void init_support(int index);//根据不同参数创建不同资源

};

#endif 
#pragma once
