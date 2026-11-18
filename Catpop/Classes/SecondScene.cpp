#include "SimpleAudioEngine.h"
#include "SecondScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;

Scene* Second::createScene()
{
    return Second::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Second::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();	

	gridNodeTarget = NodeGrid::create();//网格特效类，需要添加一个层
	this->addChild(gridNodeTarget);

	auto bg = Sprite::create("beijing.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	gridNodeTarget->addChild(bg);//此处不能用this去添加子类

	pict = Sprite::create("pict.png");//返回给Sprite* pict;
	pict->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	gridNodeTarget->addChild(pict);

	auto goMenuItem = MenuItemImage::create("go-up.png", "go-down.png",
		CC_CALLBACK_1(Second::menugoCallback, this));
	goMenuItem->setPosition(Vec2(visibleSize.width / 2, 180));
    auto backMenuItem = MenuItemImage::create("back-up.png","back-down.png",
        CC_CALLBACK_1(Second::menuCloseCallback, this));
	backMenuItem->setPosition(Vec2(visibleSize.width / 2, 80));  
	
	auto menu = Menu::create(goMenuItem, backMenuItem, NULL);
    menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
    
    return true;
}

void Second::onEnter()
{
	Scene::onEnter();
	log("onEnter layer->flag =%i", this->flag);
	log("onEnter layer->tag =%d", this->getTag());
}

void Second::menuCloseCallback(Ref* pSender)
{
	auto sc = HelloWorld::createScene();
	auto tsc = TransitionSlideInL::create(0.5f, sc);

	Director::getInstance()->replaceScene(tsc);
}

void Second::menugoCallback(Ref* pSender)
{
	log("Tag=%i", this->getTag());
	Size visibleSize = Director::getInstance()->getVisibleSize();

	switch (this->getTag()){
	case kFlipX3d://第一个参数是执行时间
		gridNodeTarget->runAction(FlipX3D::create(2.0f));
		break;
	case kWaves3d://第一个参数是执行时间，第二个是网格大小，第三个是波动次数，第四个是振幅
		gridNodeTarget->runAction(Waves3D::create(2.0f, Size(15, 10), 5, 40));
		break;
	case kWavesTiles3d:
		gridNodeTarget->runAction(CCWavesTiles3D::create(2.0f, Size(15, 10), 5, 40));
		break;
	default:
		break;
	}
}
/*帧动画的OnAction函数
void Second::OnAction(Ref* pSender)
{
	if (!isPlaying)
	{
		Animation* animation = Animation::create();
		for (int i = 1; i <= 5; i++)
		{
			String *frameName = String::createWithFormat("p%d.png", i);
			log("frameName = %s", frameName->getCString());
			SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->
									   getSpriteFrameByName(frameName->getCString());
			animation->addSpriteFrame(spriteFrame);
		}
		
		animation->setDelayPerUnit(0.15f);//设置动画每帧的间隔
		animation->setRestoreOriginalFrame(true);//动画播放后回到原始状态
		Animate*action = Animate::create(animation);
		pict->runAction(RepeatForever::create(action));//反复播放动画

		isPlaying = true;//改变动画播放状态
	}
	else
	{
		pict->stopAllActions();//如果动画正在播放
		isPlaying = false;//停止播放
	}
}*/

/*有参和无参的调用
void Second::CallBack1()
{
	//无参函数，pict是定义好的成员变量
	pict->runAction(TintBy::create(0.5, 255, 0, 255));//变色
}

void Second::CallBack2(Ref* pSender)
{
	//有参函数，传递精灵变量sp
	Sprite* sp = (Sprite*)pSender;
	sp->runAction(TintBy::create(1, 255, 255, 0));
}

void Second::OnCallFunc(Ref* pSender)
{
	auto ac1 = MoveBy::create(1, Vec2(100, 100));
	auto ac2 = ((FiniteTimeAction*)ac1)->reverse();
//无参函数调用
	auto acf = CallFunc::create(CC_CALLBACK_0(Second::CallBack1, this));
	auto seq = Sequence::create(ac1, ac2, acf, NULL);

	pict->runAction(Sequence::create(seq, NULL));
}

void Second::OnCallFuncN(Ref* pSender)
{
	auto ac1 = MoveBy::create(1, Vec2(100, 100));
	auto ac2 = ((FiniteTimeAction*)ac1)->reverse();
//有参函数调用
	auto acf = CallFuncN::create(CC_CALLBACK_1(Second::CallBack2, this));
	auto seq = Sequence::create(ac1, ac2, acf, NULL);

	pict->runAction(Sequence::create(seq, NULL));
}*/

/*组合动画，五种函数
void Second::OnSequence(Ref* pSender) //顺序
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 p = Vec2(visibleSize.width / 2, 200);
	//Sequence::create()的参数类型必须是FiniteTimeAction，故需要强制转换类型
	auto ac0 = (FiniteTimeAction*)pict->runAction(Place::create(p));
	auto ac1 = (FiniteTimeAction*)pict->runAction(MoveTo::create(2, Vec2(visibleSize.width - 200,
		visibleSize.height - 300)));
	auto ac2 = (FiniteTimeAction*)pict->runAction(JumpBy::create(2, Vec2(50, 50), 6, 3));
	auto ac3 = (FiniteTimeAction*)pict->runAction(Blink::create(2, 3));
	auto ac4 = (FiniteTimeAction*)pict->runAction(TintBy::create(0.5, 0, 255, 255));

	pict->runAction(Sequence::create(ac0, ac1, ac2,ac3, ac4, NULL));
}

void Second::OnSpawn(Ref* pSender)//并列
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 p = Vec2(visibleSize.width / 2, 200);
	//设置初始位置和角度
	pict->setRotation(0);
	pict->setPosition(p);
	
	auto ac1 = (FiniteTimeAction*)pict->runAction(MoveTo::create(2, Vec2(visibleSize.width - 100,
		visibleSize.height - 100)));
	auto ac2 = (FiniteTimeAction*)pict->runAction(RotateTo::create(2,90));
	pict->runAction(Spawn::create(ac1, ac2, NULL));
}

void Second::OnRepeat(Ref* pSender)//有限次数重复
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 p = Vec2(visibleSize.width / 2, 100);
	//设置初始位置和角度
	pict->setRotation(0);
	pict->setPosition(p);

	auto ac1 = (FiniteTimeAction*)pict->runAction(MoveBy::create(1, Vec2(0, 200)));
	auto ac2 = (FiniteTimeAction*)pict->runAction(JumpBy::create(1, Vec2(50, 50), 20, 3));
	auto ac3 = (FiniteTimeAction*)pict->runAction(JumpBy::create(1, Vec2(-50, -50), 20, 3));
	auto seq = Sequence::create(ac1, ac2, ac3, NULL);//先构成一个Sequence
	//重复三次去播放序列，Repeat::create()的动作类型需要ActionInterval;
	pict->runAction(Repeat::create(seq, 3));//对Sequence的重复
}

void Second::OnRepeatForever(Ref* pSender)//无限次数重复
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 p = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	pict->setRotation(0);
	pict->setPosition(p);

	ccBezierConfig bezier;//定义一个贝塞尔变量
	bezier.controlPoint_1 = Vec2(0, visibleSize.height / 2);
	bezier.controlPoint_2 = Vec2(10, -visibleSize.height / 2);
	bezier.endPosition = Vec2(10, 20);

	auto ac1 = (FiniteTimeAction*)pict->runAction(BezierBy::create(2, bezier));//第一个参数是时间，第二个是事件
	auto ac2 = (FiniteTimeAction*)pict->runAction(TintBy::create(1, 0, 0, 255));
	auto ac1Reverse = (FiniteTimeAction*)ac1->reverse();//反转的动作
	auto ac2Repeat = (FiniteTimeAction*)pict->runAction(Repeat::create(ac2, 2));//ac2动作重复二次
	auto ac3 = (FiniteTimeAction*)pict->runAction(Spawn::create(ac1, ac2Repeat, NULL));
	auto ac4 = (FiniteTimeAction*)pict->runAction(Spawn::create(ac1Reverse, ac2Repeat, NULL));

	auto seq = Sequence::create(ac3, ac4,NULL);//先构成一个Sequence
	pict->runAction(RepeatForever::create(seq));//对Sequence的重复
}

void Second::OnReverse(Ref* pSender)//反动作
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 p = Vec2(visibleSize.width / 2, 300);
	pict->setRotation(0);
	pict->setPosition(p);

	auto ac1 = (FiniteTimeAction*)pict->runAction(MoveBy::create(1, Vec2(50, 300)));
	auto ac2 = ac1->reverse();
	auto seq = Sequence::create(ac1, ac2, NULL);
	pict->runAction(Repeat::create(seq, 2));
}*/