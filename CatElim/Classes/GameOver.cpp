#include "GameOver.h"
#include "SelectScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "Stage.h"
using namespace CocosDenshion;
USING_NS_CC;

Scene* GameOver::createScene()
{
	return GameOver::create();
}
bool GameOver::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("beijing1.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(background);

	bestScore = UserDefault::sharedUserDefault()->getIntegerForKey("BestScore1", 0);
	if(bestScore<Stage::score)        //最高分更新则记录更新
	{
		bestScore = Stage::score;
	}
	UserDefault::sharedUserDefault()->setIntegerForKey("BestScore1", bestScore);
	UserDefault::sharedUserDefault()->flush();  //保存数据不丢失

	char count[20];
	sprintf(count, "bestscore:%d", bestScore);  //最好成绩
	Label *bestScoreLabel = Label::createWithTTF(count, "fonts/arial.ttf", 90);
	bestScoreLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 150);
	bestScoreLabel->setColor(Color3B(255, 255, 255));
	bestScoreLabel->enableOutline(Color4B::BLACK, 3);
	this->addChild(bestScoreLabel, 0);           //新成绩
	sprintf(count, "nowscore:%d", Stage::score);
	Label *nowScoreLabel = Label::createWithTTF(count, "fonts/arial.ttf", 90);
	nowScoreLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 150);
	nowScoreLabel->setColor(Color3B(255, 255, 255));
	nowScoreLabel->enableOutline(Color4B::BLACK, 3);
	this->addChild(nowScoreLabel, 0);
//返回：
	MenuItemFont *toSelect = MenuItemFont::create("return", CC_CALLBACK_0(GameOver::toSelect, this));
	Menu *returnMenu = Menu::create(toSelect, NULL);
	returnMenu->setPosition(visibleSize.width / 2, 40);
	this->addChild(returnMenu, 0);

	return true;
}

void GameOver::toSelect()
{
	Stage::number = 10;
	Scene *scene = SelectScene::createScene();
	Director::getInstance()->replaceScene(scene);
}