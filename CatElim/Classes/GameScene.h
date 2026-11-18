#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "SimpleAudioEngine.h"
#include "Stage.h"
using namespace CocosDenshion;
#include "cocos2d.h"
USING_NS_CC;
class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void toExit();  //退出界面
	bool onTouchStart(Touch *touch, Event *event);    //鼠标触发事件
	void onTouchMove(Touch *touch, Event *event);
	void onTouchEnd(Touch *touch, Event *event);
	bool ifOnTouchMove;	

	void update(float dt);
	void toGameOver(float dt);
	CREATE_FUNC(GameScene);
	
	static int touchflag;
	Stage *stage;
	int x1, y1, x2, y2; //图片坐标
};

#endif // __HELLOWORLD_SCENE_H__
