#include "SimpleAudioEngine.h"

#include "HelloWorldScene.h"
#include "GameOver.h"
#include "MainGame.h"
USING_NS_CC;
#include "cocos2d.h"

GameOver::GameOver() {}
GameOver::~GameOver() {}

Scene* GameOver::createScene()
{
	return GameOver::create();
}

bool GameOver::init()
{
	if (!Scene::init())
		return false;

	auto dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");
	auto visiable = Director::getInstance()->getWinSize();

	//添加背景
	auto spr_bg = Sprite::create("ui/bg.png");
	spr_bg->setPosition(ccp(visiable.width / 2, visiable.height / 2));
	this->addChild(spr_bg);

	/*设置分数*/
	auto label_score = Label::create();
	label_score->setString(((__String*)(dictionary->objectForKey("score")))->getCString());
	label_score->setSystemFontSize(40);
	label_score->setAnchorPoint(ccp(0.5, 0.5));
	label_score->setPosition(ccp(visiable.width / 2 - label_score->getContentSize().width / 2,
		visiable.height / 4 * 3));
	this->addChild(label_score);

	auto label_score_num = Label::create();
	label_score_num->setSystemFontSize(30);
	label_score_num->setAnchorPoint(ccp(0, 0.5));
	label_score_num->setPosition(ccp(visiable.width / 2 + 20, visiable.height / 4 * 3));
	this->addChild(label_score_num);
	//最高分
	auto label_best_score = Label::create();
	label_best_score->setString(((__String*)(dictionary->objectForKey("best_score")))->getCString());
	label_best_score->setSystemFontSize(40);
	label_best_score->setAnchorPoint(ccp(0.5, 0.5));
	label_best_score->setPosition(ccp(visiable.width / 2 - label_best_score->getContentSize().width / 2,
		visiable.height / 4 * 3 - 40));
	this->addChild(label_best_score);

	auto label_best_score_num = Label::create();
	label_best_score_num->setSystemFontSize(30);
	label_best_score_num->setAnchorPoint(ccp(0, 0.5));
	label_best_score_num->setPosition(ccp(visiable.width / 2 + 20, visiable.height / 4 * 3 - 40));
	this->addChild(label_best_score_num);

	//获取最高分
	auto score_win = UserDefault::getInstance()->getIntegerForKey("best_score");
	auto score = UserDefault::getInstance()->getIntegerForKey("score");
	//最高分
	label_best_score_num->setString(String::createWithFormat("%d", score_win)->getCString());
	label_score_num->setString(String::createWithFormat("%d", score)->getCString());

	//添加返回主页Menu
	auto btn_label = Label::create();
	btn_label->setString(((__String*)(dictionary->objectForKey("back_menu")))->getCString());
	btn_label->setSystemFontSize(40);
	auto start_menu = MenuItemLabel::create(btn_label, CC_CALLBACK_1(GameOver::menu_play, this));

	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(ccp(visiable.width / 2, visiable.height / 2));
	this->addChild(menu);

	return true;
}

void GameOver::menu_play(Ref * pSender)
{
	auto sc = HelloWorld::createScene();
	auto tsc = TransitionCrossFade::create(0.5f, sc);
	Director::getInstance()->replaceScene(tsc);
}

