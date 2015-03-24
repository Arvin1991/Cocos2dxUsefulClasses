#ifndef _TEST_JOYSTICK_H_
#define _TEST_JOYSTICK_H_

#include "cocos2d.h"
#include "TestBase.h"
#include "Joystick.h"

class TestJoystick : public TestBase
{
public:
    bool init();  

	//ҡ���¼�����
	void moveSpr(Joystick* joystick,float interval,float x , float y,JoystickEventType type);

	//������ҡ���ⲿ���¼�������followģʽ�µ�ҡ������,����ûص�����true,���Ժ󽫼�������JET_TOUCH_BEGIN,JET_TOUCH_MOVE��JET_TOUCH_END��Ϣ
	bool touchOutsideHandle(Joystick* joystick,const cocos2d::Vec2&);

	
	void menuItemToggleCallback(Ref*);

    CREATE_FUNC(TestJoystick);
    CREATE_SCENE(TestJoystick);

private:
	cocos2d::Sprite* m_ball;
	Joystick* m_joystick;
	bool      m_isFollow;
};

#endif
