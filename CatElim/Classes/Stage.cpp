#include "Stage.h"
#include "SelectScene.h"
#include "GameOver.h"
#include "GameScene.h"

#include "SimpleAudioEngine.h"
#include "math.h"
using namespace CocosDenshion;
USING_NS_CC;

int Stage::tag[9][9] = { 0 };
int Stage::score = 0;              //初始化分数
int Stage::number = 10;

bool Stage::init()
{
	if (!Layer ::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Stage::score = 0;  //退出一关后分数重置为零
	Stage::number = 10;

	scoreLb = Label::createWithTTF("0", "fonts/arial.ttf", 90);   //初始化分数标签
	scoreLb->setPosition(visibleSize.width / 2, visibleSize.height - 70);
	this->addChild(scoreLb, 1);
	if (SelectScene::flag == 1) {
		changeLb = Label::createWithTTF("0", "fonts/arial.ttf", 90);  //初始化步骤标签
		changeLb->setPosition(visibleSize.width / 2, visibleSize.height - 150);
		this->addChild(changeLb, 1);
	}
	if (SelectScene::flag == 2|| SelectScene::flag == 3) {
		start_time = GetCurrentTime();
		Qlabel = Label::createWithTTF("0:0:0", "fonts/arial.ttf", 90);
		Qlabel->setPosition(visibleSize.width / 2, visibleSize.height - 150);
		Qlabel->setOpacity(50);
		scheduleUpdate();
		this->addChild(Qlabel, 1);
	}
	
	srand((unsigned int)time(0));  //确保initMap中的随机数不重复
	ifDelectSwap = true;
	initMap();
	
	updateAnimal(0);

	return true;
}
long long Stage::GetCurrentTime()
{
	struct timeval vt;
	gettimeofday(&vt, NULL);
	long long time = (long long)vt.tv_sec * 1000 + vt.tv_usec / 1000;

	return time;
}
void Stage::update(float dt)
{
	now_time = GetCurrentTime();
	char *mtime = new char[15];
	sprintf(mtime, "%lld:%lld:%lld", (now_time - start_time) / 1000 / 60, (now_time - start_time) / 1000 % 60, (now_time - start_time) % 1000);
	Qlabel->setString(mtime);
}
//图片生成：
void Stage::initMap()
{
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			if (tag[i][j] == -1)
				continue;
			tag[i][j] = rand() % 6 + 1;
			switch (tag[i][j])
			{
			case 1:animal[i][j] = Sprite::create("1.png");
				break;
			case 2:animal[i][j] = Sprite::create("2.png");
				break;
			case 3:animal[i][j] = Sprite::create("3.png");
				break;
			case 4:animal[i][j] = Sprite::create("4.png");
				break;
			case 5:animal[i][j] = Sprite::create("5.png");
				break;
			case 6:animal[i][j] = Sprite::create("6.png");
				break;
			}
			animal[i][j]->setPosition(Vec2(120 * j, 1500 - 120 * i));
			this->addChild(animal[i][j], 0);
		}
	}
}
//选中图片：
void Stage::selectFirst(int x, int y)
{
	animal[x][y]->setOpacity(50);    //选中图片改变透明度
}
//选中图片恢复透明度：
void Stage::removeSelectFirst(int x, int y)
{
	animal[x][y]->setOpacity(255);   
}
//坐标交换（游戏进行步骤）：
void Stage::swap(int x_1, int y_1, int x_2, int y_2)
{
	x1 = x_1;
	y1 = y_1;
	x2 = x_2;
	y2 = y_2;
	swapAnimal();
	
	ifDelectSwap = false;
	scheduleOnce(schedule_selector(Stage::updateAnimal), 0.25f);  //计时器，延长0.25秒进行消除，增强游戏效果
}
//计算分数
void Stage::nowScore(int length)  
{
	score += pow(2, length - 1);
	char count[20];
	sprintf(count, "%d", score);
	scoreLb->setString(count);

	if (SelectScene::flag == 1) {       //第一关分数
		char Ncount[20];
		sprintf(Ncount, "%d", number);
		changeLb->setString(Ncount);
	}
}

void Stage::updateAnimal(float dt)
{
	for (int i = 1; i <= 8;i++) {
		for (int j = 1; j <= 8; j++) {
			if (removeAnimal(i, j)) {         //消除成功，ifDelectSwap值为真
				ifDelectSwap = true;
			}
		}
	}
	fillAnimal();   
	
	if (ifDelectSwap == true) {              //只有ifDelectSwap值为假是，才将图片换回原位
		scheduleOnce(schedule_selector(Stage::updateAnimal), 0.3f);
	}      
	if (ifDelectSwap == false)
		swapAnimal();
}

//图片交换：
void Stage::swapAnimal()
{
	int dir;
	if (y1 == y2){          //dir=1为纵坐标相同，左右图片交换
		dir = 1;
		if (x1 > x2)
			std::swap(x1, x2);
	}else{                  //dir=2为横坐标相同，上下图片交换
		dir = 2;
		if (y1 > y2)
			std::swap(y1, y2);
	}
	if (dir == 1){
		auto move1 = MoveBy::create(0.25f, Vec2(0, -120));  //120为相邻图片之间的像素距离
		auto move2 = MoveBy::create(0.25f, Vec2(0, 120));
		animal[x1][y1]->runAction(move1);
		animal[x2][y2]->runAction(move2);
		std::swap(animal[x1][y1], animal[x2][y2]);  //关键：图片交换后坐标还原
		std::swap(tag[x1][y1], tag[x2][y2]);
	}else {
		auto move1 = MoveBy::create(0.25f, Vec2(120, 0));
		auto move2 = MoveBy::create(0.25f, Vec2(-120, 0));
		animal[x1][y1]->runAction(move1);
		animal[x2][y2]->runAction(move2);
		std::swap(animal[x1][y1], animal[x2][y2]); 
		std::swap(tag[x1][y1], tag[x2][y2]);
	}	
}
//游戏核心：相同图片进行消除
bool Stage::removeAnimal(int x, int y)
{
	if (tag[x][y] == 0 || tag[x][y]==-1) //坐标点为零不执行函数
		return false;

	int up = 0, down = 0, left = 0, right = 0, i, j;
	j = y;   //上
	i = x - 1;
	while (i >= 1) {
		if (tag[i][j] == tag[x][y])  //当两张图片相同时，up++
			up++;
		else
			break;
		i--;                  //横坐标恢复为零
	}
	j = y;  //下
	i = x + 1;
	while (i <= 8) {
		if (tag[i][j] == tag[x][y])
			down++;
		else
			break;
		i++;
	}
	i = x;  //左
	j = y - 1;
	while (j >= 1) {
		if (tag[i][j] == tag[x][y])
			left++;
		else
			break;
		j--;
	}

	i = x;  //右
	j = y + 1;
	while (j <= 8) {
		if (tag[i][j] == tag[x][y])
			right++;
		else
			break;
		j++;
	}
	//消除：当上下左右有两个以上相同图片时进行消除
	if (up + down >= 2 && left + right >= 2) {
		if (GameScene::touchflag)
		{
			number--;
			GameScene::touchflag = 0;
		}	
		for (i = x, j = y - left; j <= y + right; j++) {
			nowScore(left + right);   //记录分数
			removeAnimaLFromPoint(i, j);
		}
		for (i = x - up, j = y; i <= x + down; i++) {
			if (i == x)
				continue;
			nowScore(up + down);
			removeAnimaLFromPoint(i, j);
		}
		return true;       //消除成功
	}
	else if (up + down >= 2) {
		if (GameScene::touchflag)
		{
			number--;
			GameScene::touchflag = 0;
		}
		for (i = x - up, j = y; i <= x + down; i++) {
			nowScore(up + down);
			removeAnimaLFromPoint(i, j);
		}
		return true;
	}
	else if (left + right >= 2) {
		if (GameScene::touchflag)
		{
			number--;
			GameScene::touchflag = 0;
		}
		for (i = x, j = y - left; j <= y + right; j++) {
			nowScore(left + right);
			removeAnimaLFromPoint(i, j);
		}
		return true;
	}
	return false;     //消除失败
}
//消除图片：
void Stage::removeAnimaLFromPoint(int x, int y)
{
	tag[x][y] = 0;                          //坐标消除
	animal[x][y]->removeFromParent();       //图片消除
}

//从上面向下掉图片
void Stage::fillAnimal()  
{
	haveRemoveToUp();
	while (haveTag()){
		initAnimal();
		haveRemoveToUp();
	}
}

//掉图片具体步骤
void  Stage::haveRemoveToUp()  
{
	for (int i = 8; i > 1; i--) {      //从左下角开始tag[8][1]开始遍历
		for (int j = 1; j <= 8; j++) {
			if (tag[i][j] == 0) {
				int k = i - 1;
				for (; k >= 1; k--) {
					if (tag[k][j] != 0 && tag[k][j] != -1)  //格子未被消除或不为空才可进行补充
						break;
				}
				if (k >= 1) {
					moveDown(k, j, i - k);
					std::swap(animal[i][j], animal[k][j]);
					std::swap(tag[i][j], tag[k][j]);
				}
			}
		}
	}
}

//cnt表示掉多少个格子
void  Stage::moveDown(int i, int j, int cnt)     
{
	auto move = MoveBy::create(0.3f, Vec2(0, -120 * cnt));
	animal[i][j]->runAction(move);
}

void Stage::initAnimal() 
{
	int flag[9] = { 0 };
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (tag[i][j] == 0 && flag[j] == 0) {
				initAnimalFromPoint(i, j);
				flag[j] = 1;
			}
		}
	}
}

bool Stage::haveTag()
{
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (tag[i][j] == 0)
				return true;
		}
	}
	return false;
}

void Stage::initAnimalFromPoint(int x, int y)
{
	tag[x][y] = rand() % 6 + 1;
	switch (tag[x][y])
	{
	case 1:animal[x][y] = Sprite::create("1.png");
		break;
	case 2:animal[x][y] = Sprite::create("2.png");
		break;
	case 3:animal[x][y] = Sprite::create("3.png");
		break;
	case 4:animal[x][y] = Sprite::create("4.png");
		break;
	case 5:animal[x][y] = Sprite::create("5.png");
		break;
	case 6:animal[x][y] = Sprite::create("6.png");
		break;
	}
	animal[x][y]->setPosition(Vec2(120 * y, 1500 - 120 * x));
	this->addChild(animal[x][y], 0);
}
