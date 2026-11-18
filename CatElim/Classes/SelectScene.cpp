#include "HelloWorldScene.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "Stage.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

Scene* SelectScene::createScene()
{
	return SelectScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

int SelectScene::flag = 0;
bool SelectScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}
	isopen = false;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	MenuItemFont::setFontSize(100);
	
	auto dic = Dictionary::createWithContentsOfFile("guanqia.xml");
	char name[10];
//选择菜单：
	sprintf(name, "guanqia1");
	p = ((String*)dic->objectForKey(name))->getCString();
	auto label1 = Label::createWithTTF(p, "fonts/STXINGKA.TTF", 100);
	label1->setColor(Color3B(255, 255, 255));
	label1->enableOutline(Color4B::BLACK, 3);
	auto guanqiaFirst = MenuItemLabel::create(label1, CC_CALLBACK_0(SelectScene::toFirst, this));
	auto guanqiaFirstMenu = Menu::create(guanqiaFirst, NULL);
	guanqiaFirstMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4 * 3));
	this->addChild(guanqiaFirstMenu, 1);

	sprintf(name, "guanqia2");
	p = ((String*)dic->objectForKey(name))->getCString();
	auto label2 = Label::createWithTTF(p, "fonts/STXINGKA.TTF", 100);
	label2->setColor(Color3B(255, 255, 255));
	label2->enableOutline(Color4B::BLACK, 3);
	auto guanqiaSecond = MenuItemLabel::create(label2, CC_CALLBACK_0(SelectScene::toSecond, this));
	auto guanqiaSecondMenu = Menu::create(guanqiaSecond, NULL);
	guanqiaSecondMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4 * 2));
	this->addChild(guanqiaSecondMenu, 1);

	sprintf(name, "guanqia3");
	p = ((String*)dic->objectForKey(name))->getCString();
	auto label3 = Label::createWithTTF(p, "fonts/STXINGKA.TTF", 100);
	label3->setColor(Color3B(255, 255, 255));
	label3->enableOutline(Color4B::BLACK, 3);
	auto guanqiaThird = MenuItemLabel::create(label3, CC_CALLBACK_0(SelectScene::toThird, this));
	auto guanqiaThirdMenu = Menu::create(guanqiaThird, NULL);
	guanqiaThirdMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4 * 1));
	this->addChild(guanqiaThirdMenu, 1);
//首页背景：
	auto background = Sprite::create("beijing.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(background);
//点击音效：
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/Button1.wav");
	SimpleAudioEngine* audioEngine = SimpleAudioEngine::getInstance();
	audioEngine->playEffect("sound/Button1.wav", false, 1.0f, 0.0f, 1);
	audioEngine->setEffectsVolume(1);
//动画：
	/*SpriteFrameCache::getInstance()->addSpriteFramesWithFile("gif/sanjiao.plist", "gif/sanjiao.png");
	Sprite * sprite4 = Sprite::create();
	Animation * animation = Animation::create();
	char donghua[40];
	for (int i = 0; i <= 28; i++)
	{
		sprintf(donghua, "IMG000%d%d.bmp", i / 10, i % 10);
		SpriteFrame*sframe = SpriteFrameCache::getInstance()->getSpriteFrameByName(donghua);
		animation->addSpriteFrame(sframe);
	}
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);
	Animate * animate = Animate::create(animation);
	sprite4->runAction(animate);
	sprite4->setPosition(visibleSize.width / 2 + 300, visibleSize.height / 2 - 250);
	this->addChild(sprite4, 2);*/

//退出开关：
	sprintf(name, "exit2");
	p = ((String*)dic->objectForKey(name))->getCString();
	auto exit = MenuItemFont::create(p, CC_CALLBACK_0(SelectScene::toExit, this));
	auto exitMenu = Menu::create(exit, NULL);
	exitMenu->setPosition(Vec2(visibleSize.width / 10 * 9, visibleSize.height / 10 ));
	this->addChild(exitMenu, 0);

	return true;
}
////音乐开关：
//void SelectScene::menuMusicToggleCallback(Ref* pSender)							
//{
//	if (isopen){
//		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/yinyue1.mp3");
//		isopen = false;
//	}else{
//		SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/yinyue1.mp3");
//		isopen = true;
//	}
//}

void SelectScene::toFirst()       //进入第一关
{
	flag = 1;
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			Stage::tag[i][j] = 0;
		}
	}

	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void SelectScene::toSecond()      //进入第二关
{
	flag = 2;
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			Stage::tag[i][j] = 0;
		}
	}
	Stage::tag[1][1] = -1;
	Stage::tag[1][2] = -1;
	Stage::tag[2][1] = -1;
	Stage::tag[1][8] = -1;
	Stage::tag[1][7] = -1;
	Stage::tag[2][8] = -1;
	Stage::tag[7][8] = -1;
	Stage::tag[7][1] = -1;
	Stage::tag[8][1] = -1;
	Stage::tag[8][2] = -1;
	Stage::tag[8][7] = -1;
	Stage::tag[8][8] = -1;	
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void SelectScene::toThird()      //进入第三关
{
	flag = 3;
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			Stage::tag[i][j] = 0;
		}
	}
	Stage::tag[1][1] = -1;
	Stage::tag[1][8] = -1;
	Stage::tag[8][1] = -1;
	Stage::tag[8][8] = -1;
	Stage::tag[4][4] = -1;
	Stage::tag[4][5] = -1;
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void SelectScene::toExit()
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}