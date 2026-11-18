#include "SimpleAudioEngine.h"

#include "SuspandLayer.h"

USING_NS_CC;
#include "cocos2d.h"

SuspandLayer::SuspandLayer() {}
SuspandLayer::~SuspandLayer() {}

bool SuspandLayer::init()
{
	if (!Layer::init())
		return false;
	auto visiablesize = Director::getInstance()->getWinSize();
	//»ñÈ¡µ½½ØÆÁµÃµ½µÄÍ¼Æ¬Â·¾¶
	auto bg_name = FileUtils::getInstance()->getWritablePath() + "suspand.png";
	auto spr_bg = Sprite::create(bg_name);
	spr_bg->setPosition(Point(visiablesize.width / 2, visiablesize.height / 2));
	this->addChild(spr_bg);

	//Ìí¼Ó»Ö¸´ÓÎÏ·Âß¼­menu
	auto dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");
	auto btn_label = Label::create();
	btn_label->setString(((__String*)(dictionary->objectForKey("back_game")))->getCString());
	btn_label->setSystemFontSize(40);
	auto start_menu = MenuItemLabel::create(btn_label, CC_CALLBACK_1(SuspandLayer::back_game, this));

	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(ccp(visiablesize.width / 2, visiablesize.height / 2));
	this->addChild(menu);

	return true;

}

void SuspandLayer::back_game(Ref* ref)
{
	//»Ö¸´ÓÎÏ·Âß¼­
	Director::getInstance()->popScene();
}