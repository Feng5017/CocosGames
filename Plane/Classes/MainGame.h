#ifndef __MainGame_SCENE_H__
#define __MainGame_SCENE_H__
#include "PlaneSupport.h"
#include "cocos2d.h"
using namespace std;
using namespace cocos2d;

class PlaneSupport;
class MainGame : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

//声明全局变量精灵类一定要加using namespace cocos2d头文件
	//背景
	Sprite* spr_bg1;
	Sprite* spr_bg2;	
	//按钮回调：
	//void menuCloseCallback(cocos2d::Ref* pSender);
	virtual void update(float delta);//update为scheduleUpdate定时器的刷新函数体，调用定时器时自动触发

//单击触摸方法：绑定触摸监听
	bool onTouchBegan(Touch *touch, Event* unused_event);
	void onTouchMoved(Touch *touch, Event* unused_event);
	//初始化玩家飞机
	int plane_type;
	void init_hero_plane(int index);//参数用于玩家选择飞机
	//玩家飞机
	Sprite* hero_player;
//添加敌机
	void add_enemy(float delta);
//添加子弹
	void add_bullet(float delta);
//碰撞检测
	void is_crash(float tm);
//主角死亡
	void hero_death();
	void hero_player_action_end();

//添加物资
	void add_support(float tm);
	void add_support_bullet(float tm);//获得物资后的子弹效果
	PlaneSupport* plane_support;//支援物资
	int support_index;//支援的物资类型
//暂停
	void suspend(cocos2d::Ref* pSender);
//分数
	int score;//当前分数
	Label* label_score_num;
	Label* label_best_score_num;

	void onEnterTransitionDidFinish();
	void onExit();
	// implement the "static create()" method manually
	CREATE_FUNC(MainGame);
};

#endif // __HELLOWORLD_SCENE_H__
