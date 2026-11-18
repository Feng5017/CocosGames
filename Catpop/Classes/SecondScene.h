#ifndef __SECOND_SCENE_H__
#define __SECOND_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class Second : public cocos2d::Scene
{
	cocos2d::Sprite* pict;
	cocos2d::NodeGrid* gridNodeTarget;//新加一个节点
	
public:
    static cocos2d::Scene* createScene();

	int flag;//public法的参数，设置标识，由HelloWorld主动访问Second场景
	virtual bool init();
 	virtual void onEnter();
	
/*	帧动画声明
	bool isPlaying;//播放停止选择
	void OnAction(cocos2d::Ref* pSender);
	组合动画声明
	void OnSequence(cocos2d::Ref* pSender);
	void OnSpawn(cocos2d::Ref* pSender);
	void OnRepeat(cocos2d::Ref* pSender);
	void OnRepeatForever(cocos2d::Ref* pSender);
	void OnReverse(cocos2d::Ref* pSender);
	函数调用声明
	void OnCallFunc(cocos2d::Ref* pSender);
	void OnCallFuncN(cocos2d::Ref* pSender);
	void CallBack1();//无参函数
	void CallBack2(cocos2d::Ref* pSender);//有参函数*/	
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menugoCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(Second);
};

#endif 
