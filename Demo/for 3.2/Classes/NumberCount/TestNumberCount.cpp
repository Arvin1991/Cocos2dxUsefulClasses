#include "TestNumberCount.h"

USING_NS_CC;
using namespace ui;

bool TestNumberCount::init()
{
    if(!TestBase::init())
    {
        return false;
    }

	MenuItemFont* pIncrease = MenuItemFont::create("increase 20",CC_CALLBACK_1(TestNumberCount::increaseCallback,this));
	pIncrease->setAnchorPoint(Vec2(0.0f,1.0f));
	pIncrease->setPosition(m_visibleOrigin.x,
						   m_visibleOrigin.y + m_visibleSize.height - 0.0f);


	MenuItemFont* pReduce = MenuItemFont::create("reduce 20",CC_CALLBACK_1(TestNumberCount::reduceCallback,this));
	pReduce->setAnchorPoint(Vec2(0.0f,1.0f));
	pReduce->setPosition(m_visibleOrigin.x,
						 m_visibleOrigin.y + m_visibleSize.height - 40.0f);

	MenuItemFont* pGoto = MenuItemFont::create("goto 100",CC_CALLBACK_1(TestNumberCount::gotoCallback,this));
	pGoto->setAnchorPoint(Vec2(0.0f,1.0f));
	pGoto->setPosition(m_visibleOrigin.x,
					   m_visibleOrigin.y + m_visibleSize.height - 80.0f);

	Menu* pMenu = Menu::create(pIncrease,pReduce,pGoto, NULL);
	pMenu->setPosition(Vec2(0.0f,0.0f));
    this->addChild(pMenu, 1);


	LabelAtlas* pNumber = LabelAtlas::create("","NumberCount/number.png",55,84,'0');
	pNumber->setAnchorPoint(Vec2(0.5f,0.0f));
	pNumber->setPosition(m_visibleCenter);

	this->addChild(pNumber);

	m_finishTip = Label::create();
	m_finishTip->setAnchorPoint(Vec2(0.5f,1.0f));
	m_finishTip->setPosition(m_visibleCenter);
	this->addChild(m_finishTip);

	//����Ǵ�cocostudio�����Ļ������NumberCount::setTextAtlas
	m_numberCount.setLabelAtlas(pNumber); 

	//������ÿһ����������ʼ��Ϊ3
	m_numberCount.setNumberDelta(3);

	//�����ֱ仯ʱ��������Ϊ0.1��
	m_numberCount.setTimeDelta(0.1f);

	//�����ֳ�ʼ��Ϊ100
	m_numberCount.setNumber(100,false);

	//��������ֹͣ�仯ʱ��Ļص�
	m_numberCount.setChangeFinishCallback(CC_CALLBACK_1(TestNumberCount::finishCallback,this));

	//����������������10�뵹��ʱ
	//m_numberCount.setNumberDelta(1);
	//m_numberCount.setTimeDelta(1.0f);
	//m_numberCount.setNumber(9,false);
	//m_numberCount.setNumber(0,true);
	//m_numberCount.setChangeFinishCallback(CC_CALLBACK_1(HelloWorld::finishCallback,this));

    return true;
}

void TestNumberCount::increaseCallback(Ref* pSender)
{
	m_numberCount.add(20);
	m_finishTip->setString("");
}

void TestNumberCount::reduceCallback(Ref* pSender)
{
	if(m_numberCount.getNumberTarget()-20>0)
	{
		m_numberCount.add(-20);
		m_finishTip->setString("");
	}
}

void TestNumberCount::gotoCallback(Ref* pSender)
{
	m_numberCount.setNumber(100,true);
	m_finishTip->setString("");
}

void TestNumberCount::finishCallback(int targetNumber)
{
	m_finishTip->setString("finish !");
}