#include "SimpleAudioEngine.h"
#include "HelloWorld.h"
#include "GameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init() //初始化场景
{
	if (!Scene::init()) {
		return false;
	}
	//设置窗口大小和坐标系
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

//添加游戏背景
	auto spr_bg = Sprite::create("bg1.png");
	spr_bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(spr_bg);
//音乐背景：
	isopen = false;
	auto menuitem = MenuItemImage::create("on.png", "on.png", CC_CALLBACK_1(HelloWorld::menuMusicToggleCallback, this));
	auto musicToggleMenuItem = Menu::create(menuitem, NULL);
	musicToggleMenuItem->setPosition(Vec2(visibleSize.width / 10 * 9, visibleSize.height / 10 * 9));
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/yinyue1.mp3");
	this->addChild(musicToggleMenuItem, 1);
	//点击音效：
	//auto menuitem1 = MenuItemImage::create("on1.png", "on1.png", CC_CALLBACK_1(HelloWorld::menuMusicEffectCallback, this));
	//auto musicEffectMenuItem = Menu::create(menuitem1, NULL);
	//musicEffectMenuItem->setPosition(Vec2(visibleSize.width / 10 * 9 + 20, visibleSize.height / 10 * 8));
	//this->addChild(musicEffectMenuItem, 3);
	//SimpleAudioEngine::getInstance()->preloadEffect("sound/Button1.wav");
	//SimpleAudioEngine* audioEngine = SimpleAudioEngine::getInstance();
	////isopen = true;
	//audioEngine->setEffectsVolume(1);

//读取xml，以显示汉字按钮
	auto dic = Dictionary::createWithContentsOfFile("fonts/text.xml");
	//通过xml创建标题
	const char *title;
	char name[10];
	sprintf(name, "title");
	title = ((String*)dic->objectForKey(name))->getCString();
	//注意：xml生成的字体必须赋予一层标签，否则无法生成
	auto titleLabel = Label::createWithTTF(title, "fonts/STXINGKA.TTF", 60);
	titleLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 20));
	titleLabel->setColor(Color3B(255, 255, 255));
	titleLabel->enableOutline(Color4B::BLACK, 3);
	this->addChild(titleLabel);
	
	//添加开始按钮
	auto str = (String*)(dic->objectForKey("play"));
	auto btn_label = Label::create();
	btn_label->setString(str->getCString());
	btn_label->setSystemFontSize(40);
	btn_label->setColor(Color3B(255, 255, 255));
	btn_label->enableOutline(Color4B::BLACK, 3);
	//绑定监听
	auto start_menu = MenuItemLabel::create(btn_label,
		CC_CALLBACK_1(HelloWorld::start_play, this));
	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.3));
	this->addChild(menu);


	return true;
}

//音乐开关：
void HelloWorld::menuMusicToggleCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/Button1.wav", false, 1.0f, 0.0f, 1);
	if (isopen) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/yinyue1.mp3");
		isopen = false;
	}
	else {
		SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/yinyue1.mp3");
		isopen = true;
	}
}
void HelloWorld::menuMusicEffectCallback(Ref* pSender)
{
	static int effectId;
	if (isopen) {
		SimpleAudioEngine* audioEngine = SimpleAudioEngine::getInstance();
		SimpleAudioEngine::getInstance()->preloadEffect("sound/Button1.wav");
		isopen = false;
	}
	else {
		SimpleAudioEngine* audioEngine = SimpleAudioEngine::getInstance();
		audioEngine->unloadEffect("sound / Button1.wav");
		isopen = true;
	}
}

void HelloWorld::start_play(Ref* pSender)
{
	//切换场景
	auto sc = GameScene::createScene();
	auto tsc = TransitionCrossFade::create(0.5f, sc);
	Director::getInstance()->replaceScene(tsc);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}