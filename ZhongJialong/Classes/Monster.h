#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d;

class Monster :public Node {
public:
	Monster();//构造函数
	Sprite* sprite;
	bool isEmerge;//是否处于屏幕的标识
};

#endif // __HELLOWORLD_SCENE_H__

