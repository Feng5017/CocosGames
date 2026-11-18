#ifndef __COIN__H__  
#define __COIN__H__  

#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d;

class Coin : public Node {
public:
	Coin();//构造函数
	Sprite* sprite;
	bool isEmerge;//是否处于屏幕的标识
};/**/

#endif  
