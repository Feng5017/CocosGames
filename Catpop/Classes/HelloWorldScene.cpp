#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SecondScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("beijing.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);
	
	/*速度控制
	auto EaseInOutLabel = Label::createWithBMFont("fonts/fnt2.fnt", "kEaseInOut");
	auto EaseSineInLabel = Label::createWithBMFont("fonts/fnt2.fnt", "kEaseSineIn");
	auto EaseExponentialOutLabel = Label::createWithBMFont("fonts/fnt2.fnt", "kEaseExponentialOut");
	auto SpeedLabel=Label::createWithBMFont("fonts/fnt2.fnt", "kSpeed");
	
	auto EaseInOutItem = MenuItemLabel::create(EaseInOutLabel, 
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	auto EaseSineInItem = MenuItemLabel::create(EaseSineInLabel, CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	auto EaseExponentialOutItem = MenuItemLabel::create(EaseExponentialOutLabel, CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	auto SpeedItem = MenuItemLabel::create(SpeedLabel, CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));*/
	
	//网格动画菜单标签
	auto pb1 = Label::createWithBMFont("fonts/fnt2.fnt", "FlipX3D");
	auto pb2 = Label::createWithBMFont("fonts/fnt2.fnt", "Waves3D");
	auto pb3 = Label::createWithBMFont("fonts/fnt2.fnt", "WavesTiles3D");

	auto pm1 = MenuItemLabel::create(pb1, CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	auto pm2 = MenuItemLabel::create(pb2, CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	auto pm3 = MenuItemLabel::create(pb3, CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
		
	pm1->setTag(kFlipX3d);
	pm2->setTag(kWaves3d);
	pm3->setTag(kWavesTiles3d);

	Menu* mn = Menu::create(pm1, pm2, pm3, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);

/*	帧动画菜单标签
	auto pb1 = Label::createWithBMFont("fonts/fnt2.fnt", "FrameAction");
	auto pm1 = MenuItemLabel::create(pb1, CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	Menu* mn = Menu::create(pm1, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);*/
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	MenuItem* mitem = (MenuItem*)pSender;//定义菜单项,强制类型转换
	//
	//auto sc = Second::createScene();此语句功能等同于下面三局
	auto sc = Scene::create();//建立一个空场景；
	auto layer = Second::create();//建立空层；	
	sc->addChild(layer);//把层加到场景中
	
	//这是层标签法
	layer->setTag(mitem->getTag());//菜单的tag即为层的tag
	//这是public法
	layer->flag = mitem->getTag();

	auto tsc = TransitionSlideInR::create(0.5f, sc);
	Director::getInstance()->replaceScene(tsc);
}
