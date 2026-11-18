#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
//生命周期函数
    virtual bool init();//初始化场景调用
	virtual void onEnter();//进入场景时调用
	virtual void onEnterTransitionDidFinish();//进入场景且过渡动画结束时调用
	virtual void onExit();//退出场景时调用
	virtual void onExitTransitionDidStart();//退出场景且过渡动画结束时调用
	virtual void cleanup();//场景对象被清除时使用

    // a selector callback
	void menuGoCallback(cocos2d::Ref* pSender);
	void menuStartCallback(cocos2d::Ref* pSender);
	void menuSettingCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
