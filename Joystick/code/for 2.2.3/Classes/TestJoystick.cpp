#include "TestJoystick.h"

USING_NS_CC;

CCScene* TestJoystick::createScene()
{
	CCScene* scene = CCScene::create();

	TestJoystick* layer = TestJoystick::create();
    scene->addChild(layer);
    return scene;
}


bool TestJoystick::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
  
	m_isFollow = true;
	CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    pSprite->setPosition(ccp(visibleOrigin.x + visibleSize.width / 2.0f,
							 visibleOrigin.y + visibleSize.height / 2.0f));
    this->addChild(pSprite, 0);

	CCMenuItemToggle* toggle = CCMenuItemToggle::createWithTarget(this,
														menu_selector(TestJoystick::menuItemToggleCallback),
														CCMenuItemFont::create("follow"),
														CCMenuItemFont::create("normal"),
														NULL);
	toggle->setAnchorPoint(ccp(0.5f,0.5f));

	this->addChild(CCMenu::create(toggle,NULL),1);


	m_ball = CCSprite::create("ball.png");
	m_ball->setScale(0.5f);
	m_ball->setPosition(ccp(200.0f,200.0f));
	this->addChild(m_ball,2);

	//����ҡ��ʵ
	m_joystick = Joystick::create("joystickBg.png",70.0f,"joystickHandle.png",50.0f);
	m_joystick->setPosition(ccp(70.0f,70.0f));
	m_joystick->setVisible(false);

	//ҡ�˴����¼��Ļص�
	m_joystick->setHandleEventListener(this,joystickEvent_selector(TestJoystick::moveSpr));

	//������ҡ���ⲿ�Ļص�������followģʽ�µ�ҡ�ˣ�����ûص�����true,���Ժ󽫼�������JET_TOUCH_BEGIN,JET_TOUCH_MOVE��JET_TOUCH_END��Ϣ
	m_joystick->setTouchOutsideHandleEventListener(this,touchOutsideHandleEvent_selector(TestJoystick::touchOutsideHandle));
	
	this->addChild(m_joystick,3);

    return true;
}

//ҡ���¼�����
void TestJoystick::moveSpr(Joystick* joystick,float interval,float x , float y,JoystickEventType type)
{
	switch(type)
	{
	case JoystickEventType::JET_TOUCH_BEGIN:
		joystick->setVisible(true);
		break;

	case JoystickEventType::JET_TOUCH_MOVE:
		m_ball->setPosition(ccp(m_ball->getPosition().x + x * 0.5f,
								m_ball->getPosition().y + y * 0.5f));
		break;

	case JoystickEventType::JET_TOUCH_END:
		if(m_isFollow)
			joystick->setVisible(false);
		break;
	}
}


bool TestJoystick::touchOutsideHandle(Joystick* joystick,const cocos2d::CCPoint& position)
{
	//����ûص�����true,���Ժ󽫼�������JET_TOUCH_BEGIN,JET_TOUCH_MOVE��JET_TOUCH_END��Ϣ

	if(m_isFollow)
	{
		joystick->setPosition(position);
		return true;
	}
	else
	{
		return false;
	}
}

void TestJoystick::menuItemToggleCallback(CCObject* item)
{
	if(((CCMenuItemToggle*)item)->getSelectedIndex() == 0)
	{
		m_joystick->setVisible(false);
		m_isFollow = true;
	}
	else
	{
		m_joystick->setPosition(ccp(70,70));
		m_joystick->setVisible(true);
		m_isFollow = false;
	}
}