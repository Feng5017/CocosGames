#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual void initGLContextAttrs();

    virtual bool applicationDidFinishLaunching();//完成游戏启动

    virtual void applicationDidEnterBackground();//进入后台，接电话时暂停游戏

    virtual void applicationWillEnterForeground();//回到前台，挂电话后回到游戏
};

#endif // _APP_DELEGATE_H_

