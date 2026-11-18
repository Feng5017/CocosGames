#include "SimpleAudioEngine.h"

#include "GameOver.h"
#include "GameScene.h"
#include "HelloWorld.h"
USING_NS_CC;
#include "cocos2d.h"

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
//背景
	auto spr_bg = Sprite::create("bg2.png");
	spr_bg->setPosition(ccp(visiable.width / 2, visiable.height / 2));
	this->addChild(spr_bg);
//分数记录
	auto label_score = Label::create();
	label_score->setString(((__String*)(dictionary->objectForKey("score")))->getCString());
	label_score->setSystemFontSize(40);
	label_score->setColor(Color3B(255, 255, 255));
	label_score->enableOutline(Color4B::BLACK, 3);
	label_score->setAnchorPoint(ccp(0.5, 0.5));
	label_score->setPosition(ccp(visiable.width / 2 - label_score->getContentSize().width / 2,
		visiable.height / 4 * 3));
	this->addChild(label_score);

	auto label_score_num = Label::create();
	label_score_num->setSystemFontSize(40);
	label_score_num->setColor(Color3B(255, 255, 255));
	label_score_num->enableOutline(Color4B::BLACK, 3);
	label_score_num->setAnchorPoint(ccp(0, 0.5));
	label_score_num->setPosition(ccp(visiable.width / 2 + label_score->getContentSize().width / 2, visiable.height / 4 * 3));
	this->addChild(label_score_num);

//返回菜单
	auto str = (__String*)(dictionary->objectForKey("back_menu"));
	auto btn_label = Label::create();
	btn_label->setColor(Color3B(255, 255, 255));
	btn_label->enableOutline(Color4B::BLACK, 3);
	btn_label->setString(str->getCString());
	btn_label->setSystemFontSize(40);

	auto start_menu = MenuItemLabel::create(btn_label,
		CC_CALLBACK_1(GameOver::menu_play, this));
	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(ccp(visiable.width / 2, visiable.height / 2));
	this->addChild(menu);

	//获取分数
	auto score = UserDefault::getInstance()->getIntegerForKey("score");
	label_score_num->setString(String::createWithFormat("%d", score)->getCString());

	log("I will be back");	

	return true;
}

void GameOver::menu_play(Ref * pSender)
{
	log("I will be back");
	auto sc = HelloWorld::createScene();
	auto tsc = TransitionCrossFade::create(0.5f, sc);
	Director::getInstance()->replaceScene(tsc);
}
