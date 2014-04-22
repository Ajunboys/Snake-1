#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);

    return scene;
}

void HelloWorld::onEnter()
{
	Layer::onEnter();
	CCLOG("HelloWorld onEnter");
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	
	///�����˵�������Ϸ��Ϸ���������˳���Ϸ�İ�ť
	auto labelstart = LabelTTF::create("startGame","����",24);
	auto labelhelp = LabelTTF::create("GameHelp","����",24);
	auto labelexit = LabelTTF::create("exitGame","����",24);

	//������Ϸ��ť
	auto mi01 = MenuItemLabel::create(labelstart,[](Ref* sender)
	{
		CCLOG("go to game");
		Director::getInstance()->replaceScene(GameLayer::createScene());//��ת����Ϸ����
	});
	mi01->setPosition(Point(100,200)); 

	//������ť
	auto mi02 = MenuItemLabel::create(labelhelp,[](Ref* sender)
	{
		CCLOG("go to help");
		Director::getInstance()->replaceScene(GameHelp::createScene());//��ת����������
	});
	mi02->setPosition(Point(100,150));

	//������Ϸ
	auto mi03 = MenuItemLabel::create(labelexit,[](Ref* sender)
	{
		CCLOG("exit the game");
		Director::getInstance()->end();//�˳���Ϸ
	});
	mi03->setPosition(Point(100,50));
	auto pMenu = Menu::create(mi01,mi02,mi03, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu, 1);

    return true;
}

void HelloWorld::onExit()
{
	CCLOG("HelloWorld onExit");
}



bool GameHelp::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	auto labhelp = LabelTTF::create("please click screen to game","����",15);
	labhelp->setPosition(Point(0,280));
	this->addChild(labhelp);

	auto labback = LabelTTF::create("MainMenu","����",15);
	auto miback = MenuItemLabel::create(labback,[](Ref* sender)
	{
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	});
	miback->setPosition(Point(0,0));

	auto pm = Menu::create(miback,NULL);
	this->addChild(pm);

	return true;
}

//��ȡ��������
Scene * GameHelp::createScene()
{
	auto scene = Scene::create();
	auto hl = GameHelp::create();
	scene->addChild(hl);
	return scene;
}

void GameHelp::onEnter()
{
	Layer::onEnter();
	CCLOG("GameHelp onEnter");
}
void GameHelp::onExit()
{
	CCLOG("GameHelp onExit");
}


//��ʼ����Ϸ��
bool GameLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	auto labhelp = LabelTTF::create("this is game","����",15);
	labhelp->setPosition(Point(0,340));
	this->addChild(labhelp);

	auto labback = LabelTTF::create("MainMenu","����",15);
	auto miback = MenuItemLabel::create(labback,[](Ref* sender)
	{
		Director::getInstance()->replaceScene(HelloWorld::createScene());
	});
	miback->setPosition(Point(360,200));

	//chead=::CCTextureCache::sharedTextureCache()->addImage("head.png");

	//��ʼ����ͷ�����ʳ�������
	sHead = new SnakeNode();
	sHead->row = rand()%10;
	sHead->col = rand()%10;

	//��ʼ��ʳ�������
	sFood = new SnakeNode();
	sFood->row = rand()%10;
	sFood->col = rand()%10;

	//ִ�ж�ʱ����
	this->schedule(schedule_selector(GameLayer::logic01),0.5);
	return true;
}

//��ȡ��Ϸ����
Scene * GameLayer::createScene()
{
	auto scene = Scene::create();
	auto hl = GameLayer::create();
	scene->addChild(hl);
	return scene;
}

void GameLayer::onEnter()
{
	Layer::onEnter();
	CCLOG("GameLayer onEnter");

	Device::setAccelerometerEnabled(true);//���豸��������Ӧ
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::onAcceleration, this));//����һ�����������¼�
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//��listener�ŵ��¼�ί����
}
void GameLayer::onExit()
{
	CCLOG("GameLayer onExit");
}
void GameLayer::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
	///������״
	::glLineWidth(2);//�趨���ߵĿ��
	for(int i=0;i<11;i++)
	{
		DrawPrimitives::drawLine(Point(0,i*32),Point(320,i*32));//����������
		DrawPrimitives::drawLine(Point(i*32,0),Point(i*32,320));//����������
	}

	//                    RGBA
	//DrawPrimitives::drawColor4B(ccc4(255,0,0,255));//�趨���ߵ���ɫ

	//������ͷ
	DrawPrimitives::drawSolidRect(Point(sHead->col*32+2,sHead->row*32+2),
		Point(sHead->col*32+32,sHead->row*32+32),
		Color4F(Color3B(255,0,0)));

	//����ʳ��
	DrawPrimitives::drawSolidRect(Point(sFood->col*32+2,sFood->row*32+2),
		Point(sFood->col*32+32,sFood->row*32+32),
		Color4F(Color3B(0,0,255)));

	//��������
	for(int i=0;i<allBody.size();i++)
	{
		SnakeNode * node=(SnakeNode *)allBody.at(i);
		DrawPrimitives::drawSolidRect(Point(node->col*32+2,node->row*32+2),
		Point(node->col*32+32,node->row*32+32),
		Color4F(Color3B(0,0,255)));
	}

	/*Rect r(340,0,57,57);
	chead->drawInRect(r);
	Layer::draw();*/
}

void GameLayer::onAcceleration(Acceleration* acc, Event* event)
{
	void GameLayer::onAcceleration(Acceleration* acc, Event* event)
	{
		//0.5�ⶫ����΢���˵
		if(acc->x<=-0.5)
		{
			sHead->dir=DIR_DEF::LEFT;
			log("LEFT");
		}
		else if(acc->x>=0.5)
		{
			sHead->dir=DIR_DEF::RIGHT;
			log("RIGHT");
		}
		else if(acc->y<=-0.5)
		{
			sHead->dir=DIR_DEF::DOWN;
			log("DOWN");
		}
		else if(acc->y>=0.5)
		{
			sHead->dir = DIR_DEF::UP;
			log("UP");
		}
		else
		{
			;
		}
	}
}

//��ʱ���ص�
void GameLayer::logic01(float t)
{   
	//�ƶ��ߵ�����
	for(int i = allBody.size()-1; i>=0; i--)
	{ 
		SnakeNode * sn = (SnakeNode *)allBody.at(i);//��ȡ�������ϵ�ĳ���ڵ�
		
		if(i>0) 
		{ 
			//����ýڵ㲻�ǵ�һ���ڵ�,��ô�ýڵ����һ�����������ǰһ��������꣨���ﲻ�ö���ͣ�����ߵĶ�����
			SnakeNode * snpre = (SnakeNode *)allBody.at(i-1);//��ȡǰһ���ڵ�,��ǰһ���ڵ�ķ������괫����ǰ�ڵ�
			sn->dir = snpre->dir;
			sn->row = snpre->row;
			sn->col = snpre->col;
		}
		else if(i==0)
		{
			//���i=0���ǵ�һ���ڵ㣬��ͷ��������Ǹýڵ������
			sn->dir = sHead->dir;
			sn->row = sHead->row;
			sn->col = sHead->col;
		}
	}

	//�ƶ���ͷ,����dir���ж���ͷ���ƶ�����
	switch(sHead->dir)
	{
	case DIR_DEF::UP:
		sHead->row++;//����
		if(sHead->row >= 10)
		{
			sHead->row=0;//���������߽���ӵײ�����
		}
		break;
	case DIR_DEF::DOWN:
		sHead->row--;
		if(sHead->row < 0)
		{
			sHead->row=9;
		}
		break;
	case DIR_DEF::LEFT:
		sHead->col--;
		if(sHead->col < 0)
		{
			sHead->col=9;
		}
		break;
	case DIR_DEF::RIGHT:
		sHead->col++;
		if(sHead->col >= 10)
		{
			sHead->col=0;
		}
		break;
	};  

	//��ײ���
	//�����ͷ�ĺᡢ��λ��һ����˵���߳Ե������ʳ��
	if(sHead->row == sFood->row && sHead->col == sFood->col)
	{ 
		//ʳ��ӵ�ǰλ����ʧ�������������һ������
		sFood->row = rand()%10;
		sFood->col = rand()%10;

		//������嵽����
		SnakeNode * sn = new SnakeNode();//����һ���µĽڵ㣨Ҳ���ǳԵ����Ǹ�ʳ�������ŵ��ߵ�β����
		SnakeNode * lastNode = NULL;
		//��ȡ�ߵ����һ���ڵ㣬���allBody��size()Ϊ0����˵�����ǵ�һ�β�ʳ����ô�������һ���ڵ�Ҳ������ͷ����
		if(allBody.size()>0)
			lastNode = (SnakeNode *)allBody.back();
		else
			lastNode = sHead;//���һ���ڵ�����ͷ

		//ͨ�����һ���ڵ�ķ��������µĽڵ��ʼ���ᡢ������
		switch(lastNode->dir)
		{
		case DIR_DEF::UP:
			sn->row = lastNode->row-1;
			sn->col = lastNode->col;
			break;
		case DIR_DEF::DOWN:
			sn->row = lastNode->row+1;
			sn->col = lastNode->col;
			break;
		case DIR_DEF::LEFT:
			sn->row = lastNode->row;
			sn->col = lastNode->col+1;
			break;
		case DIR_DEF::RIGHT:
			sn->row=lastNode->row;
			sn->col=lastNode->col-1;
			break;
		}
		this->allBody.pushBack(sn);//���µĽڵ���뵽�ߵ������С�
	}
}

