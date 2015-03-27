#ifndef _TEST_JOYSTICK_H_
#define _TEST_JOYSTICK_H_

#include "cocos2d.h"
#include "Joystick.h"

class TestJoystick : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* createScene();

    bool init();  

	//ҡ���¼�����
	void moveSpr(Joystick* joystick,float interval,float x , float y,JoystickEventType type);

	//������ҡ���ⲿ���¼�������followģʽ�µ�ҡ������,����ûص�����true,���Ժ󽫼�������JET_TOUCH_BEGIN,JET_TOUCH_MOVE��JET_TOUCH_END��Ϣ
	bool touchOutsideHandle(Joystick* joystick,const cocos2d::CCPoint& position);

	void menuItemToggleCallback(CCObject*);

    CREATE_FUNC(TestJoystick);

private:
	cocos2d::CCSprite* m_ball;
	Joystick* m_joystick;
	bool      m_isFollow;
};

#endif
