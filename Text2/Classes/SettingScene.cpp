#include "SettingScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* Setting::createScene()
{
	log("create a Setting Scene");

	auto scene = Scene::create();
	auto layer = Setting::create();
	scene->addChild(layer);
	return scene;
}

bool Setting::init()
{
	if (!Scene::init())
	{
		return false;
	}
	log("Setting Scene init");

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
//Ìí¼Ó±³¾°
	auto bg = Sprite::create("WX/setting-back.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg, 0);
//±³¾°Òô¿ØÖÆ°´¼ü
	auto soundOnMenuItem = MenuItemImage::create("WX/on.png", "WX/on.png");
	auto soundOffMenuItem = MenuItemImage::create("WX/off.png", "WX/off.png");
	auto soundToggleMenuItem = MenuItemToggle::createWithCallback
		(CC_CALLBACK_1(Setting::menuOkCallback, this),
			soundOnMenuItem, soundOffMenuItem, NULL);
	soundToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(870, 400)));
//ÒôÐ§¿ØÖÆ°´¼ü
	auto musicOnMenuItem = MenuItemImage::create("WX/on.png", "WX/on.png");
	auto musicOffMenuItem = MenuItemImage::create("WX/off.png", "WX/off.png");
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback
		(CC_CALLBACK_1(Setting::menuOkCallback, this),
			musicOnMenuItem, musicOffMenuItem, NULL);
	musicToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(870, 250)));
//±³¾°Òô¿ØÖÆ°´¼ü
	auto okMenuItemOn = MenuItemImage::create("WX/ok-on.png", "WX/ok-on.png");
	auto okMenuItemOff = MenuItemImage::create("WX/ok-up.png", "WX/ok-up.png");
	auto okToggleMenu = MenuItemToggle::createWithCallback
		(CC_CALLBACK_1(Setting::menuCloseCallback, this),
			okMenuItemOn, okMenuItemOff, NULL);
	okToggleMenu->setPosition(Director::getInstance()->convertToGL(Vec2(720, 560)));

	auto mn = Menu::create(soundToggleMenuItem, musicToggleMenuItem, okToggleMenu, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);

	return true;
}

void Setting::menuOkCallback(cocos2d::Ref * pSender)
{
}

void Setting::menuCloseCallback(Ref* pSender)
{
	log("Pop to HelloWorld Scene");
	auto sc = HelloWorld::createScene();	
	auto tsc = TransitionFadeTR::create(1.0f, sc);
	Director::getInstance()->popScene();	

	/*if (isEffect)
		SimpleAudioEngine::getInstance()->playEffect("sound/Button1.wav");*/
}

//void Setting::menuSoundToggleCallback(cocos2d::Ref * pSender)
//{
//	auto soundToggleMenuItem = (MenuItemToggle*)pSender;
//	log("soundToggleMenuItem %d", soundToggleMenuItem->getSelectedIndex());
//	if (isEffect)
//		SimpleAudioEngine::getInstance()->playEffect("sound/Button1.wav");
//
//	if (soundToggleMenuItem->getSelectedIndex() == 1)
//		SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/K448.mp3");
//	else
//		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/K448.mp3");
//}
//
//void Setting::menuMusicToggleCallback(cocos2d::Ref * pSender)
//{
//	auto musicToggleMenuItem = (MenuItemToggle*)pSender;
//	log("musicToggleMenuItem %d", musicToggleMenuItem->getSelectedIndex());
//	if (isEffect)
//		SimpleAudioEngine::getInstance()->playEffect("sound/Button1.wav");
//
//	if (musicToggleMenuItem->getSelectedIndex() == 1)
//		isEffect = false;
//	else
//		isEffect = true;
//}

void Setting::onEnter()
{
	Scene::onEnter();
	log("Setting onEnter");
}

void Setting::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
	log("Setting onEnterTransitionDidFinish");
	/*isEffect = true;
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/K448.mp3", true);*/
}

void Setting::onExit()
{
	Scene::onExit();
	log("Setting onExit");
}

void Setting::onExitTransitionDidStart()
{
	Scene::onExitTransitionDidStart();
	log("Setting onExitTransitionDidStart");
}

void Setting::cleanup()
{
	Scene::cleanup();
	log("Setting cleanup");
	/*SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/K448.mp3");*/
}
