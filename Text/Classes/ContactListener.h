#ifndef __CONTACTLISTENER_H__
#define __CONTACTLISTENER_H__

#include "cocos2d.h"
using namespace cocos2d;

#define MAX_COUNT 100

class ContactListener :public cocos2d::Scene
{
//Array容器法：
	Array* list1;//指针类型的Array成员变量
//Vector容器法：
	Vector<Sprite*> list2;//使用Vector列表容器
//REF字典容器:Dictionary容器方法
	Dictionary* dict1;
	Dictionary* dict2;
//REF字典容器：Map容器法：
	Map<std::string, Sprite*>map1;
	Map<std::string, Sprite*>map2;
//ValueVector容器法:
	ValueVector list3;//对象类型而非对象指针类型
//Value字典：ValueMap容器法
	ValueMap vmap1;
	ValueMap vmap2;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuGoCallback(Ref* pSender);//点击go按钮响应
	void menuCloseCallback(Ref* pSender);

	virtual void onEnter();
	CREATE_FUNC(ContactListener);
	~ContactListener();//增加析构函数，为了解决retain带来的问题
};



#endif // __HELLOWORLD_SCENE_H__
