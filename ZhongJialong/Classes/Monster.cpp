#include "Monster.h"

Monster::Monster() {

	Size visibleSize = Director::sharedDirector()->getVisibleSize();

	sprite = CCSprite::create("monster.png");//使用CloseSelected.png这张图片

	float x = 5 * visibleSize.width / 6 + CCRANDOM_0_1()*visibleSize.width / 6;
	float y = CCRANDOM_0_1()*visibleSize.height + 96;
	sprite->setPosition(ccp(x, y));
	this->addChild(sprite);//添加到舞台

	isEmerge = true;//开始为已经出现状态
}