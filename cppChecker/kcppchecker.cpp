#include "kcppchecker.h"

#include<iomanip>
#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

KCppCheck::KCppCheck(string fileName)
	:m_FileName(fileName)
	, m_BraceCount(0)
	, m_FileLineNum(1)
{
}

KCppCheck::~KCppCheck(void)
{
}

bool KCppCheck::checkCppFile(bool veiwSrcCode)
{
	cout << "\nthe open file is " << m_FileName << endl << endl;
	ifstream fin(m_FileName);
	if (fin.is_open())
	{
		string fileLine("");
		m_FileLineNum = 1;

		while (!fin.eof())
		{
			getline(fin, fileLine);
			if (veiwSrcCode)
			{
				cout.flags(ios::right);
				cout << setw(5) << m_FileLineNum <<"|" << fileLine<<endl;
			}

			if (fileLine != "")
			{
				int linePos = 0;
				while(linePos < fileLine.size() && fileLine[linePos] == '	')
					++linePos;

				lineEndCheck(fileLine);
				lineCheck(fileLine, linePos);
			}
			++ m_FileLineNum;
		}

		fin.close();
		return true;
	}
	else
	{
		return false;
	}
}

void KCppCheck::lineCheck(const string &line, const int &linePos)
{
	if (linePos < line.size())
	{
		if (line[linePos] == ' ')
		{
			coutErrorMsg(2);
			sameLineBrace(line);
		}
		else
		{
			if (line[linePos] == '{')
			{
				if (linePos == line.size() - 1)
				{
					coutErrorMsg(linePos == m_BraceCount ? 0 : 4);
					++ m_BraceCount;
				}
				else
					sameLineBrace(line);
			}
			else
			{
				if (line[linePos] == '}')
				{
					-- m_BraceCount;
					coutErrorMsg(linePos == m_BraceCount ? 0 : 4);
				}
				else
				{
					coutErrorMsg(linePos >= m_BraceCount ? 0 : 1);
					sameLineBrace(line);
				}
			}
		}
	}
}

void KCppCheck::coutErrorMsg(const int &index)
{
	static string errorMessage[] =
	{
		"",
		"------代码对齐有问题 \n",
		"------不是以Tab缩进\n",
		"------行尾有多余的空格、Tab等字符\n",
		"------大括号没有对齐\n",
		"------大括号在单独一行，或左右大括号在同一行\n"
	};
	if (index > 0)
	{
		cout.flags(ios::right);
		cout << setw(5) << m_FileLineNum <<"|" << errorMessage[index];
	}
}

void KCppCheck::lineEndCheck(const string &line)
{
	auto iter = line.rbegin();
	if (*iter == ' ' || *iter == '	')
		coutErrorMsg(3);

}

void KCppCheck::sameLineBrace(string line)
{
	for (auto iter = line.begin(); iter != line.end(); ++ iter)
	{
		if (*iter == '\\')
		{
			if (*(++ iter) == '\"')
			{
				*iter = ' ';
			}
		}
		else
		{
			if (*iter == '\"')
			{
				*iter = '\'';
			}
		}
	}

	int braceBackUp = m_BraceCount;
	checkLeftBrace(line);
	checkRightBrace(line);
	coutErrorMsg(braceBackUp == m_BraceCount ? 0 : 5);
}

void KCppCheck::checkLeftBrace(const string &line)
{
	auto startIter = line.begin();
	auto braceIter = find (line.begin(), line.end(), '{');
	while (braceIter != line.end())
	{
		auto quoteIter = find(startIter, braceIter, '\'');
		if (quoteIter == braceIter)
		{
			++ m_BraceCount;
			startIter = braceIter + 1;
			braceIter = find(startIter, line.end(), '{');
		}
		else
		{
			startIter = find(quoteIter + 1, line.end(), '\'');
			braceIter = find(startIter + 1, line.end(), '{');
		}
	}
}

void KCppCheck::checkRightBrace(const string &line)
{
	auto startReverseIter = line.rbegin();
	auto braceReverseIter = find (line.rbegin(), line.rend(), '}');
	while (braceReverseIter != line.rend())
	{
		auto quoteReverseIter = find(startReverseIter, braceReverseIter, '\'');
		if (quoteReverseIter == braceReverseIter)
		{
			-- m_BraceCount;
			startReverseIter = braceReverseIter + 1;
			braceReverseIter = find(startReverseIter, line.rend(), '}');
		}
		else
		{
			startReverseIter = find(quoteReverseIter + 1, line.rend(), '\'');
			braceReverseIter = find(startReverseIter + 1, line.rend(), '}');
		}
	}
}
