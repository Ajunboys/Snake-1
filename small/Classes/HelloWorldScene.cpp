#include "HelloWorldScene.h"
using namespace cocos2d;



bool HelloWorld::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!CCLayer::init());
        
        ///�����˵�������Ϸ��Ϸ�����˳���Ϸ
        CCLabelTTF * labelstart = CCLabelTTF::create("startGame", "����", 24);
        CCLabelTTF * labelhelp = CCLabelTTF::create("GameHelp", "����", 24);
        CCLabelTTF * labelexit = CCLabelTTF::create("exitGame", "����", 24);
       
        //����˵���Ŀ
        CCMenuItemLabel *mi01 = CCMenuItemLabel::create(labelstart, this, menu_selector(HelloWorld::menuCloseCallback));
        mi01->setTag(eStart);
        mi01->setPosition(ccp(100, 200));
       
        CCMenuItemLabel *mi02 = CCMenuItemLabel::create(labelhelp, this, menu_selector(HelloWorld::menuCloseCallback));
        mi02->setTag(eHelp);
        mi02->setPosition(ccp(100, 150));
        
        CCMenuItemLabel *mi03 = CCMenuItemLabel::create(labelexit, this, menu_selector(HelloWorld::menuCloseCallback));
        mi03->setTag(eExit);
        mi03->setPosition(ccp(100, 50));

        CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, 
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(!pCloseItem);
        pCloseItem->setTag(eClose);
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));
        
        CCMenu* pMenu = CCMenu::create(mi01, mi02, mi03, pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(!pMenu);
        this->addChild(pMenu, 1);
        
        CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
        CC_BREAK_IF(!pLabel);
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        pLabel->setPosition(ccp(size.width / 2, size.height - 50));
        this->addChild(pLabel, 1);

        CCSprite* pSprite = CCSprite::create("HelloWorld.png");
        CC_BREAK_IF(!pSprite);
        pSprite->setPosition(ccp(size.width / 2, size.height / 2));
        this->addChild(pSprite, 0);

        bRet = true;
    } while (0);
    return bRet;
}

void HelloWorld::onEnter(){
    CCLayer::onEnter();
    CCLog("HelloWorld onEnter");
}

void HelloWorld::onExit()
{
    CCLog("HelloWorld onExit");
}

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do
    {
        scene = CCScene::create();
        CC_BREAK_IF(!scene);
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(!layer);
        scene->addChild(layer);
    } while (0);
    return scene;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    switch (((CCNode*)pSender)->getTag())
    {
    case eStart:// ������Ϸ
        CCLog("go to game");
        CCDirector::sharedDirector()->replaceScene(GameLayer::scene());
        break;
    case eHelp://�������
        CCLog("go to help");
        CCDirector::sharedDirector()->replaceScene(GameHelp::scene());
        break;
    case eExit:
    case eClose:
        CCDirector::sharedDirector()->end();
    };
}



bool GameHelp::init(){
    if (!CCLayer::init())
    {
        return false;
    }

    CCLabelTTF * labhelp = CCLabelTTF::create("please click screen to game", "����", 15);
    labhelp->setPosition(ccp(0, 280));
    this->addChild(labhelp);

    CCLabelTTF * labback = CCLabelTTF::create("MainMenu", "����", 15);
    CCMenuItemLabel * miback = CCMenuItemLabel::create(labback, this, menu_selector(GameHelp::menuBackToMain));
    miback->setPosition(ccp(0, 0));
    
    CCMenu * pm = CCMenu::create(miback, NULL);
    this->addChild(pm);
    
    return true;
}

void GameHelp::onEnter()
{
    CCLayer::onEnter();
    CCLog("GameHelp onEnter");
}

void GameHelp::onExit()
{
    CCLog("GameHelp onExit");
}

//��ȡ��������
cocos2d::CCScene* GameHelp::scene()
{
    CCScene* scene = CCScene::create();
    CCLayer* hl = GameHelp::create();
    scene->addChild(hl);
    return scene;
}

void GameHelp::menuBackToMain(CCObject *pSender)//�������˵�
{
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}




bool GameLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }

    //��ȡ��Ļ�ߴ�
    CCSize size = CCDirector::getInstance()->getWinSize();
    unsigned int width = size.width;
    unsigned int heiht = size.height;
    this->m_len = width < heiht ? width : heiht;
    this->m_line = m_len / LEN; //����һ���ܻ���������

    CCLabelTTF * labhelp = CCLabelTTF::create("This is the game", "����", 15);
    labhelp->setPosition(ccp(0, 340));
    this->addChild(labhelp);
    CCLabelTTF * labback = CCLabelTTF::create("MainMenu", "����", 15);
    CCMenuItemLabel * miback = CCMenuItemLabel::create(labback, this, menu_selector(GameLayer::menuBackToMain));
    miback->setPosition(ccp(360, 200));
    
    //chead = ::CCTextureCache::sharedTextureCache()->addImage("HelloWorld.png");
    
    ///���ܴ����¼�
    //this->setTouchEnabled(true);
    //this->setAccelerometerEnabled(true);
    //this->setKeypadEnabled(true);
    //3.0�����¼�
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //��ʼ����ͷ�����ʳ�������
    sHead = new SnakeNode();
    sHead->row = rand() % m_line;
    sHead->col = rand() % m_line;
    //��ʼ��ʳ�������
    sFood = new SnakeNode();
    sFood->row = rand() % m_line;
    sFood->col = rand() % m_line;
    //��ʼ���ߵ�����
    this->allBody = cocos2d::CCArray::create();
    this->allBody->retain();
    //ִ�ж�ʱ����
    this->schedule(schedule_selector(GameLayer::logic01), 0.5);
    return true;
}

void GameLayer::onEnter()
{
    CCLayer::onEnter();
    CCLog("GameLayer onEnter");
}

void GameLayer::onExit()
{
    CCLog("GameLayer onExit");
}

cocos2d::CCScene * GameLayer::scene()
{
    CCScene * scene = CCScene::create();
    CCLayer * hl = GameLayer::create();
    scene->addChild(hl);
    return scene;
}//��ȡ��������

void GameLayer::menuBackToMain(CCObject *pSender)//�������˵�
{
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

void GameLayer::draw(cocos2d::Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
    ///������״
    ::glLineWidth(2);//�趨���ߵĿ��
    for (int i = 0; i <= m_line; ++i)
    {
        ::ccDrawLine(ccp(0, i * LEN), ccp(m_len, i * LEN));//����������
        ::ccDrawLine(ccp(i * LEN, 0), ccp(i * LEN, m_len));//����������
    }
    //                    RGBA
    //::ccDrawColor4B(ccc4(255,0,0,255));//�趨���ߵ���ɫ
    //������ͷ
    ::ccDrawSolidRect(ccp(sHead->col * LEN + 2, sHead->row * LEN + 2),
        ccp(sHead->col * LEN + LEN, sHead->row * LEN + LEN),
        ccc4FFromccc3B(ccc3(255, 0, 0)));
    //����ʳ��
    ::ccDrawSolidRect(ccp(sFood->col * LEN + 2, sFood->row * LEN + 2),
        ccp(sFood->col * LEN + LEN, sFood->row * LEN + LEN),
        ccc4FFromccc3B(ccc3(0, 0, 255)));
    //��������
    for (int i = 0; i < allBody->count(); i++)
    {
        SnakeNode * node = (SnakeNode *)allBody->objectAtIndex(i);
        ::ccDrawSolidRect(ccp(node->col * LEN + 2, node->row * LEN + 2),
            ccp(node->col * LEN + LEN, node->row * LEN + LEN),
            ccc4FFromccc3B(ccc3(0, 0, 255)));
    }
    //CCRect r(340, 0, 57, 57);
    //chead->drawInRect(r);
    CCLayer::draw(renderer, transform, transformUpdated);
}

//void GameLayer::registerWithTouchDispatcher()
//{//    CCDirector::sharedDirector()->getTouchDispatcher()->
//        addTargetedDelegate(this, 1, false);

//}

bool GameLayer::onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    //CCLayer::ccTouchBegan(pTouch,pEvent);
    CCPoint p = pTouch->getLocation();
    int nowrow;//��ǰ�û���������
    nowrow = ((int)p.y) / LEN;
    int nowcol;////��ǰ�û���������
    nowcol = ((int)p.x) / LEN;
    if (::abs(nowrow - sHead->row) > abs(nowcol - sHead->col)) //�����ƶ�
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
    else////�����ƶ�
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
    CCLog("rand %d", rand());
    CCLog("you touchbegan%f,%f", p.x, p.y);
    return true;
}

void GameLayer::onTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    //CCPoint p=pTouch->getLocation();
    //CCLog("you ccTouchMoved%f,%f",p.x,p.y);
}

void GameLayer::onTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    //CCPoint p=pTouch->getLocation();
    //CCLog("you ccTouchEnded%f,%f",p.x,p.y);
}

void GameLayer::logic01(float t)
{
    //�ƶ��ߵ�����
    for (int i = allBody->count() - 1; i >= 0; i--)
    {
        SnakeNode * sn = (SnakeNode *)allBody->objectAtIndex(i);
        if (i > 0)
        {
            SnakeNode * snpre = (SnakeNode *)allBody->objectAtIndex(i - 1);
            sn->dir = snpre->dir;
            sn->row = snpre->row;
            sn->col = snpre->col;
        }
        else if (i == 0)
        {//�ƶ���һ���ڵ�
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
        if (sHead->row > m_line - 1){ sHead->row = 0; }
        break;
    case DIR_DEF::DOWN:
        sHead->row--;
        if (sHead->row < 0){ sHead->row = m_line - 1; }
        break;
    case DIR_DEF::LEFT:
        sHead->col--;
        if (sHead->col < 0){ sHead->col = m_line - 1; }
        break;
    case DIR_DEF::RIGHT:
        sHead->col++;
        if (sHead->col > m_line - 1){ sHead->col = 0; }
        break;
    };
    //��ײ���
    if (sHead->row == sFood->row && sHead->col == sFood->col)
    { //ʳ����ʧ
        sFood->row = rand() % m_line;
        sFood->col = rand() % m_line;
        //������嵽����
        SnakeNode * sn = new SnakeNode();
        SnakeNode *lastNode = NULL;
        if (allBody->count() > 0)
            lastNode = (SnakeNode *)allBody->lastObject();
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
        this->allBody->addObject(sn);
    }
}
