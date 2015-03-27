/****************************************************************************
 for cocos2d-x 2.2.3

 author : LuoYu
 
 e-mail : 466474482@qq.com

 github : https://github.com/bluesky466/cocos2dxUsefulClasses
 ****************************************************************************/

#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include "cocos2d.h"

enum JoystickEventType{
	JET_TOUCH_BEGIN,
	JET_TOUCH_MOVE,
	JET_TOUCH_END
};

class Joystick;

//interval��ʱ����,�����x��y�ķ�Χ����0-1.0F,JoystickEventType�����ͣ���ʼ,�ƶ�,������
typedef void (cocos2d::CCObject::*SEL_JoystickEvent)(Joystick*,float interval,float x, float y,JoystickEventType type);
#define joystickEvent_selector(_SELECTOR) (SEL_JoystickEvent)(&_SELECTOR)

///������ҡ���ⲿ��ʱ��Ļص�����������ûص�����true,���Ժ󽫼�������JET_TOUCH_BEGIN,JET_TOUCH_MOVE��JET_TOUCH_END��Ϣ
typedef bool (cocos2d::CCObject::*SEL_TouchOutsideHandleEvent)(Joystick*,const cocos2d::CCPoint&);
#define touchOutsideHandleEvent_selector(_SELECTOR) (SEL_TouchOutsideHandleEvent)(&_SELECTOR)

/**
 * @brief һ������ҡ����
 *
 * ���ݸ�,�����Ͱ�ť�����Ǿ�����,���ǵ�ê��һֱ����ccp(0.5,0.5)
 * ������setHandleEventListener��������ҡ��ҡ���¼��Ĵ���
 */
class Joystick : public cocos2d::CCNode,public cocos2d::CCTargetedTouchDelegate
{
public:
	Joystick():m_bMove(false){}
	virtual ~Joystick(){}

	/**
	 * ����һ��ҡ��ʵ���ľ�̬����
	 *@param fnBg ����ͼƬ���ļ���,��������ҡ�˵ĵ��̾���
	 *@param bgRadius ҡ�˵ĵ��̵İ뾶
	 *@param fnHandle ҡ��ͼƬ���ļ���,��������ҡ�˾���
	 *@param handleRadius ҡ�˵İ뾶
	 */
	static Joystick* create(const char *fnBg,     float bgRadius,
					        const char *fnHandle, float handleRadius);

	bool init(const char *fnBg,     float bgRadius,
			  const char *fnHandle, float handleRadius);

	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	void onEnter();
	void onExit();

	///����ҡ���ƶ�ʱҪ���õķ������������������Ϊvoid f��float interval, float x, float y��,interval��ʱ�����������x��y�ķ�Χ����0-1.0F
	void setHandleEventListener(cocos2d::CCObject *target, SEL_JoystickEvent selector);

	///������ҡ���ⲿ��ʱ��Ļص�����������ûص�����true,���Ժ󽫼�������JET_TOUCH_BEGIN,JET_TOUCH_MOVE��JET_TOUCH_END��Ϣ
	void setTouchOutsideHandleEventListener(cocos2d::CCObject *target, SEL_TouchOutsideHandleEvent selector);

	///�������ÿһ֡��������,���������ҡ���¼��Ĵ���Ļ���������ĸ�������
	void callHandleEvent(float interval);
protected:
	cocos2d::CCSprite* m_bg;        ///<���̵ľ���
	cocos2d::CCSprite* m_handle;    ///<ҡ�˵ľ���

	float m_bgRadius;               ///<���̵İ뾶
	float m_handleRadius;           ///<ҡ�˵İ뾶
	bool  m_bMove;		            ///<ҡ���Ƿ������ƶ�

	cocos2d::CCPoint m_handlePos;   ///<ҡ���ڵ�������ϵ������
	
	cocos2d::CCObject*  m_touchEventListener;
    SEL_JoystickEvent   m_touchEventSelector;

	cocos2d::CCObject*  m_outsideEventListener;
    SEL_TouchOutsideHandleEvent  m_outsideEventSelector;

	void setHandlePosition(const cocos2d::CCPoint& position);
};

inline void Joystick::setHandleEventListener(cocos2d::CCObject *target, SEL_JoystickEvent selector)
{
	m_touchEventListener = target;
	m_touchEventSelector = selector;
}

inline void Joystick::setTouchOutsideHandleEventListener(cocos2d::CCObject *target, SEL_TouchOutsideHandleEvent selector)
{
	m_outsideEventListener = target;
	m_outsideEventSelector = selector;
}

#endif