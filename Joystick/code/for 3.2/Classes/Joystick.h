/****************************************************************************
 for cocos2d-x 3.2

 author : LuoYu
 
 e-mail : 466474482@qq.com

 github : https://github.com/bluesky466/cocos2dxUsefulClasses
 ****************************************************************************/

#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include "cocos2d.h"

enum class JoystickEventType{
	JET_TOUCH_BEGIN,
	JET_TOUCH_MOVE,
	JET_TOUCH_END
};

class Joystick;

//interval��ʱ����,�����x��y�ķ�Χ����0-1.0F,JoystickEventType�����ͣ���ʼ,�ƶ�,������
typedef std::function<void(Joystick*,float interval,float x, float y,JoystickEventType type)> JoystickEventCallback;
#define JOYSTICK_CALLBACK(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5, ##__VA_ARGS__)

///������ҡ���ⲿ��ʱ��Ļص�����������ûص�����true,���Ժ󽫼�������JET_TOUCH_BEGIN,JET_TOUCH_MOVE��JET_TOUCH_END��Ϣ
typedef std::function<bool(Joystick*,const cocos2d::Vec2&)> TouchOutsideHandleEvent;

/**
 * @brief һ������ҡ����
 *
 * ���ݸ�,�����Ͱ�ť�����Ǿ�����,���ǵ�ê��һֱ����ccp(0.5,0.5)
 * ������setHandleEventListener��������ҡ��ҡ���¼��Ĵ���
 */
class Joystick : public cocos2d::Node
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

	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	void onTouchCancelled(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

	///����ҡ���ƶ�ʱҪ���õķ������������������Ϊvoid f��float interval, float x, float y��,interval��ʱ�����������x��y�ķ�Χ����0-1.0F
	void setHandleEventListener(const JoystickEventCallback& callback);

	///���ô�����ҡ���ⲿ��ʱ��Ļص�����������ûص�����true,���Ժ󽫼�������JET_TOUCH_BEGIN,JET_TOUCH_MOVE��JET_TOUCH_END��Ϣ
	void setTouchOutsideCallback(const TouchOutsideHandleEvent& callback);

	///�������ÿһ֡��������,���������ҡ���¼��Ĵ���Ļ���������ĸ�������
	void callHandleEvent(float interval);
protected:
	cocos2d::Sprite* m_bg;         ///<���̵ľ���
	cocos2d::Sprite* m_handle;     ///<ҡ�˵ľ���

	float m_bgRadius;              ///<���̵İ뾶
	float m_handleRadius;          ///<ҡ�˵İ뾶
	bool  m_bMove;		           ///<ҡ���Ƿ������ƶ�

	cocos2d::Point m_handlePos;    ///<ҡ���ڵ�������ϵ������
	
	JoystickEventCallback m_touchEventCallback;
	TouchOutsideHandleEvent m_touchOutsideCallback;
	
	void setHandlePosition(const cocos2d::Vec2 position);
};

inline void Joystick::setHandleEventListener(const JoystickEventCallback& callback)
{
	m_touchEventCallback = callback;
}

inline void Joystick::setTouchOutsideCallback(const TouchOutsideHandleEvent& callback)
{
	m_touchOutsideCallback = callback;
}

#endif