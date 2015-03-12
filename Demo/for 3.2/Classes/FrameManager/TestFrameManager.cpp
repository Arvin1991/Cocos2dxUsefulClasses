#include "TestFrameManager.h"
#include "editor-support\cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;

bool TestFrameManager::init()
{
    if ( !TestBase::init() )
    {
        return false;
    }

    auto item = MenuItemFont::create("SHOW", CC_CALLBACK_1(TestFrameManager::btVisbleCallback, this));
	item->setAnchorPoint(Vec2(0.5f,0.5f));
	item->setPosition(m_visibleCenter);

    auto menu = Menu::create(item, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu,0);
    
	/*Frame�Ĳ���*/
	Widget* frame = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("FrameManager/UIRes/DemoLogin.ExportJson");
	frame->setScale(0.8f); //���ű��������������
	frame->setAnchorPoint(Vec2(0.5f,0.5f));//ê������������
	frame->setPosition(m_visibleCenter);//��������������
	this->addChild(frame,1);
	
	//��������
	Helper::seekWidgetByName(frame,"login_Button")->addTouchEventListener(CC_CALLBACK_2(TestFrameManager::touchUiItemCallBack,this));
	Helper::seekWidgetByName(frame,"close_Button")->addTouchEventListener(CC_CALLBACK_2(TestFrameManager::touchUiItemCallBack,this));
	Helper::seekWidgetByName(frame,"agree_CheckBox")->addTouchEventListener(CC_CALLBACK_2(TestFrameManager::touchUiItemCallBack,this));
	Helper::seekWidgetByName(frame,"name_TextField")->addTouchEventListener(CC_CALLBACK_2(TestFrameManager::touchUiItemCallBack,this));
	Helper::seekWidgetByName(frame,"password_TextField")->addTouchEventListener(CC_CALLBACK_2(TestFrameManager::touchUiItemCallBack,this));
	Helper::seekWidgetByName(frame,"confirm_TextField")->addTouchEventListener(CC_CALLBACK_2(TestFrameManager::touchUiItemCallBack,this));

	//frame��ʼ��,������һ�²���ʼ����ֱ��layer->setVisible(false);���ô��ڲ��ɼ�֮��,�����ԭ���İ�ť���򣬿����Ƿ��жԻ������
	m_frame.setFrame(frame,Helper::seekWidgetByName(frame,"backageImg"));

	//���õ���ڶԻ����ⲿʱ��ļ����¼������������ｫ�Ի�������
	m_frame.setTouchOutOfFrameEventListener(CC_CALLBACK_1(TestFrameManager::touchOutOfFrame,this));
	
	m_frame.setFrameVisible(true);

    return true;
}

void TestFrameManager::btVisbleCallback(Ref* pSender)
{
	//���öԻ���ɼ�
	m_frame.setFrameVisible(true);
}

void TestFrameManager::touchUiItemCallBack(Ref* pObject,Widget::TouchEventType eventType)
{
	if(eventType == Widget::TouchEventType::ENDED)
	{
		MessageBox("touch ui widget","touch ui widget");
	}
}

void TestFrameManager::touchOutOfFrame(cocos2d::ui::Widget*)
{
	//�������ڶԻ����⣬���Ի�������
	m_frame.setFrameVisible(false);
}

