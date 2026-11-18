#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "CardSprite.h"

USING_NS_CC;
USING_NS_CC_MATH;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Scene::init()){
        return false;
    }
	Size visibleSize = Director::getInstance()->getVisibleSize();
//加入游戏的背景
	auto background = Sprite::create("bg2.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background);

	auto startMenuItem = MenuItemImage::create("back_on.png", "back_off.png",
		CC_CALLBACK_1(HelloWorld::menuCallback, this));
	startMenuItem->setPosition(Vec2(visibleSize.width / 2, 50));
	auto mn = Menu::create(startMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);

//在上方加入游戏分数
//分数设置
	auto dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");
	score = 0;

	auto labTTFCardNumberName = Label::create();
	labTTFCardNumberName->setString(((__String*)(dictionary->objectForKey("score")))->getCString());
	labTTFCardNumberName->setSystemFontSize(40);
	labTTFCardNumberName->setAnchorPoint(Vec2(0.5, 0.5));
	labTTFCardNumberName->setPosition(Vec2(visibleSize.width / 5 * 3, visibleSize.height - 100));
	this->addChild(labTTFCardNumberName);

	labTTFCardNumber = LabelTTF::create("0", "Arial", 40);
	labTTFCardNumber->setPosition(Vec2(visibleSize.width / 5 * 3, visibleSize.height - 165));
	this->addChild(labTTFCardNumber);

	//最高分
	auto label_best_score = Label::create();
	label_best_score->setString(((__String*)(dictionary->objectForKey("best_score")))->getCString());
	label_best_score->setSystemFontSize(40);
	label_best_score->setPosition(Vec2(visibleSize.width / 5 * 4+20, visibleSize.height - 100));
	this->addChild(label_best_score);
	bestscore = Label::create();
	bestscore->setSystemFontSize(40);
	bestscore->setPosition(Vec2(visibleSize.width / 5 * 4+20, visibleSize.height - 165));
	this->addChild(bestscore);
	//赋值最高分
	int score_win = UserDefault::getInstance()->getIntegerForKey("best_score");
	bestscore->setString(__String::createWithFormat("%d", score_win)->getCString());

	/*susScore = 0;
	susScoreTTF = LabelTTF::create("0", "Arial", 40);
	susScoreTTF->setPosition(Vec2(labTTFCardNumber->getPosition().x, labTTFCardNumber->getPosition().y));
	action1 = CCMoveTo::create(1, ccp(labTTFCardNumber->getPosition().x, labTTFCardNumber->getPosition().y + 50));
	action2 = CCFadeOut::create(2);
	this->addChild(susScoreTTF);*/

	firstX = 0;
	firstY = 0;
	endX = 0;
	endY = 0;

//加入游戏的手势识别监听事件，进行绑定
	auto touchListener = EventListenerTouchOneByOne::create();//创建单点触摸监听事件
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

void HelloWorld::onEnter()
{
	Scene::onEnter();
	Size visibleSize = Director::getInstance()->getVisibleSize();
//调用生成卡片的方法
	createCardSprite(visibleSize);
//调用生成随机数
	autocreateCardNumber();
	autocreateCardNumber();
}

void HelloWorld::onExit()
{	//存储分数变量
	UserDefault::getInstance()->setIntegerForKey("score", score);
	//获得最高分
	int score_win = UserDefault::getInstance()->getIntegerForKey("best_score");
	if (score>score_win){
		UserDefault::getInstance()->setIntegerForKey("best_score", score);
	}

	Scene::onExit();
	/*EventDispatcher *disp = Director::getInstance()->getEventDispatcher();
	disp->removeAllEventListeners();*/
}

//自动生成卡片
void HelloWorld::autocreateCardNumber()
{
	int i = CCRANDOM_0_1() * 4;
	int j = CCRANDOM_0_1() * 4;
	//判断是否已经存在的位置
	if (cardArr[i][j]->getNumber()>0) {
		autocreateCardNumber();//此格子有数，换个格子生成
	}
	else { //按1:9的概率生成数字4和2
		cardArr[i][j]->setNumber(CCRANDOM_0_1() * 10 < 1 ? 4 : 2);
	}
}

bool HelloWorld::onTouchBegan(Touch * touch, Event * event)
{
	Point touchPO = touch->getLocation();
	firstX = touchPO.x;
	firstY = touchPO.y;
	return true;
}

void HelloWorld::onTouchMoved(Touch * touch, Event * event)
{
	Point touchPO = touch->getLocation();
	endX = firstX - touchPO.x;
	endY = firstY - touchPO.y;
	/*log("%d", endX);
	log("%d", endY);*/
}

void HelloWorld::onTouchEnded(Touch * touch, Event * event)
{
//获得X轴和Y轴的移动范围
	Point touchPO = touch->getLocation();
//判断X轴和Y轴的移动距离，如果X轴的绝对值比Y轴的绝对值大就是左右，否则就是上下
	if (abs(endX)>abs(endY)){	//左右
		if (endX + 5 > 0) {		//5只是偏移量，避免误操作
			if (doLeft()) {
				autocreateCardNumber();	//移动的位置再生成一个数
				doCheckGameOver();
			}
		}else {
			if (doRight()) {
				autocreateCardNumber();
				doCheckGameOver();
			}
		}
	}
	else{	 //上下
		if (endY + 5 > 0) {
			if (doDown()) {
				autocreateCardNumber();
				doCheckGameOver();
			}
		}else {
			if (doUp()) {
				autocreateCardNumber();
				doCheckGameOver();
			}
		}			
	}
}

bool HelloWorld::doUp()
{
	log("do up");
	bool isdo = false;//判断代码块有无合并或移动
	for (int x = 0; x < 4; x++) {
		for (int y = 3; y >= 0; y--) {
			for (int y1 = y - 1; y1 >= 0; y1--) {
				if (cardArr[x][y1]->getNumber()>0) {
					if (cardArr[x][y]->getNumber() <= 0) {
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y++;
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber()) {
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);
						//设置分数
						score += cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());
						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
}

bool HelloWorld::doDown()
{
	log("do down");
	bool isdo = false;//判断代码块有无合并或移动
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			for (int y1 = y + 1; y1 < 4; y1++) {
				if (cardArr[x][y1]->getNumber()>0) {
					if (cardArr[x][y]->getNumber() <= 0) {
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y--;
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber()) {
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);
						//设置分数
						score += cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
}

bool HelloWorld::doLeft()//上下左右滑动法
{	log("do left");
	bool isdo = false;//判断代码块有无合并或移动
	for (int y = 0; y < 4; y++) { 
		for (int x = 0; x < 4; x++) {		
			for (int x1 = x + 1; x1 < 4; x1++){
				if (cardArr[x1][y]->getNumber()>0){
					if (cardArr[x][y]->getNumber() <= 0) {
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());//左边的值变为右边的值
						cardArr[x1][y]->setNumber(0);//右边的模块变为
						x--;//依次将数字左移直到左边有个卡片
						isdo = true;
					}else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()) {
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);//左边的卡片合并右边的值
						cardArr[x1][y]->setNumber(0);//右边的模块变为0
						//设置分数
						score += cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i",score)->getCString());
						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
}

bool HelloWorld::doRight()
{
	log("do right");
	bool isdo = false;//判断代码块有无合并或移动
	for (int y = 0; y < 4; y++) {
		for (int x = 3; x >= 0; x--) {

			for (int x1 = x - 1; x1 >= 0; x1--) {
				if (cardArr[x1][y]->getNumber()>0) {
					if (cardArr[x][y]->getNumber() <= 0) {
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x++;
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()) {	
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);
						//设置分数
						score += cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());
						isdo = true;
					}
					break;
				}
			}
		}
	}
	return isdo;
}

void HelloWorld::doCheckGameOver()//游戏是否能运行下去
{
	bool isGameOver = true;

	for (int y = 0; y < 4; y++){
		for (int x = 0; x < 4; x++){
			if (cardArr[x][y]->getNumber() == 0 ||
				(x > 0 && (cardArr[x][y]->getNumber() == cardArr[x - 1][y]->getNumber())) ||
				(x < 3 && (cardArr[x][y]->getNumber() == cardArr[x + 1][y]->getNumber())) ||
				(y > 0 && (cardArr[x][y]->getNumber() == cardArr[x][y - 1]->getNumber())) ||
				(y < 3 && (cardArr[x][y]->getNumber() == cardArr[x][y + 1]->getNumber()))) {
				isGameOver = false;
			}
		}
	}

	if (isGameOver){
		//结束游戏
		Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
	}
}

void HelloWorld::menuCallback(cocos2d::Ref * pSender)
{
	auto sc = GameStart::createScene();
	auto tsc = TransitionFadeBL::create(0.5f, sc);
	Director::getInstance()->replaceScene(tsc);
}

//创建卡片
void HelloWorld::createCardSprite(cocos2d::Size size)
{//求出单元格的宽和高
	int lon = (size.width - 28) / 4;
//4*4的单元格
	for (int j = 0; j < 4; j++){
		for (int i = 0; i < 4; i++){
			CardSprite *card = CardSprite::createCardSprite(0, lon, lon, lon*j + 20, lon*i + 20 + size.height / 7);
			addChild(card);
			//添加卡片到二维数组
			cardArr[j][i] = card;
		}
	}

}
