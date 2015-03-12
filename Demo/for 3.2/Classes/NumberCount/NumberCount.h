/****************************************************************************
 for cocos2d-x 3.2

 author : LuoYu
 
 e-mail : 466474482@qq.com

 github : https://github.com/bluesky466/cocos2dxUsefulClasses
 ****************************************************************************/

#ifndef _NUMBER_COUNT_H_
#define _NUMBER_COUNT_H_

#include "cocos2d.h"
#include "editor-support\cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

///����Ŀ�����ֵĻص�
typedef std::function<void(int target)> ChangeFinishCallback;

/**
 * @brief һ�����ֱ�ǩ����ǿ������
 *
 * ���ܣ������ֱ�ǩ���趨������һ������
 *       ���ֻ�ÿ��m_timeDeltaʱ��,����m_numberDelta,ֱ������Ŀ������m_numberTarget
 *
 * Ӧ�÷�Χ���������ڷ�������ʾ���ߵ���ʱ
 */
class NumberCount : public cocos2d::Ref
{
public:
	NumberCount();
	~NumberCount();

	void setLabelAtlas(cocos2d::LabelAtlas* ccLabelAtlas)   
	{
		m_ccLabelAtlas = ccLabelAtlas;
		m_ccLabelAtlas->setString(cocos2d::__String::createWithFormat("%d",m_numberCurrent)->getCString());
	}

	void setTextAtlas(cocos2d::ui::TextAtlas* uiLabelAtlas) 
	{
		m_uiLabelAtlas = uiLabelAtlas;
		m_uiLabelAtlas->setString(cocos2d::__String::createWithFormat("%d",m_numberCurrent)->getCString());
	}

	void setChangeFinishCallback(ChangeFinishCallback callback)
	{
		m_finishCallback = callback;
	}

	///Ĭ�Ͼ����ڼ����ģ���������б�Ҫ�������ȹ�����������Ҫ��ʱ���ڿ�ʼ
	void begin()
	{
		cocos2d::Director::getInstance()->getScheduler()->schedule(schedule_selector(NumberCount::updateNumber),this,0.0f,false);
	}

	///Ĭ�Ͼ����ڼ����ģ���������б�Ҫ�������ȹ�����������Ҫ��ʱ���ڿ�ʼ
	void stop()
	{
		cocos2d::Director::getInstance()->getScheduler()->unschedule(schedule_selector(NumberCount::updateNumber),this);
	}
	
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
	
	cocos2d::LabelAtlas*    m_ccLabelAtlas;
	cocos2d::ui::TextAtlas* m_uiLabelAtlas;

	ChangeFinishCallback m_finishCallback;
};

#endif