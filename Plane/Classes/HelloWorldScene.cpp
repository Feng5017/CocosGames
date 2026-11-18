#include "HelloWorldScene.h"
#include "MainGame.h"
#include "Select_Plane_Scene.h"
#include "SimpleAudioEngine.h"
#include "ManagerBase.h"
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
    if ( !Scene::init() ){
        return false;
    }
//设置窗口大小和坐标系
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

//添加游戏背景
	auto spr_bg = Sprite::create("ui/bg.png");
	spr_bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(spr_bg);
//读取xml，以显示汉字按钮
	auto dic = Dictionary::createWithContentsOfFile("fonts/text.xml");
//通过xml创建标题
	const char *title;
	char name[10];
	sprintf(name, "title");
	title = ((String*)dic->objectForKey(name))->getCString();
	//注意：xml生成的字体必须赋予一层标签，否则无法生成
	auto titleLabel = Label::createWithTTF(title, "fonts/STXINGKA.TTF", 60);
	titleLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200));
	titleLabel->setColor(Color3B(255, 255, 255));
	titleLabel->enableOutline(Color4B::BLACK, 3);
	this->addChild(titleLabel);
//创建帧动画
	auto animation = Animation::create();
	for (int i = 1; i <= 4; i++){
		auto spr_name = String::createWithFormat("ui/start%d.png", i);
		animation->addSpriteFrameWithFile(spr_name->getCString());
	}
	animation->setDelayPerUnit(0.3f);//帧动画每帧的播放时间
	animation->setLoops(-1);//帧动画的播放次数，-1为无限循环
	//创建精灵启动帧动画
	auto sprite = Sprite::create("ui/start1.png");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite);
	sprite->runAction(Animate::create(animation));
//添加开始按钮
	auto str = (String*)(dic->objectForKey("play"));
	auto btn_label = Label::create();
	btn_label->setString(str->getCString());
	btn_label->setSystemFontSize(40);
	//绑定监听
	auto start_menu = MenuItemLabel::create(btn_label, 
		CC_CALLBACK_1(HelloWorld::start_play, this));
	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.3));
	this->addChild(menu);

	
    return true;
}

void HelloWorld::start_play(Ref* pSender)
{
	ManagerBase::getInstance()->enemy_list_.clear();
	ManagerBase::getInstance()->planesupport_list_.clear();
	ManagerBase::getInstance()->bullet_list_.clear();
	//切换场景
	auto sc = SelectPlaneScene::createScene();
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
