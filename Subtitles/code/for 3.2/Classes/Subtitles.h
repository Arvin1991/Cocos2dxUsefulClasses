/****************************************************************************
 for cocos2d-x 3.2

 author : LuoYu
 
 e-mail : 466474482@qq.com

 github : https://github.com/bluesky466/cocos2dxUsefulClasses
 ****************************************************************************/
#ifndef _SUBTITLES_H_
#define _SUBTITLES_H_

#include "cocos2d.h"
#include <string>
#include <vector>

struct DialogueData
{
	DialogueData(const std::string& who,
				 const std::string& say, 
				 void* userData):
						_who(who),
						_say(say),
						_userData(userData)
	{
	}

	std::string _who;
	std::string _say;
	void* _userData;
};

///ÿ���ֳ��ֶ������,��һ���������_who,�ڶ����������_say,�������������_userData
typedef std::function<void(const std::string&,const std::string&,void*)> WordAppearEvent;

///��һ�ζԻ���ȫ��ʾ��ʱ����ã���һ��������ŸöԻ������,�ڶ���������ŸöζԻ�����Ϣ
typedef std::function<void(int,const DialogueData&)> DialogueEndEvent;

/**
 *  һ����Ļ��
 *  �ܹ�һ����һ���ֵĴ�ӡ����ζԻ�
 *  ��֧��utf8����
 */
class Subtitles : public cocos2d::Ref
{
public:
	Subtitles();

	///ÿһ֡����,���м���
	void update(float interval);

	///����Ի��б�,�������жԻ�
	void setDialogueList(const std::vector<DialogueData>& dialogueList);

	///��ʾ�öζԻ�����������
	void showWholeDialogue();

	///������һ�ζԻ�
	bool nextDialogue();
	
	///����ĳһ�ζԻ�
	bool jumpToDialogue(int index);

	///��ζԻ��Ƿ��Ѿ���ȫ��ʾ
	bool isShowWholeDialogue()			 {return m_numByteCopy>=m_dialogueList[m_dialogueIndex]._say.size();}

	///�����ַ����ֵ�ʱ����
	void setWordInterval(float interval) {m_wordInterval = interval;}

	///���ÿ�ʼ��ֹͣ��ӡ�Ի�
	void setRunning(bool isRunning)      {m_isRunning = isRunning;}

	///�ǲ������һ�ζԻ�
	bool isEndofDialogueList()			 {return m_dialogueIndex>=m_dialogueList.size()-1;}

	///�����µ��ַ����ֵ�ʱ��Ļص�����
	void setWordAppearEvent(WordAppearEvent callback) {m_wordAppearCallback = callback; }

	///��һ�ζԻ�ȫ����ӡ������ʱ��Ļص�����
	void setDialogueEndEvent(DialogueEndEvent callback){m_dialogueEndCallback = callback;}

	const DialogueData& getDialogueData(int index)
	{
		return m_dialogueList[index];
	}

	const std::vector<DialogueData>& dialogueDataList()
	{
		return m_dialogueList;
	}

private:
	///�Ի��б�
	std::vector<DialogueData> m_dialogueList;

	bool  m_isRunning;
	float m_timeAccumulate;  ///<ʱ����ۻ���,��m_timeAccumulate���ڵ���m_wordIntervalʱ���Ӷ��ӡһ����,������
	float m_wordInterval;    ///<��Ļÿһ���ֳ��ֵļ��
	int   m_dialogueIndex;   ///<��ǰ�ǵڼ�����Ļ
	char* m_dialogue;        ///<��ǰ��ʾ�ĶԻ�
	int   m_numByteCopy;     ///<�����˶��ٸ��ֽڵ���Ļ(utf8���ַ����ǹ̶����ȵ�,������Ҫ��¼)
	
	WordAppearEvent m_wordAppearCallback;
	DialogueEndEvent m_dialogueEndCallback;

	/**
	 *  ����src�ĵ�һ��utf8�ַ�
	 *@return ���ַ���ռ���ֽ���
	 */
	int copyUtf8Word(char* desc,const char* src);
};

#endif