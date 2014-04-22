#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
//��ʶ̰ʳ�ߵ��ƶ�����
typedef enum {
	UP=1,
	DOWN,
	LEFT,
	RIGHT
}DIR_DEF;

//����ÿһ����Ԫ�ص����ԣ������������У��У��ƶ�����
class SnakeNode :public cocos2d::Ref{
public:
	int row;//��
	int col;//��
	int dir;//����
};

//��Ϸ���˵�����
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();//�������˵�����ĳ���
	virtual bool init();  //��ʼ������
	//�˵������¼�
    void menuCloseCallback(Ref* pSender);
	void menuStartCallback(Ref* pSender);
	void menuHelpCallback(Ref* pSender);
    
    CREATE_FUNC(HelloWorld);
};

//��Ϸ��������
class GameHelp :public cocos2d::Layer
{
public :
	virtual bool init();//��ʼ��
	//��ť�¼�����
	void menuGoGameCallback(Ref* pSender);
	void menuGoMainCallback(Ref* pSender);
	static cocos2d::Scene * createScene();//������������
	CREATE_FUNC(GameHelp);
};

//��Ϸ����
class GameLayer :public cocos2d::Layer
{
protected:
	SnakeNode *sHead;  //�����߶���
	SnakeNode *sFood;  //ʳ�����
	cocos2d::Vector<Ref*> allBody;//�ߵ�����
	cocos2d::Texture2D * chead;
public :
	virtual bool init();//��ʼ��

	virtual void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;

	//���������¼�
	bool onTouchBegan(cocos2d::Touch* touch, Event  *event);
	
	void timesthing(float t);//��ʱ�¼�
	static cocos2d::Scene * createScene();//������Ϸ����
	CREATE_FUNC(GameLayer);
};



#endif // __HELLOWORLD_SCENE_H__
