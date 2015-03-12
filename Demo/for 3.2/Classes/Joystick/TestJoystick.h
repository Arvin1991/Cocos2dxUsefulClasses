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
	void moveSpr(float interval,float x , float y,JoystickEventType type);

    CREATE_FUNC(TestJoystick);
    CREATE_SCENE(TestJoystick);

private:
	cocos2d::Sprite* m_ball;
	cocos2d::Label*  m_label;
};

#endif
