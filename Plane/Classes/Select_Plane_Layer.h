#ifndef __SELECT_PLANE_LAYER_H__
#define __SELECT_PLANE_LAYER_H__

#include<iostream>
#include "cocos2d.h"

using namespace cocos2d;

USING_NS_CC;

class SelectPlaneLayer :public cocos2d::Layer
{
private:
	int page_node;		//几个飞机
	int cur_page_node;  //当前页面
	Point touch_down_point; //点击时为止
	Point touch_up_point;   //拾起时为止
	Point touch_cur_point;
	float size_x, size_y;
public:
	SelectPlaneLayer();
	~SelectPlaneLayer();
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void goToCurrNode();
	void addNode(Node *level);

	bool onTouchBegan(Touch* touch, Event* unused_event);
	void onTouchMoved(Touch* touch, Event* unused_event);
	void onTouchEnded(Touch* touch, Event* unused_event);

	CREATE_FUNC(SelectPlaneLayer);
};


#endif 
