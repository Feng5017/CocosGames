#include "SimpleAudioEngine.h"
#include "ManagerBase.h"

USING_NS_CC;
#include "cocos2d.h"

ManagerBase* ManagerBase::manager = NULL;//初始化参数

ManagerBase::ManagerBase() {}
ManagerBase::~ManagerBase() {}

ManagerBase * ManagerBase::getInstance()
{
	if (manager==NULL){
		manager = new ManagerBase();
	}
	return manager;
}

void ManagerBase::deleteInstance()
{
	if (manager){
		delete manager;
		manager = NULL;
	}
}

void ManagerBase::set_enemy_list(EnemyBase * enemy){
	enemy_list_.pushBack(enemy);
}

void ManagerBase::set_bullet_list(Bullet * bullet){
	bullet_list_.pushBack(bullet);
}

void ManagerBase::remove_enemy_list(EnemyBase * enemy){
	enemy_list_.eraseObject(enemy);
}

void ManagerBase::remove_bullet_list(Bullet * bullet){
	bullet_list_.eraseObject(bullet);
}

void ManagerBase::set_plane_support_list(PlaneSupport * planesupport)
{
	planesupport_list_.pushBack(planesupport);
}

void ManagerBase::remove_plane_support_list(PlaneSupport * planesupport)
{
	planesupport_list_.eraseObject(planesupport);
}
