#ifndef _TEST_SCROLLING_BACKGROUND_H_
#define _TEST_SCROLLING_BACKGROUND_H_

#include "cocos2d.h"
#include "TestBase.h"
#include "ScrollingBackground.h"

/**
 * SpriteBackground�����ʾdemo
 * ������ģʽ,ѭ�������Ͷ�������
 * ���������Ĳ������� void okCallback(CCObject*) ������е�,ע�⿴����
 * setBgSpriteScrollBy �� setFullScreen ����û��������ʾ,��������������Ҳ�ܼ�,����ע�;ͻ�����
 */
class TestScrollingBackground : public TestBase
{
public:
    virtual bool init();  

	///�����ǲ˵�������,���ÿ�
	void createInitMenu();//����ѡ��
	void dirChangeCallback(cocos2d::Ref*);

	///ģʽѡ��,ѭ������ģʽ�ͱ߹����߶�������ģʽ
	void modeChangeCallback(cocos2d::Ref*);

	void toggleCallback(cocos2d::Ref*);

	///ȷ��ѡ��ť,���������Ĳ��������������
	void okCallback(cocos2d::Ref*);

	///���ذ�ť,����ѡ�����ģʽ
	void btBackCallback(cocos2d::Ref*);

	///�������¸���������ϸ�����
	void nextBgCallback(cocos2d::Ref*);

	///��ͣ�Ϳ�ʼ
	void pauseCallback(cocos2d::Ref*);

	//���ñ������������
	void reverseCallback(cocos2d::Ref*);

	///���Ӿ��鱳��
	void addBgSpriteCallback(cocos2d::Ref*);

	///ѭ��ģʽ����һ�����������뿪��Ļ��ʱ�����
	void loopBgChangeCallback(cocos2d::Sprite* current,cocos2d::Sprite* follow,cocos2d::Sprite* leave);
	
	///����ģʽ����һ�����������뿪��Ļ��ʱ�����
	void dropBgChangeCallback(cocos2d::Sprite* current,cocos2d::Sprite* follow,cocos2d::Sprite* leave);

	///ÿһ֡�����ƶ���ʱ�����
	void bgMoveCallback(cocos2d::Sprite* current,cocos2d::Sprite* follow);
	
    CREATE_FUNC(TestScrollingBackground);
    CREATE_SCENE(TestScrollingBackground);

private:
	bool m_isRunning;

	ScrollingBackground* m_bg;
	ScrollDirection      m_direction;

	//��ʼ�ķ����ģʽѡ��˵�
	cocos2d::Layer*          m_setLayer;
	cocos2d::MenuItemToggle* m_dirSelItem;
	cocos2d::MenuItemToggle* m_modeSelItem;

	//��������֮��Ĳ˵�
	cocos2d::Layer*   m_runLayer;
	cocos2d::Label*   m_itemTipsLabel; ///<itemλ����ʾ
	cocos2d::Label*   m_addTipsLabel;  ///<���ӱ����Ƿ�ɹ�����ʾ
	cocos2d::Label*   m_numBgLabel;	   ///<������Ŀ����ʾ
	cocos2d::Sprite*  m_bgSprite;      ///<��ǰ���鱳��
	cocos2d::Sprite*  m_pItem;         ///<һ������,ע���������Ǳ��������child,ֻ�������汳����������,����HelloWorld��child
	float	 m_velocity;

	//���ӱ�������
	bool addBgSprite(int index);

	//����������ʾ
	void setTextTips(cocos2d::Sprite* bgSprite);
};

#endif
