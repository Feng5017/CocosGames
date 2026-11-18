#include "SimpleAudioEngine.h"

#include "HelloWorldScene.h"
#include "GameStart.h"

USING_NS_CC;
using namespace cocos2d;

Scene* GameStart::createScene()
{
	auto scene = GameStart::create();
	return scene;
}

bool GameStart::init()
{
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");

	auto bg = Sprite::create("bg.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);

	auto startMenuItem = MenuItemImage::create("on.png", "off.png",
		CC_CALLBACK_1(GameStart::menuCallback, this));
	startMenuItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 60));
	auto rescoreMenuItem = MenuItemImage::create("rescore_on.png", "rescore_off.png",
		CC_CALLBACK_1(GameStart::rescoreCallback, this));
	rescoreMenuItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 30));
	auto mn = Menu::create(startMenuItem,rescoreMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);

	return true;
}

void GameStart::menuCallback(cocos2d::Ref * pSender)
{
	auto sc = HelloWorld::createScene();
	auto tsc = TransitionFadeBL::create(0.5f, sc);
	Director::getInstance()->replaceScene(tsc);
}

void GameStart::rescoreCallback(cocos2d::Ref * pSender)
{
	int score = 0;
	UserDefault::getInstance()->setIntegerForKey("best_score", score);
}
