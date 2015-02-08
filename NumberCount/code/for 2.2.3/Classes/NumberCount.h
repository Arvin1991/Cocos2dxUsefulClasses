/****************************************************************************
 for cocos2d-x 2.2.3

 author : LuoYu
 
 e-mail : 466474482@qq.com

 github : https://github.com/bluesky466/cocos2dxUsefulClasses
 ****************************************************************************/

#ifndef _NUMBER_COUNT_H_
#define _NUMBER_COUNT_H_

#include "cocos2d.h"
#include "cocos-ext.h"

///����Ŀ�����ֵĻص�
typedef void (cocos2d::CCObject::*SEL_ChangeFinish)(int numberTarget);
#define changeFinish_selector(_SELECTOR) (SEL_ChangeFinish)(&_SELECTOR)

/**
 * @brief һ�����ֱ�ǩ����ǿ������
 *
 * ���ܣ������ֱ�ǩ���趨������һ������
 *       ���ֻ�ÿ��m_timeDeltaʱ��,����m_numberDelta,ֱ������Ŀ������m_numberTarget
 *
 * Ӧ�÷�Χ���������ڷ�������ʾ���ߵ���ʱ
 */
class NumberCount : public cocos2d::CCObject
{
public:
	NumberCount();

	void setLabelAtlas(cocos2d::CCLabelAtlas* ccLabelAtlas)   
	{
		m_ccLabelAtlas = ccLabelAtlas;
		m_ccLabelAtlas->setString(cocos2d::CCString::createWithFormat("%d",m_numberCurrent)->getCString());
	}

	void setLabelAtlas(cocos2d::ui::LabelAtlas* uiLabelAtlas) 
	{
		m_uiLabelAtlas = uiLabelAtlas;
		m_uiLabelAtlas->setStringValue(cocos2d::CCString::createWithFormat("%d",m_numberCurrent)->getCString());
	}

	void setChangeFinishCallback(SEL_ChangeFinish selector,CCObject* target)
	{
		m_selector = selector;
		m_target = target;
	}

	///Ĭ�Ͼ����ڼ����ģ���������б�Ҫ�������ȹ�����������Ҫ��ʱ���ڿ�ʼ
	void begin();

	///Ĭ�Ͼ����ڼ����ģ���������б�Ҫ�������ȹ�����������Ҫ��ʱ���ڿ�ʼ
	void stop();
	
	///������ֱ仯���ʱ������ʾ������
	int getNumberTarget() {return m_numberTarget;}

	///��õ�ǰ��ʾ������
	int getNumberCurrent(){return m_numberCurrent;}

	/**
	 * ʹ��������һ��ֵ
	 */
	void add(int increment)   {m_numberTarget += increment;}

	/**
	 * ��������ÿһ�����ӵ������ľ���ֵ
	 * ���ֻ�ÿ��m_timeDeltaʱ��,����m_numberDelta,ֱ������m_numberTarget
	 */
	void setNumberDelta(int delta)     {m_numberDelta = abs(delta);}
	
	/**
	 * ��������ÿһ�����ӵ�ʱ����m_timeDelta
	 * ���ֻ�ÿ��m_timeDeltaʱ��,���ӻ����m_numberDelta,ֱ������m_numberTarget
	 */
	void setTimeDelta(float timeDelta) {m_timeDelta = timeDelta;}

	/**
	 * ��������
	 *@param number Ŀ������
	 *@param bGradually �ǲ����ɵ�ǰ����һ��һ�����ӵ�Ŀ������
	 */
	bool setNumber(int number, bool bGradually);

	///schedule����,�������ӵļ����������ʵ��
	void updateNumber(float fInterval);

private:
	int   m_numberTarget;  ///<���ֱ仯��Ŀ��ֵ
	int   m_numberCurrent; ///<���ֵ�ǰ��ֵ
	int   m_numberDelta;   ///<ÿһ��������
	float m_timeDelta;     ///<��øı�һ������
	float m_timeEscape;
	
	cocos2d::CCLabelAtlas*    m_ccLabelAtlas;
	cocos2d::ui::LabelAtlas*  m_uiLabelAtlas;

	SEL_ChangeFinish m_selector;
	CCObject* m_target;
};

#endif