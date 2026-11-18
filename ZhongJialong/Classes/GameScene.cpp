#include "GameScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace cocos2d;

#define TAG 1
#define COINS_NUM 13

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();	//场景具有物理引擎
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);//开启物理世界的调试
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
    //return GameScene::create();
}

bool GameScene::init()
{
    if ( !Layer::init() )   {
        return false;
    }
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

//增加节点到物理引擎世界
	//将屏幕边界创建为一个静态物理体/刚体
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 1.0f);
	auto edgeNode = Node::create();//创建一个游戏中的结点
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 96));
	edgeNode->setPhysicsBody(body);//调用物理引擎
	this->addChild(edgeNode);
//添加背景
	auto spr_bg = Sprite::create("bg.png");
	spr_bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(spr_bg);
//添加循环播放层
	tileMap1 = TMXTiledMap::create("TiledMap.tmx");
	tileMap2 = TMXTiledMap::create("TiledMap.tmx");
	tileMap2->setPosition(Point(tileMap1->getContentSize().width -20, 
		tileMap1->getPosition().y));
	this->addChild(tileMap1);
	this->addChild(tileMap2);
/*文字声明*/
/*通过载入text.xml的中文，防止乱码*/
	Dictionary *dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");
	//分数设置
	hp = 300;
	score = 0;
	auto label_score = Label::create();
	label_score->setString(((__String*)(dictionary->objectForKey("score")))->getCString());
	label_score->setColor(Color3B::ORANGE);
	label_score->setSystemFontSize(40);
	label_score->setAnchorPoint(Vec2(0.5, 0.5));
	label_score->setPosition(Vec2(label_score->getContentSize().width / 2 + 5, visibleSize.height - label_score->getContentSize().height / 2 - 5));
	this->addChild(label_score);
	label_score_num_ = Label::create();
	label_score_num_->setColor(Color3B::ORANGE);
	label_score_num_->setSystemFontSize(30);
	label_score_num_->setAnchorPoint(Vec2(0, 0.5));
	label_score_num_->setPosition(ccp(label_score->getContentSize().width + 5, label_score->getPositionY()));
	label_score_num_->setString(String::createWithFormat("%d", score)->getCString());
	this->addChild(label_score_num_);
	//血量设置
	auto label_blood = Label::create();
	label_blood->setString(((__String*)(dictionary->objectForKey("blood")))->getCString());
	label_blood->setColor(Color3B::RED);
	label_blood->setSystemFontSize(40);
	label_blood->setAnchorPoint(Vec2(0.5, 0.5));
	label_blood->setPosition(Vec2(label_blood->getContentSize().width / 2 + 5, visibleSize.height - label_blood->getContentSize().height * 3 / 2 - 5));
	this->addChild(label_blood);

	label_blood_num = Label::create();
	label_blood_num->setColor(Color3B::RED);
	label_blood_num->setSystemFontSize(30);
	label_blood_num->setAnchorPoint(ccp(0, 0.5));
	label_blood_num->setPosition(Vec2(label_blood->getContentSize().width + 5, label_blood->getPositionY()));
	label_blood_num->setString(String::createWithFormat("%d", hp)->getCString());
	this->addChild(label_blood_num);
	//collidable = tileMap1->getLayer("collider");//找到碰撞层
	//auto collBody = PhysicsBody::createBox(collidable->getContentSize());
	//collidable->setPhysicsBody(collBody);
	//TMXObjectGroup *objects1 = tileMap1->getObjectGroup("Gold");
	//ValueVector values = objects1->getObjects();	
	//for (Value value : values)//遍历所有对象
	//{
	//	ValueMap valueMap = value.asValueMap();//获得属性值：Value转换成ValueMap
	//	float gx = valueMap["x"].asFloat();//获取对象的属性:(as一类的方法 （转换类型）
	//	float gy = valueMap["y"].asFloat();
	//	//this->coinsList.pushBack(valueMap);
	//	Sprite* gold = Sprite::create("gold.png");
	//	gold->setPosition(Vec2(gx, gy));
	//	log("now add gold");
	//	
	//	addChild(gold);k
	//}
	
//添加人物精灵
	player = Sprite::create("player.png");//获得精灵对象
	//player = new Player();
	player->setPosition(100, 150);
	player->setTag(0);
	auto playerBody = PhysicsBody::createBox(player->getContentSize());
	player->setPhysicsBody(playerBody);
	addChild(player);
/*怪物的产生*/
	for (int i = 0; i<MAX_MONSTER_NUM; i++) {
		monster = new Monster();
		this->addChild(monster, 1);//将此控件添加到场景，层次为2
		monster_arr[i] = monster;//保存怪物对象到类指针中，给即时更新事件update中处理。
	}
/*金币的产生*/
	for (int i = 0; i<MAX_MONSTER_NUM; i++) {
		coin = new Coin();
		this->addChild(coin, 1);//将此控件添加到场景，层次为2
		coin_arr[i] = coin;//保存怪物对象到类指针中，给即时更新事件update中处理。
	}
	setTouchEnabled(true);//开启层触摸事件
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);//设置单点触摸事件
//添加循环播放，用于背景循环和人物移动
	this->scheduleUpdate();
    return true;
}

void GameScene::onEnter()
{
	Layer::onEnter();
	//log("HelloWorld onEnter");
//键盘事件的监听器、分发器和优先级
	auto listener = EventListenerKeyboard::create();//创建监听器
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		//log("press");
		keyMap[keyCode] = true;
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) {
			auto jump = MoveBy::create(0.5, Vec2(0, 100));
			player->runAction(jump);
		}
	};
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		//log("release");
		keyMap[keyCode] = false;
	}; 
	EventDispatcher *eventdis = Director::getInstance()->getEventDispatcher();
	//设置优先级
	eventdis->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::update(float delta)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
//背景滚动：
	auto mapPositionX1 = tileMap1->getPositionX();
	auto mapPositionX2 = tileMap2->getPositionX();
	
	int iSpeed = 10;	//滚动速度
	mapPositionX1 -= iSpeed;
	mapPositionX2 -= iSpeed;

	if (mapPositionX1 <= -tileMap1->getContentSize().width) {
		mapPositionX1 = tileMap1->getContentSize().width + tileMap2->getPositionX() - 15;

		log("now add map1");
	}else if (mapPositionX2 <= -tileMap1->getContentSize().width) {
		mapPositionX2 = tileMap2->getContentSize().width + tileMap1->getPositionX() - 15;
		//log("now add map2");
	}
	tileMap1->setPositionX(mapPositionX1);
	tileMap2->setPositionX(mapPositionX2);
//怪物产生：
	for (int i = 0; i<MAX_MONSTER_NUM; i++) {//时刻遍历怪物的类指针数组
		monster = monster_arr[i];
		if (monster->isEmerge) {//如果怪物处于屏幕内	
			monster->sprite->setPosition(ccp(monster->sprite->getPositionX() - visibleSize.width / 100,
				monster->sprite->getPositionY()));//那么他们的位置将会移动当前屏幕宽度与高度的1/100
			if (monster->sprite->getPositionX()<0 || monster->sprite->getPositionY()<0) {//如果怪物x坐标小于0，则表示已经超出屏幕范围，隐藏怪物
				monster->sprite->setVisible(false);//将其隐藏
				monster->isEmerge = false;//设置为不在屏幕内
			}
			if (is_collision(player, monster->sprite)) {//判断怪物是否碰撞玩家
				monster->sprite->setVisible(false);//将其隐藏
				SimpleAudioEngine::getInstance()->playEffect("sound/1.wav");
				hp -= 30;
				label_blood_num->setString(String::createWithFormat("%d", hp)->getCString());
				//player->hit();//玩家执行被撞击函数
				monster->isEmerge = false;//设置为不在屏幕内		
				if (hp<1) {//如果玩家被扣到0						
					UserDefault::getInstance()->setIntegerForKey("score", score);
					Director::getInstance()->replaceScene(GameOver::createScene());//游戏重新开始
				}
			}
		}
		else {
			monster->sprite->setPosition(ccp(5 * visibleSize.width / 6 + CCRANDOM_0_1()*visibleSize.width / 6,  CCRANDOM_0_1()*visibleSize.height + 96));
			monster->sprite->setVisible(true);
			monster->isEmerge = true;
		}
	}
	for (int i = 0; i<MAX_MONSTER_NUM; i++) {//时刻遍历怪物的类指针数组
		coin = coin_arr[i];
		if (coin->isEmerge) {	
				coin->sprite->setPosition(ccp(coin->sprite->getPositionX() - visibleSize.width / 100,
				coin->sprite->getPositionY()));
			if (coin->sprite->getPositionX()<0 || coin->sprite->getPositionY()<0) {
				coin->sprite->setVisible(false);
				coin->isEmerge = false;
			}
			if (is_collision(player, coin->sprite)) {//判断金币是否碰撞玩家
				coin->sprite->setVisible(false);//将其隐藏
				SimpleAudioEngine::getInstance()->playEffect("sound/about.wav");
				score += 10;
				label_score_num_->setString(String::createWithFormat("%d", score)->getCString());
				coin->isEmerge = false;
			}
		}
		else {//在屏幕的右方区域产生金币
			coin->sprite->setPosition(ccp(5 * visibleSize.width / 6 + CCRANDOM_0_1()*visibleSize.width / 6, CCRANDOM_0_1()*visibleSize.height + 96));
			coin->sprite->setVisible(true);
			coin->isEmerge = true;
		}
	}
//人物移动：
	auto left = cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW;
	auto right = cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	auto up = cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW;
	int offsetX = 0;
	if (keyMap[left]) {
		offsetX = -4;
	}
	if (keyMap[right]) {
		offsetX = 4;
	}
	if (offsetX == 0) {
		return;
	}
	Node* moveSprite = this->getChildByTag(0);
	auto moveTo = MoveTo::create(0.2, Vec2(moveSprite->getPositionX() + offsetX, moveSprite->getPositionY()));
	moveSprite->runAction(moveTo);
}

void GameScene::onExit()
{
	this->scheduleUpdate();
	Layer::onExit();
}

bool GameScene::onTouchBegan(cocos2d::Touch * touch, Event * event)
{
	return true;
}

void GameScene::onTouchMoved(cocos2d::Touch * touch, Event * event)
{

}

void GameScene::onTouchEnded(cocos2d::Touch * touch, Event * event)
{
	
}

bool GameScene::is_collision(Sprite * sprite1, Sprite * sprite2)
{
	//建立精灵1的矩形  
	Size sprite_size1 = sprite1->getContentSize();//求精灵的尺寸  
	Point sprite_position1 = sprite1->getPosition();//求精灵的中心点坐标  
	Rect sprite_rect1 = CCRectMake(//以精灵的中心点为中心点、以精灵的尺寸为宽与高，建立一个矩形。  
		sprite_position1.x - sprite_size1.width / 2,
		sprite_position1.y - sprite_size1.height / 2,
		sprite_size1.width,
		sprite_size1.height);
	//建立精灵2的矩形，同理  
	Size sprite_size2 = sprite2->getContentSize();
	Point sprite_position2 = sprite2->getPosition();
	Rect sprite_rect2 = CCRectMake(
		sprite_position2.x - sprite_size2.width / 2,
		sprite_position2.y - sprite_size2.height / 2,
		sprite_size2.width,
		sprite_size2.height);
//如果是判断矩形与一个像素点则用Rect实例.containsPoint(像素点);这里是判断两个矩形是否相交  
	return sprite_rect1.intersectsRect(sprite_rect2);
}






