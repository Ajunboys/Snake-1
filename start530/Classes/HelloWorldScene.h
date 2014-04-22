#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

//ö������DIR_DEF���ֱ��ʶ̰ʳ�ߵ��ƶ�����
typedef enum {
	UP=1,
	DOWN,
	LEFT,
	RIGHT
}DIR_DEF;

//��ÿ���ڵ㶼���Լ����ƶ�������ˣ��ڽڵ���SnakeNode�Ķ����а������С��кͷ���3����Ա
class SnakeNode :public cocos2d::Ref
{
public:
	int row;//��
	int col;//��
	int dir;//����
};

//��Ϸ��ӭ���棬�����Һ����
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();//��ȡ��ӭ�����Scene
    virtual bool init();  
	virtual void onEnter();
	virtual void onExit();
    
    CREATE_FUNC(HelloWorld);
};

//��Ϸ��������
class GameHelp :public cocos2d::Layer
{
public :
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	static cocos2d::Scene * createScene();//��ȡ��������
	CREATE_FUNC(GameHelp);
};

//��Ϸ����
class GameLayer :public cocos2d::Layer
{
public :
	static cocos2d::Scene * createScene();//��ȡ��Ϸ����
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	virtual void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;//ʵ�ֵ�ǰLayer�Ķ���

	void onAcceleration(Acceleration* acc, Event* event);//�����¼��Ļص�
	
	void logic01(float t);//update�Ļص�
	
	CREATE_FUNC(GameLayer);

protected:
	SnakeNode *sHead;  //̰ʳ��px py
	SnakeNode *sFood;  //ʳ��
	cocos2d::Vector<Ref*> allBody;//�ߵ�����
//	cocos2d::Texture2D * chead;
};


#endif // __HELLOWORLD_SCENE_H__
