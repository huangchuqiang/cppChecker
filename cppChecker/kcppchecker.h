// -------------------------------------------------------
// kcppchecker.h
// 创建者： 黄楚强
// 创建时间： 2013/7/5
// 功能描述： 负责cpp文件的检查，检查内容如下：
//			1.缩进是否为Tab；
//			2.行尾是否有空格、Tab等多余字符；
//			3.大括号是否位于行首，是否对齐对齐。
// Copyright 2013 Kingsoft
// --------------------------------------------------------
#ifndef __KCPPCHECK_H__
#define __KCPPCHECK_H__

#include <string>
using std::string;

class KCppCheck
{
public:
	KCppCheck(string fileName);
	~KCppCheck(void);
	bool checkCppFile(bool veiwSrcCode);

private:
	void coutErrorMsg(const int &index);
	void lineEndCheck(const string &line);
	void lineCheck(const string &line, const int &linePos);
	void sameLineBrace(string line);
	void checkLeftBrace(const string &line);
	void checkRightBrace(const string &line);
	string m_FileName;
	int m_BraceCount;
	int m_FileLineNum;
};


#endif //__KCPPCHECK_H__