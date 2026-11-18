#ifndef __SELECT_PLANE_PAGE_H__
#define __SELECT_PLANE_PAGE_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d;

class SelectPlanePage :public cocos2d::Node
{	//继承的是Node类
public:
	//初始化飞机选择界面
	bool initLevelPage(int Page);
	static SelectPlanePage* create(int page);
	void menuStartCallBack(Ref* pSender);
public:
	int page_;
	
	CREATE_FUNC(SelectPlanePage);
};

#endif 

