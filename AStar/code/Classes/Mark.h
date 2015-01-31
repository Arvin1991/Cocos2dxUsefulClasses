/****************************************************************************
 author : LuoYu
 
 e-mail : 466474482@qq.com

 github : https://github.com/bluesky466/cocos2dxUsefulClasses
 ****************************************************************************/
#ifndef _MARK_H_
#define _MARK_H_

#include <string.h>

/**
 * ��ά�����
 * �൱��һ����ά��bool����
 * ÿһ��������λ����һ�������ö�����λΪ1��Ϊtrue��Ϊ0��Ϊfalse
 */
class Mark
{
public:
	Mark();
	~Mark();

	///���ô�С,����m_marks����Ĵ�С
	int setSize(unsigned int row, unsigned int col); 

	///���ĳ����,��������ĳ�����־λΪ1
	void setMark(unsigned int row, unsigned int col);

	///ȡ�����ĳ����,��������ĳ�����־λΪ0
	void cancelMark(unsigned int row, unsigned int col);

	///��ѯ�Ƿ�ĳ�����Ƿ񱻱��
	bool isMask(unsigned int row, unsigned int col)const;
	
	///ȡ�����б��
	void clearMarks();

	const Mark& operator = (const Mark& mark);

	unsigned int getRow() {return m_row;}
	unsigned int getCol() {return m_col;}

private:
	unsigned char* m_marks;
	unsigned int m_row;
	unsigned int m_col;
};

inline const Mark& Mark::operator = (const Mark& mark)
{
	int size = setSize(mark.m_row,mark.m_col);
	memcpy(m_marks,mark.m_marks,size*sizeof(unsigned char));
	return *this;
}

#endif