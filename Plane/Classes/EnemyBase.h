#ifndef __Enemy_BASE_H__
#define __Enemy_BASE_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d;

class EnemyBase : public cocos2d::Sprite //敌机的类继承于精灵
{
public:
	EnemyBase();
	~EnemyBase();
public:
	virtual bool init();
//敌机的初始化
	int enemy_index;//敌机类型
	int enemy_hp;//敌机血量
	bool is_death;//是否爆炸
	
	void init_enemy(int index);//初始化敌机
	void enemy_death();//爆炸动画
//删除自己
	void remove_enemy();
//敌机血量
	void set_hp(int hp);
	int get_hp() { return enemy_hp; }

	virtual void update(float delta);
	void onEnterTransitionDidFinish();
	void onExit();

	CREATE_FUNC(EnemyBase);
};

#endif 
#pragma once
