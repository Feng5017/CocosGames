#include "SimpleAudioEngine.h"

#include "HelloWorldScene.h"
#include "SelectScene.h"
#include "GameScene.h"
#include "Stage.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* HelloWorld::createScene()
{
	/*Scene *scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(100.0f, 0.0f));

	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;*/

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

	////物理世界边界：
	//Sprite *edgeSprite = Sprite::create();
	//PhysicsBody*boundBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	//boundBody->getShape(0)->setFriction(0.0f);   //摩擦力
	//boundBody->getShape(0)->setRestitution(1.0f);  //刚体恢复力

	//edgeSprite->setPhysicsBody(boundBody);
	//edgeSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	//addChild(edgeSprite);
//首页背景：
	auto background = Sprite::create("beijing.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(background);
//音乐背景：
	isopen = false;
	auto menuitem = MenuItemImage::create("on.png", "on.png", CC_CALLBACK_1(HelloWorld::menuMusicToggleCallback, this));
	auto musicToggleMenuItem = Menu::create(menuitem, NULL);
	musicToggleMenuItem->setPosition(Vec2(visibleSize.width / 10 * 9, visibleSize.height / 10 * 9));
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/yinyue1.mp3");
	this->addChild(musicToggleMenuItem, 1);
//点击音效：
	auto menuitem1= MenuItemImage::create("on1.png", "on1.png", CC_CALLBACK_1(HelloWorld::menuMusicEffectCallback, this));
	auto musicEffectMenuItem = Menu::create(menuitem1, NULL);
	musicEffectMenuItem->setPosition(Vec2(visibleSize.width / 10 * 9 + 20, visibleSize.height / 10 * 8));
	this->addChild(musicEffectMenuItem, 3);
	SimpleAudioEngine::getInstance()->preloadEffect("sound/Button1.wav");
	SimpleAudioEngine* audioEngine = SimpleAudioEngine::getInstance();
	//isopen = true;
	audioEngine->setEffectsVolume(1);
//游戏菜单：
	auto dic = Dictionary::createWithContentsOfFile("Hello.xml");
	const char *p;
	char name[10];
	sprintf(name, "num_0");
	p = ((String*)dic->objectForKey(name))->getCString();
	auto label1 = Label::createWithTTF(p, "fonts/STXINGKA.TTF", 150);
	label1->setColor(Color3B(255, 255, 255));
	label1->enableOutline(Color4B::BLACK, 3);
	auto guanqiaFirst = MenuItemLabel::create(label1, CC_CALLBACK_0(HelloWorld::toSelect, this));
	auto guanqiaFirstMenu = Menu::create(guanqiaFirst, NULL);
	guanqiaFirstMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4 * 2));
	this->addChild(guanqiaFirstMenu, 1);
//退出开关：
	sprintf(name, "num_1");
	p = ((String*)dic->objectForKey(name))->getCString();
	auto label2 = Label::createWithTTF(p, "fonts/STXINGKA.TTF", 100);
	label2->setColor(Color3B(255, 255, 255));
	label2->enableOutline(Color4B::BLACK, 3);
	auto exit = MenuItemLabel::create(label2, CC_CALLBACK_0(HelloWorld::toExit, this));
	auto exitMenu = Menu::create(exit, NULL);	
	exitMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4 * 1));
	this->addChild(exitMenu, 0);
//粒子特效：
	ParticleSystem* particle = ParticleRain::create();
	particle->setTexture(CCTextureCache::sharedTextureCache()->addImage("lizi.png"));
	particle->setStartSize(10);
	particle->setScale(5.0f);
	particle->setSpeed(3);
	this->addChild(particle, 3);

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

void HelloWorld::toSelect()      //进入场景
{
	auto scene = SelectScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void HelloWorld::toExit()
{
	Director::getInstance()->end();
}