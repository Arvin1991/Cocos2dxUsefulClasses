#include "TestJoystick.h"

USING_NS_CC;

bool TestJoystick::init()
{
    if(!TestBase::init())
    {
        return false;
    }
  
	m_isFollow = true;

    Sprite* pSprite = Sprite::create("Joystick/HelloWorld.png");
    pSprite->setPosition(Vec2(m_visibleOrigin.x + m_visibleSize.width / 2.0f,
							  m_visibleOrigin.y + m_visibleSize.height / 2.0f));
    this->addChild(pSprite, 0);

	MenuItemToggle* toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(TestJoystick::menuItemToggleCallback,this),
																MenuItemFont::create("follow"),
																MenuItemFont::create("normal"),
																NULL);
	toggle->setAnchorPoint(Vec2(0.5f,0.5f));

	this->addChild(Menu::create(toggle,NULL),1);


	m_ball = CCSprite::create("Joystick/ball.png");
	m_ball->setScale(0.5f);
	m_ball->setPosition(Vec2(200.0f,200.0f));
	this->addChild(m_ball,2);

	//����ҡ��ʵ
	m_joystick = Joystick::create("Joystick/joystickBg.png",70.0f,"Joystick/joystickHandle.png",50.0f);
	m_joystick->setPosition(Vec2(70.0f,70.0f));
	m_joystick->setVisible(false);

	//ҡ�˴����¼��Ļص�
	m_joystick->setHandleEventListener(JOYSTICK_CALLBACK(TestJoystick::moveSpr,this));

	//������ҡ���ⲿ�Ļص�������followģʽ�µ�ҡ�ˣ�����ûص�����true,���Ժ󽫼�������JET_TOUCH_BEGIN,JET_TOUCH_MOVE��JET_TOUCH_END��Ϣ
	m_joystick->setTouchOutsideCallback(CC_CALLBACK_2(TestJoystick::touchOutsideHandle,this));
	
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
		m_ball->setPosition(m_ball->getPosition().x + x * 0.5f,
							m_ball->getPosition().y + y * 0.5f);
		break;

	case JoystickEventType::JET_TOUCH_END:
		if(m_isFollow)
			joystick->setVisible(false);
		break;
	}
}


bool TestJoystick::touchOutsideHandle(Joystick* joystick,const cocos2d::Vec2& position)
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

void TestJoystick::menuItemToggleCallback(Ref* item)
{
	if(((MenuItemToggle*)item)->getSelectedIndex() == 0)
	{
		m_joystick->setVisible(false);
		m_isFollow = true;
	}
	else
	{
		m_joystick->setPosition(Vec2(70,70));
		m_joystick->setVisible(true);
		m_isFollow = false;
	}
}