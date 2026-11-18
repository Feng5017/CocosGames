#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "SelectScene.h"
#include "Stage.h"
#include "GameOver.h"
USING_NS_CC;


Scene* GameScene::createScene()
{
	return GameScene::create();
}

int GameScene::touchflag = 0;
bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	MenuItemFont::setFontSize(100);
//游戏背景
	auto background = Sprite::create("gamebackground.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(background);
//退出界面
	auto dic = Dictionary::createWithContentsOfFile("guanqia.xml");
	const char *p;
	char name[10];
	sprintf(name, "exit1");
	p = ((String*)dic->objectForKey(name))->getCString();
	auto exit = MenuItemFont::create(p, CC_CALLBACK_0(GameScene::toExit, this));
	auto exitMenu = Menu::create(exit, NULL);
	exitMenu->setPosition(Vec2(visibleSize.width / 10 * 9, visibleSize.height / 10 ));
	this->addChild(exitMenu, 0);

	stage = Stage::create();
	this->addChild(stage, 1);
//鼠标触发事件
	x1 = -1;
	ifOnTouchMove = false;
	auto listener = EventListenerTouchOneByOne::create();  
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchStart, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMove, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnd, this);
	
	auto eventDis = Director::getInstance()->getEventDispatcher(); 
	eventDis->addEventListenerWithSceneGraphPriority(listener, stage);
//不同关卡的不同操作：
	if (SelectScene::flag == 1)
	{
		scheduleUpdate();
	}
	if (SelectScene::flag == 2)
	{	
		schedule(schedule_selector(GameScene::toGameOver), 45.0f);
	}
	if (SelectScene::flag == 3)
	{
		schedule(schedule_selector(GameScene::toGameOver), 30.0f);
	}
	
	return true;
}
void GameScene::toExit()
{
	auto scene = SelectScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameScene::update(float dt)
{
	if (SelectScene::flag == 1)
	{
		if (Stage::number <= 0){
			schedule(schedule_selector(GameScene::toGameOver));
			unscheduleUpdate();
		}
	}
}

void GameScene::toGameOver(float dt)
{
	Scene *scene = GameOver::createScene();
	Director::getInstance()->replaceScene(scene);
}
bool GameScene::onTouchStart(Touch *touch, Event *event)
{
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			if (Stage::tag[i][j] == -1||Stage::tag[i][j] == 0)   //坐标为0表示已消除，为-1表示为空
				continue;
			if (stage->animal[i][j]->getBoundingBox().containsPoint(touch->getLocation())) //若准确点击到图片上则执行
			{
				if (x1 == -1){
					stage->selectFirst(i, j);
					x1 = i;
					y1 = j;
				}
				else {
					x2 = i;
					y2 = j;
					if (abs(x1 - x2) + abs(y1 - y2) == 1) {        //点到相邻图片才执行
						stage->removeSelectFirst(x1, y1);
						stage->swap(x1, y1, x2, y2);
						x1 = -1;
						touchflag = 1;
					}
					else {
						stage->removeSelectFirst(x1, y1);          //未点到相邻图片取消点击效果，并转换点击图片的位置
						x1 = i;
						y1 = j;
						stage->selectFirst(x1, y1);
					}
				}
				return true;   //点击事件成功，返回true
			}
		}
	}
	return false;
}
void GameScene::onTouchMove(Touch *touch, Event *event)
{
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (Stage::tag[i][j] == -1 || ifOnTouchMove == true|| Stage::tag[i][j] == 0)
				continue;

			if (x1 == -1)
				continue;
			if (stage->animal[i][j]->getBoundingBox().containsPoint(touch->getLocation())){ 
				x2 = i;
				y2 = j;
				if (abs(x1 - x2) + abs(y1 - y2) == 1) {
					stage->removeSelectFirst(x1, y1);
					stage->swap(x1, y1, x2, y2);
					x1 = -1;
					touchflag = 1;
				}
				else {
					stage->removeSelectFirst(x1, y1);
					x1 = i;
					y1 = j;
					stage->selectFirst(x1, y1);
				}
				ifOnTouchMove = true;
			}
		}
	}
}

void GameScene::onTouchEnd(Touch *touch, Event *event) //取消上一次点击
{
	ifOnTouchMove = false;
	touchflag = 1;
}
