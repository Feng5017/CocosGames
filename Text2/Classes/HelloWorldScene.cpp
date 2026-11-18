#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SettingScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	log("create a HelloWorld Scene");
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
	log("HelloWorld init!");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto bg = Sprite::create("WX/background.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg, 0);
/*
//用精灵帧缓存的方式添加菜单
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("menu/hero.plist");
//开始精灵菜单
	auto startSpriteNormal = Sprite::createWithSpriteFrameName("start-up.png");
	auto startSpriteSelected = Sprite::createWithSpriteFrameName("start-down.png");
//开始菜单
	auto startMenuItem = MenuItemSprite::create(startSpriteNormal, startSpriteSelected,
		CC_CALLBACK_1(HelloWorld::menuStartCallback, this));
	startMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(700, 168)));
*/

	auto startMenuItem = MenuItemImage::create("WX/start-up.png", "WX/start-down.png",
		CC_CALLBACK_1(HelloWorld::menuStartCallback, this));
	startMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(800, 160)));
//用图片菜单的方式添加设置菜单
	auto settingMenuItem = MenuItemImage::create("WX/setting-up.png", "WX/setting-down.png",
		CC_CALLBACK_1(HelloWorld::menuSettingCallback, this));
	settingMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(800, 340)));

//用图片菜单的方式添加帮助菜单
	auto helpMenuItem = MenuItemImage::create("WX/help-up.png", "WX/help-down.png",
		CC_CALLBACK_1(HelloWorld::menuGoCallback, this));
	helpMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(800, 520)));

	auto mn = Menu::create(startMenuItem, settingMenuItem, helpMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);

    return true;
}

void HelloWorld::onEnter(){
	Scene::onEnter();
	log("HelloWorld onEnter");
}

void HelloWorld::onEnterTransitionDidFinish(){
	Scene::onEnterTransitionDidFinish();
	log("HelloWorld onEnterTransitionDidFinish");
}

void HelloWorld::onExit(){
	Scene::onExit();
	log("HelloWorld onExit");
}

void HelloWorld::onExitTransitionDidStart(){
	Scene::onExitTransitionDidStart();
	log("HelloWorld onExitTransitionDidStart");
}

void HelloWorld::cleanup(){
	Scene::cleanup();
	log("HelloWorld cleanup");
}

void HelloWorld::menuStartCallback(Ref* pSender)
{
}

void HelloWorld::menuSettingCallback(Ref* pSender)
{
	log("Push to Setting Scene");
	auto sc = Setting::createScene();
	auto tsc = TransitionFadeTR::create(1.0f, sc);
	Director::getInstance()->pushScene(tsc);
}

void HelloWorld::menuGoCallback(Ref* pSender)
{
	log("Close down Scene");
	Director::getInstance()->end();
}
