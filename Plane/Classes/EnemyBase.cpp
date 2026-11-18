#include "SimpleAudioEngine.h"

#include "EnemyBase.h"
#include "ManagerBase.h"
USING_NS_CC;
#include "cocos2d.h"

EnemyBase::EnemyBase(){}
EnemyBase::~EnemyBase(){}

bool EnemyBase::init()
{
	is_death = false;//初始化参数
	if (!Sprite::init())
		return false;
	else
		return true;
}

void EnemyBase::onEnterTransitionDidFinish() {
	Sprite::onEnterTransitionDidFinish();
	scheduleUpdate();//刷新屏幕
}
void EnemyBase::onExit() {
	scheduleUpdate();
	Sprite::onExit();
}

void EnemyBase::init_enemy(int name_index)
{
	//初始化敌机血量，不同敌机实现不同血量
	enemy_hp = name_index;
	//初始化敌机
	auto name_str = String::createWithFormat("plane/enemy%d.png", name_index);
	//添加敌机图片
	this->initWithFile(name_str->getCString());

	//获取屏幕大小
	Size visiblesize = Director::getInstance()->getWinSize();
	float x = CCRANDOM_0_1()*(visiblesize.width - 2 * this->getContentSize().width) + this->getContentSize().width / 2;
	float y = visiblesize.height + this->getContentSize().height / 2;
	Point pos = ccp(x, y);
	this->setPosition(pos);
}

void EnemyBase::enemy_death()
{	
	is_death = true;
	//爆炸动画
	auto animation = Animation::create();
	for (int i = 1; i <= 4; i++)
	{
		auto enemy_name = String::createWithFormat("plane/b%d.png", i);
		animation->addSpriteFrameWithFile(enemy_name->getCString());
	}
	animation->setDelayPerUnit(0.2f);//每一帧播放时间
	animation->setLoops(1);
	//播放完毕时用remove方法
	this->runAction(Sequence::create(Animate::create(animation),RemoveSelf::create(),
		CallFunc::create(CC_CALLBACK_0(EnemyBase::remove_enemy, this)),NULL)); 
}

void EnemyBase::update(float delta)
{
	//如果爆炸则不移动
	if (is_death)
		return;//中断移动函数

	//实现敌机的运动
	auto point = this->getPositionY() - 5;
	this->setPositionY(point);
	//如果移动出了屏幕则从父节点中移除
	if (point < this->getContentSize().height)
	{
		this->removeFromParentAndCleanup(true);
		//移出屏幕时也用remove方法
		remove_enemy();
	}
}

void EnemyBase::remove_enemy()//调用管理器
{
	ManagerBase::getInstance()->remove_enemy_list(this);
}

void EnemyBase::set_hp(int hp)
{
	enemy_hp = hp;
}
