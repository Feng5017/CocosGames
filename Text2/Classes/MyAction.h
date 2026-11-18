#ifndef __MyAction_SCENE_H__//活动预处理
#define __MyAction_SCENE_H__

#include "HelloWorldScene.h"
#include "cocos2d.h"
USING_NS_CC;
class MyAction : public cocos2d::Scene
{
public:
	Label* pb;//设置层对象为公有变量
	Sprite* background;//设置背景精灵对象为公有变量
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onEnterTransitionDidFinish();

	void menuCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(MyAction);
};
#endif // __Setting_SCENE_H__
