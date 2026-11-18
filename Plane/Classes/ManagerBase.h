#ifndef __Manager_Base__
#define __Manager_Base__

#include "cocos2d.h"
#include "EnemyBase.h"
#include "Bullet.h"
#include "PlaneSupport.h"
USING_NS_CC;
using namespace std;
using namespace cocos2d;

class ManagerBase 
{
public:
	ManagerBase();
	~ManagerBase();
public:
	//创建
	static ManagerBase* getInstance();
	//删除
	static void deleteInstance();
private:
	static ManagerBase* manager;

public:
//管理子弹
	Vector<EnemyBase*>enemy_list_;
	Vector<Bullet*>bullet_list_;
	Vector<PlaneSupport*>planesupport_list_;
	Vector<EnemyBase*>&getEnemyList() { return enemy_list_; }
	Vector<Bullet*>&getBulletList() { return bullet_list_; }
	Vector<PlaneSupport*>&getPlaneSupportList() { return planesupport_list_; }
	//添加敌机
	void set_enemy_list(EnemyBase* enemy);
	//添加子弹
	void set_bullet_list(Bullet* bullet);
	//删除敌机
	void remove_enemy_list(EnemyBase* enemy);
	//删除子弹
	void remove_bullet_list(Bullet* bullet);

	void set_plane_support_list(PlaneSupport* planesupport);
	void remove_plane_support_list(PlaneSupport* planesupport);

};

#endif 
#pragma once
