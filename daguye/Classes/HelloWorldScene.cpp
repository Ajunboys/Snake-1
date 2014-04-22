#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);

	return scene;
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//�ڽ�������Ӳ˵�����

	//��ӹرճ���ť
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",//Ĭ����ʾͼƬ
		"CloseSelected.png",//���������ʾͼƬ
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));//�󶨵���¼�

	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));//�趨��ʾλ��Ϊ��Ļ���-�ؼ�������һ�롣Ҳ������ʾ�����½�


	//��ӿ�ʼ��ť
	auto startMenu = MenuItemImage::create(
		"btn_start.png",
		"btn_start.png",
		CC_CALLBACK_1(HelloWorld::menuStartCallback, this));

	startMenu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 50));

	//��Ӱ�����ť
	auto helpMenu = MenuItemImage::create(
		"btn_help.png",
		"btn_help.png",
		CC_CALLBACK_1(HelloWorld::menuHelpCallback, this));

	helpMenu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//����˳���ť
	auto exitMenu = MenuItemImage::create(
		"btn_exit.png",
		"btn_exit.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	exitMenu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 50));


	//�����˵����壬������Ĳ˵����ݶ���ӵ�������
	auto pMenu = Menu::create(startMenu, helpMenu, exitMenu, closeItem, NULL);//����ƶ��Ĳ˵���
	pMenu->setPosition(Point::ZERO);//������ʾλ��
	this->addChild(pMenu, 1);//��ӵ�������


	//�ƶ���Ϸ����
	auto sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	//------------------------

	return true;
}


//�˳���ť�¼�
void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Director::getInstance()->replaceScene(GameHelp::createScene());
	Director::getInstance()->end();
}
//��ʼ��Ϸ��ť�¼�
void HelloWorld::menuStartCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameLayer::createScene());
	//Director::getInstance()->end();
}
//������ť�¼�
void HelloWorld::menuHelpCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameHelp::createScene());
	//Director::getInstance()->end();
}




bool GameHelp::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	//����˳���ť
	auto gotogameMenu = MenuItemImage::create(
		"btn_gotogame.png",
		"btn_gotogame.png",
		CC_CALLBACK_1(GameHelp::menuGoGameCallback, this));

	gotogameMenu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto goMainMenu = MenuItemImage::create(
		"btn_gomain.png",
		"btn_gomain.png",
		CC_CALLBACK_1(GameHelp::menuGoMainCallback, this));

	goMainMenu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 50));

	auto pMenu = Menu::create(gotogameMenu, goMainMenu, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu, 1);

	auto sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);
	return true;
}
//������ť�¼�
void GameHelp::menuGoGameCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(GameLayer::createScene());
}

//������ť�¼�
void GameHelp::menuGoMainCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}



//��ȡ��������
Scene * GameHelp::createScene()
{
	auto scene = Scene::create();
	auto hl = GameHelp::create();
	scene->addChild(hl);
	return scene;
}

int isfirst = 0;
//��ʼ����Ϸ��
bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();


	auto goMainMenu = MenuItemImage::create(
		"btn_gomain.png",
		"btn_gomain.png",
		[](Ref* sender){
			Director::getInstance()->replaceScene(HelloWorld::createScene());
		});

	goMainMenu->setPosition(Point(origin.x + visibleSize.width - goMainMenu->getContentSize().width / 2,
		origin.y +visibleSize.height + goMainMenu->getContentSize().height / 2));

	auto pMenu = Menu::create(goMainMenu, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu, 1);


	auto labhelp = LabelTTF::create("this is game", "Arial", 15);
	labhelp->setPosition(Point(visibleSize.width + origin.x, visibleSize.height + origin.y));
	this->addChild(labhelp);

	auto labback = LabelTTF::create("MainMenu", "Arial", 15);
	auto miback = MenuItemLabel::create(labback, [](Ref* sender)
	{
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	});
	miback->setPosition(Point(visibleSize.width + origin.x - miback->getContentSize().width / 2, visibleSize.height + origin.y - miback->getContentSize().height / 2));

	this->addChild(miback);



	chead = ::CCTextureCache::sharedTextureCache()->addImage("head.png");
	//���������¼�
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);//ָ�������Ļص�����    
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//��listener�����¼�ί����  

	//��ʼ����ͷ�����ʳ�������
	sHead = new SnakeNode();
	sHead->row = rand() % 10;
	sHead->col = rand() % 10;

	//��ʼ��ʳ�������
	sFood = new SnakeNode();
	sFood->row = rand() % 10;
	sFood->col = rand() % 10;


	//ִ�ж�ʱ�¼�
	this->schedule(schedule_selector(GameLayer::timesthing), 0.5);
	return true;
}

//������Ϸ����
Scene * GameLayer::createScene()
{
	auto scene = Scene::create();
	auto hl = GameLayer::create();
	scene->addChild(hl);
	return scene;

}



void GameLayer::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	///������״
	::glLineWidth(2);//�趨���ߵĿ��
	for (int i = 0; i < 11; i++)
	{
		DrawPrimitives::drawLine(Point(0, i * 32), Point(320, i * 32));//����������
		DrawPrimitives::drawLine(Point(i * 32, 0), Point(i * 32, 320));//����������
	}


	//������ͷ
	DrawPrimitives::drawSolidRect(Point(sHead->col * 32 + 2, sHead->row * 32 + 2),
		Point(sHead->col * 32 + 32, sHead->row * 32 + 32),
		Color4F(Color3B(255, 0, 0)));

	//����ʳ��
	DrawPrimitives::drawSolidRect(Point(sFood->col * 32 + 2, sFood->row * 32 + 2),
		Point(sFood->col * 32 + 32, sFood->row * 32 + 32),
		Color4F(Color3B(0, 0, 255)));

	//��������
	for (int i = 0; i < allBody.size(); i++)
	{
		SnakeNode * node = (SnakeNode *)allBody.at(i);
		DrawPrimitives::drawSolidRect(Point(node->col * 32 + 2, node->row * 32 + 2),
			Point(node->col * 32 + 32, node->row * 32 + 32),
			Color4F(Color3B(0, 0, 255)));
	}

}

bool GameLayer::onTouchBegan(Touch* touch, Event  *event)
{
	auto p = touch->getLocation();

	int nowrow;	//��ǰ�û���������
	nowrow = ((int)p.y) / 32;
	int nowcol;	//��ǰ�û���������
	nowcol = ((int)p.x) / 32;

	if (abs(nowrow - sHead->row) > abs(nowcol - sHead->col)) //�����ƶ�
	{
		if (nowrow > sHead->row)
		{
			sHead->dir = DIR_DEF::UP;
		}
		else
		{
			sHead->dir = DIR_DEF::DOWN;
		}

	}
	else    //�����ƶ�
	{
		if (nowcol > sHead->col)
		{
			sHead->dir = DIR_DEF::RIGHT;
		}
		else
		{
			sHead->dir = DIR_DEF::LEFT;
		}
	}
	CCLOG("rand %d", rand());
	CCLOG("you touchbegan%f,%f", p.x, p.y);

	return true;
}



//��ʱ���ص�
void GameLayer::timesthing(float t)
{
	//�ƶ��ߵ�����
	for (int i = allBody.size() - 1; i >= 0; i--)
	{
		SnakeNode * sn = (SnakeNode *)allBody.at(i);

		if (i > 0)
		{
			SnakeNode * snpre = (SnakeNode *)allBody.at(i - 1);
			sn->dir = snpre->dir;
			sn->row = snpre->row;
			sn->col = snpre->col;
		}
		else if (i == 0)
		{
			//�ƶ���һ���ڵ�
			sn->dir = sHead->dir;
			sn->row = sHead->row;
			sn->col = sHead->col;
		}
	}

	//�ƶ���ͷ
	switch (sHead->dir)
	{
	case DIR_DEF::UP:
		sHead->row++;
		if (sHead->row >= 10)
		{
			sHead->row = 0;
		}
		break;
	case DIR_DEF::DOWN:
		sHead->row--;
		if (sHead->row < 0)
		{
			sHead->row = 9;
		}
		break;
	case DIR_DEF::LEFT:
		sHead->col--;
		if (sHead->col < 0)
		{
			sHead->col = 9;
		}
		break;
	case DIR_DEF::RIGHT:
		sHead->col++;
		if (sHead->col >= 10)
		{
			sHead->col = 0;
		}
		break;
	};

	//��ײ���
	if (sHead->row == sFood->row && sHead->col == sFood->col)
	{
		//ʳ����ʧ
		sFood->row = rand() % 10;
		sFood->col = rand() % 10;

		//������嵽����
		SnakeNode * sn = new SnakeNode();
		SnakeNode * lastNode = NULL;
		if (allBody.size() > 0)
			lastNode = (SnakeNode *)allBody.back();
		else
			lastNode = sHead;

		switch (lastNode->dir)
		{
		case DIR_DEF::UP:
			sn->row = lastNode->row - 1;
			sn->col = lastNode->col;
			break;
		case DIR_DEF::DOWN:
			sn->row = lastNode->row + 1;
			sn->col = lastNode->col;
			break;
		case DIR_DEF::LEFT:
			sn->row = lastNode->row;
			sn->col = lastNode->col + 1;
			break;
		case DIR_DEF::RIGHT:
			sn->row = lastNode->row;
			sn->col = lastNode->col - 1;
			break;
		}
		this->allBody.pushBack(sn);
	}
}

