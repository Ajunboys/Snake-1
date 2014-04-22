#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

const unsigned int LEN = 32;

#pragma warning(once:4996)

#include "cocos2d.h"



enum eMenuTag
{
    eStart = 1,
    eHelp,
    eExit,
    eClose,
};

typedef enum {
    UP = 1,
    DOWN,
    LEFT,
    RIGHT
}DIR_DEF;

class SnakeNode : public cocos2d::CCObject{
public:
    int row;
    int col;
    int dir;
};

//��Ϸ��ӭ����
class HelloWorld : public cocos2d::CCLayer
{
public:
    CREATE_FUNC(HelloWorld);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    static cocos2d::CCScene* scene();//��ȡ��ӭ�����Scene
    void menuCloseCallback(cocos2d::CCObject* pSender);    
};

//��Ϸ��������
class GameHelp : public cocos2d::CCLayer{
public:
    CREATE_FUNC(GameHelp);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    static cocos2d::CCScene * scene();//��ȡ��������
    void menuBackToMain(cocos2d::CCObject *pSender);//�������˵�    
};

//��Ϸ����
class GameLayer : public cocos2d::CCLayer{
public:
    CREATE_FUNC(GameLayer);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    static cocos2d::CCScene * scene();//��ȡ��Ϸ����
    void menuBackToMain(cocos2d::CCObject *pSender);//�������˵�
    //virtual void draw();//ʵ�ֵ�ǰLayer�Ķ���
    virtual void draw(cocos2d::Renderer *renderer, const kmMat4& transform, bool transformUpdated);
    //virtual void registerWithTouchDispatcher(void);
    virtual bool onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void onTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void onTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void logic01(float t);    
protected:
    SnakeNode *sHead;  //̰ʳ��px py
    SnakeNode *sFood;  //ʳ��
    cocos2d::CCArray * allBody;//�ߵ�����
    cocos2d::CCTexture2D * chead;
    unsigned char m_line; //�����ε������ж�������
    unsigned int m_len; //����ı߳�
};

#endif  // __HELLOWORLD_SCENE_H__
