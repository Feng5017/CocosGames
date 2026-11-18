#include "SimpleAudioEngine.h"

#include "HelloWorldScene.h"
#include "MainGame.h"
#include "EnemyBase.h"
#include "Bullet.h"
#include "ManagerBase.h"
#include "PlaneSupport.h"
#include "SuspandLayer.h"
#include "GameOver.h"
#include "Select_Plane_Scene.h"
#include "Select_Plane_Layer.h"
#include "Select_Plane_Page.h"
USING_NS_CC;
#include "cocos2d.h"

Scene* MainGame::createScene()
{
	return MainGame::create();
}

bool MainGame::init()
{
	plane_support = NULL;
	score = 0;
	if (!Scene::init())	{
		return false;
	}
	auto visiblesize = Director::getInstance()->getWinSize();
//背景滚动
	//背景1
	spr_bg1 = Sprite::create("ui/bgs.png");
	spr_bg1->setAnchorPoint(Vec2(0, 0));
	spr_bg1->setPosition(Vec2(0, 0));
	this->addChild(spr_bg1);
	//背景2
	spr_bg2 = Sprite::create("ui/bgs.png");
	spr_bg2->setAnchorPoint(Vec2(0, 0));
	spr_bg2->setPosition(Vec2(0, spr_bg1->getContentSize().height - 2));
	this->addChild(spr_bg2);

	//初始化飞机
	//init_hero_plane(1);

/*添加暂停*/
	//添加menu
	auto dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");
	auto btn_label = Label::create();
	btn_label->setString(((__String*)(dictionary->objectForKey("suspend")))->getCString());
	btn_label->setSystemFontSize(30);
	auto start_menu = MenuItemLabel::create(btn_label, CC_CALLBACK_1(MainGame::suspend, this));

	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(ccp(visiblesize.width - btn_label->getContentSize().width / 2 - 5,
		visiblesize.height - btn_label->getContentSize().height / 2 - 5));
	this->addChild(menu);

/*设置分数*/
	//分数设置
	auto label_score = Label::create();
	label_score->setString(((__String*)(dictionary->objectForKey("score")))->getCString());
	label_score->setSystemFontSize(40);
	label_score->setAnchorPoint(ccp(0.5, 0.5));
	label_score->setPosition(ccp(label_score->getContentSize().width / 2 + 5,
		visiblesize.height - label_score->getContentSize().height / 2));
	this->addChild(label_score);
	
	label_score_num = Label::create();
	label_score_num->setSystemFontSize(30);
	label_score_num->setAnchorPoint(ccp(0, 0.5));
	label_score_num->setPosition(ccp(label_score->getContentSize().width + 5,
		visiblesize.height - label_score->getContentSize().height / 2));
	this->addChild(label_score_num);
	//最高分
	auto label_best_score = Label::create();
	label_best_score->setString(((__String*)(dictionary->objectForKey("best_score")))->getCString());
	label_best_score->setSystemFontSize(40);
	label_best_score->setAnchorPoint(ccp(0.5, 0.5));
	label_best_score->setPosition(ccp(label_best_score->getContentSize().width / 2 + 5,
		visiblesize.height - label_best_score->getContentSize().height / 2 - 40));
	this->addChild(label_best_score);

	label_best_score_num = Label::create();
	label_best_score_num->setSystemFontSize(30);
	label_best_score_num->setAnchorPoint(ccp(0, 0.5));
	label_best_score_num->setPosition(ccp(label_best_score->getContentSize().width + 5,
		visiblesize.height - label_best_score->getContentSize().height / 2 - 40));
	this->addChild(label_best_score_num);
	//存储最高分
	int score_win = UserDefault::getInstance()->getIntegerForKey("best_score");
	label_best_score_num->setString(String::createWithFormat("%d", score_win)->getCString());
	//赋值当前分
	label_score_num->setString(String::createWithFormat("%d", score)->getCString());


//单点触摸的监听器
	EventListenerTouchOneByOne* m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->onTouchBegan = CC_CALLBACK_2(MainGame::onTouchBegan, this);
	m_touchListener->onTouchMoved = CC_CALLBACK_2(MainGame::onTouchMoved, this);
	//设置吞噬触摸
	m_touchListener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(m_touchListener,this);

	return true;
}

void MainGame::update(float delta)//调用定时器时自动触发
{
//实现背景滚动
	float y1 = spr_bg1->getPositionY() - 3;
	float y2 = spr_bg2->getPositionY() - 3;
	spr_bg1->setPositionY(y1);
	spr_bg2->setPositionY(y2);
//判断背景是否超出背景边界，如果超出边界，则重置背景图片Y坐标
	if (y1 < -spr_bg1->getContentSize().height){
		spr_bg1->setPositionY(spr_bg2->getPositionY() + spr_bg2->getContentSize().height - 2);
	}
	else if (y2 < -spr_bg1->getContentSize().height){
		spr_bg2->setPositionY(spr_bg1->getPositionY() + spr_bg1->getContentSize().height - 2);
	}
}

bool MainGame::onTouchBegan(Touch *touch, Event* unused_event)
{
	//判断点击区域是否在飞机上
	auto point = touch->getLocation();
	auto rect = hero_player->getBoundingBox();
	if (rect.containsPoint(point))
		return true;
	else
		return false;
}

void MainGame::onTouchMoved(Touch *touch, Event* unused_event)
{
//获取飞机移动距离
	auto add_point = touch->getLocation() - touch->getPreviousLocation();//获取上一节点的位置
	hero_player->setPosition(hero_player->getPosition() + add_point);//飞机移动的距离
//判断飞机移动的范围，不要超出边界
	auto visiblesize = Director::getInstance()->getWinSize();
	auto hero_size = hero_player->getContentSize();
//x的方向
	if (hero_player->getPositionX() < hero_size.width / 2){
		hero_player->setPositionX(hero_size.width / 2);
	}
	else if (hero_player->getPositionX() > visiblesize.width - hero_size.width / 2){
		hero_player->setPositionX(visiblesize.width - hero_size.width / 2);
	}
//Y方向
	if (hero_player->getPositionY() < hero_size.height / 2){
		hero_player->setPositionY(hero_size.height / 2);
	}
	else if (hero_player->getPositionY() > visiblesize.height - hero_size.height / 2){
		hero_player->setPositionY(visiblesize.height - hero_size.height / 2);
	}

}

void MainGame::onEnterTransitionDidFinish() {//进入层且过度动画结束时调用
	Scene::onEnterTransitionDidFinish();
	//log("MainGame: onEnterTransitionDidFinish");
	
	scheduleUpdate();//核心：定时器函数，每隔一定时间刷新一次
	//敌机
	this->schedule(SEL_SCHEDULE(&MainGame::add_enemy), 0.3f);
	//子弹
	this->schedule(SEL_SCHEDULE(&MainGame::add_bullet), 0.09f);
	//碰撞检测
	this->schedule(SEL_SCHEDULE(&MainGame::is_crash));	
	//物资
	this->schedule(SEL_SCHEDULE(&MainGame::add_support), 3.0f);
}

void MainGame::onExit() {	//退出层时调用
	//log("MainGame: onExit");	
	unscheduleUpdate();//每帧调用update
	Scene::onExit();	
}

void MainGame::init_hero_plane(int index)//参数用于玩家选择飞机
{
	//记录选择的飞机类型
	plane_type = index;

	auto animation = Animation::create();
	for (int i = 0; i < 2; i++)
	{
		auto str_name = String::createWithFormat("plane/heros%d_%d.png", plane_type, i + 1);
		animation->addSpriteFrameWithFile(str_name->getCString());
	}
	animation->setDelayPerUnit(0.5);
	animation->setLoops(-1);
	//创建飞机精灵
	hero_player = Sprite::create(String::createWithFormat("plane/heros%d_1.png", plane_type)->getCString());
	auto visiblesize = Director::getInstance()->getWinSize();//设置窗口大小
	hero_player->setPosition(Vec2(visiblesize.width / 2, visiblesize.height*0.2));
	this->addChild(hero_player);
	hero_player->runAction(Animate::create(animation));//播放帧动画
}

void MainGame::add_enemy(float delta)
{
	//添加敌机，根据不同概率添加不同飞机
	int enemy_x = CCRANDOM_0_1() * 9 + 1;
	if (enemy_x > 7) 
		enemy_x = 2;
	else
		enemy_x = 1;

	auto enemy = EnemyBase::create();
	enemy->init_enemy(enemy_x);
	this->addChild(enemy);

	//将敌机放入管理器
	ManagerBase::getInstance()->set_enemy_list(enemy);
}

void MainGame::add_bullet(float delta)
{
	auto bullet = Bullet::create();
	//bullet->initBullet("bullet1.png");

//设置子弹坐标，根据不同类型选择不同子弹
	if (plane_type==2)
		bullet->initBullet("bullet2.png");
	else if (plane_type == 3)
		bullet->initBullet("bullet3.png");
	else
		bullet->initBullet("bullet1.png");

	//log("You choosed Plane%d", plane_type);
	auto point = ccp(hero_player->getPositionX(), 
		hero_player->getPositionY() + hero_player->getContentSize().height / 2 + 10);
	bullet->setPosition(point);
	this->addChild(bullet);

	//将子弹放入管理器
	ManagerBase::getInstance()->set_bullet_list(bullet);
}

void MainGame::is_crash(float tm)
{	//碰撞检测，首先在管理器中获取敌机和子弹的Vector
	auto & enemy_list = ManagerBase::getInstance()->getEnemyList();
	auto & bullet_list = ManagerBase::getInstance()->getBulletList();
	auto & planesupport_list = ManagerBase::getInstance()->getPlaneSupportList();
	//敌机和子弹的碰撞，倒叙遍历，因为要最先判断新添加的敌机
	for (int i = enemy_list.size()-1; i >= 0; --i)	{		
		auto enemy = enemy_list.at(i);//敌机
		if (enemy->get_hp() <= 0)//判断血量是否小于零，若是则不进行下面的逻辑
			continue;
		auto enemy_size = enemy->getBoundingBox();//获取敌机大小
		//子弹遍历
		for (int i = bullet_list.size()-1; i >= 0; --i)	{
			auto bullet = bullet_list.at(i);
			//判断子弹和敌机是否碰撞
			if (enemy_size.containsPoint(bullet->getPosition()))
			{
				enemy->set_hp(enemy->get_hp() - 1);//血量减一
				bullet->removeFromParentAndCleanup(true);//且移除子弹
				ManagerBase::getInstance()->remove_bullet_list(bullet);
				//如果敌机血量为0则播放爆炸			
				if (enemy->get_hp() <= 0){
					enemy->enemy_death();
					score += 10;//爆炸时分数加10
					label_score_num->setString(String::createWithFormat("%d", score)->getCString());
				}
			}
		}
	}

	/*玩家飞机和敌机的碰撞检测*/
	for (auto i = enemy_list.size() - 1; i >= 0; --i)
	{
		auto enemy = enemy_list.at(i);
		if (enemy->get_hp() <= 0)
			continue;//如果已经毁灭则不进行碰撞检测
		auto rect = this->hero_player->getBoundingBox();
		auto point = enemy->getPosition();
		if (rect.containsPoint(point))//判断敌机是否与飞机碰撞
		{
			hero_death();//如果是，则主角死亡
			//enemy->remove_enemy();
			log("I am Died because of Enemy");
		}	
	}

	/*物资和玩家的碰撞检测*/
	//if (plane_support != NULL)
	//{
	//	auto rect = hero_player->getBoundingBox();//飞机大小
	//	//log("%f,%f", rect.size.width,rect.size.height);
	//	auto point = plane_support->getPosition();//物资坐标
	//	//log("%f,%f", point.x, point.y);
	//	//物资是否与玩家飞机碰撞
	//	if (rect.containsPoint(point))
	//	{
	//		this->schedule(SEL_SCHEDULE(&MainGame::add_support_bullet), 0.1f, 50, 0);//50是这个方法调用50次
	//		this->unschedule(SEL_SCHEDULE(&MainGame::add_bullet));//停止普通子弹
	//		//延迟添加执行添加普通子弹的时间
	//		this->schedule(SEL_SCHEDULE(&MainGame::add_bullet), 0.1f, -1, 5.0f);//5.0f这个参数是设置这个方法 延迟多少后被调用
	//		plane_support->setVisible(false);
	//		plane_support = NULL;
	//	}
	//	//移除物资
	//	if (plane_support!=NULL&&point.y<-plane_support->getContentSize().height)
	//	{
	//		plane_support->removeFromParent();
	//		plane_support = NULL;
	//	}
	//}
	for (int i = planesupport_list.size() - 1; i >= 0; i--)
	{
		auto support = planesupport_list.at(i);
		auto rect = hero_player->getBoundingBox();//飞机大小
		auto point = support->getPosition();//物资坐标
		if (rect.containsPoint(point))
		{
			support_index = support->sup_index;//获取物资参数
			this->schedule(SEL_SCHEDULE(&MainGame::add_support_bullet), 0.1f, 50, 0);//50是这个方法调用50次
			this->unschedule(SEL_SCHEDULE(&MainGame::add_bullet));//停止普通子弹
			//延迟添加执行添加普通子弹的时间
			this->schedule(SEL_SCHEDULE(&MainGame::add_bullet), 0.1f, -1, 5.0f);//5.0f这个参数是设置这个方法 延迟多少后被调用

			ManagerBase::getInstance()->remove_plane_support_list(support);
			support->removeFromParent();
		}
		else if (point.y < 0)
			support->removeFromParent();
	 }
}

void MainGame::hero_death()
{//存储分数变量
	UserDefault::getInstance()->setIntegerForKey("score", score);
	//最高分
	int score_win = UserDefault::getInstance()->getIntegerForKey("best_score");
	if (score>score_win)
	{
		UserDefault::getInstance()->setIntegerForKey("best_score", score);
	}
//玩家飞机坠毁
	hero_player->stopAllActions();
	this->unschedule(SEL_SCHEDULE(&MainGame::add_bullet));//停止创建子弹
	this->unschedule(SEL_SCHEDULE(&MainGame::is_crash));//停止碰撞检测
	//this->unschedule(SEL_SCHEDULE(&MainGame::add_enemy));
	//创建坠毁帧动画
	auto animation = Animation::create();
	for (int i = 1; i <= 4; i++)
	{
		auto str_name = String::createWithFormat("plane/b%d.png", i);
		animation->addSpriteFrameWithFile(str_name->getCString());
	}
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(1);
	
	hero_player->runAction(Sequence::create(Animate::create(animation),
		CallFunc::create(CC_CALLBACK_0(MainGame::hero_player_action_end, this)),NULL));
}

void MainGame::hero_player_action_end()
{
	//停止添加飞机
	this->unschedule(SEL_SCHEDULE(&MainGame::add_enemy));
	//调用结束画面
	Director::getInstance()->replaceScene(TransitionFadeTR::create(1, GameOver::createScene()));
}

void MainGame::add_support(float tm)
{
	//初始化物资
	plane_support = PlaneSupport::create();
	//随机出支援物资的类型
	int index = CCRANDOM_0_1() * 2 + 1;
	plane_support->init_support(index);
	
	this->addChild(plane_support);
	plane_support->setTag(index);
	ManagerBase::getInstance()->set_plane_support_list(plane_support);
}

void MainGame::add_support_bullet(float tm)
{
	//吃到物资后的子弹
	auto bullet = Bullet::create();
	if (support_index == 2)
		bullet->initBullet("bullet_suspand2.png");
	else
		bullet->initBullet("bullet_suspand1.png");

	auto point = Point(hero_player->getPositionX(),
		hero_player->getPositionY() + hero_player->getContentSize().height / 2 + 10);
	bullet->setPosition(point);

	this->addChild(bullet);

	//将子弹添加到ManagerBase中
	ManagerBase::getInstance()->set_bullet_list(bullet);
}

void MainGame::suspend(Ref* pSender)
{
	unscheduleUpdate();
	//先把之前不用的纹理删除
	CCTextureCache::getInstance()->removeUnusedTextures();
	auto visiblesize = Director::getInstance()->getWinSize();
	auto texture = RenderTexture::create(visiblesize.width, visiblesize.height);
	texture->begin();//开始截屏
	//渲染
	Director::getInstance()->getRunningScene()->visit();
	texture->end();

	texture->saveToFile("suspand.png", Image::Format::PNG);//将截屏图片进行保存
	//使用schedule在下一帧中调用callback函数
	//截屏时的下一帧
	auto back = [](float dt)
	{
		//切换到暂停界面
		auto scene = Scene::create();
		auto layer = SuspandLayer::create();
		scene->addChild(layer);
		//这里用pushScene
		Director::getInstance()->pushScene(scene);
	};
	//这里创建Layer 是因为移植android时不能调用主线程中界面的下一帧
	auto layer = Layer::create();
	this->addChild(layer);
	auto schedules = layer->getScheduler();
	schedules->schedule(back, layer, 0.0f, 0, 0.0f, false, "screenshot");
}
