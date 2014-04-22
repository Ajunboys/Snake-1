#include "BackgroundLayer.h"


BackgroundLayer::BackgroundLayer(void)
{
}


BackgroundLayer::~BackgroundLayer(void)
{
}
bool BackgroundLayer::init(){
	if(!Layer::init())
		return false;
	//��ȡ����
	Size  visibile=Director::getInstance()->getVisibleSize();
	Point  origin=Director::getInstance()->getVisibleOrigin();
	Sprite *background=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.jpg"));
	//����ê�㣬����㣬
	background->setAnchorPoint(Point::ZERO);
	background->setPosition(Point::ZERO);
	this->addChild(background);
	return true;
}