// -------------------------------------------------------
// main.h
// 创建者： 黄楚强
// 创建时间： 2013/7/5
// 功能描述： 工程的入口，读取命令行调用时的文件参数
// Copyright 2013 Kingsoft
// --------------------------------------------------------
#include<iostream>
#include<string>
using namespace std;

#include "kcppchecker.h"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		//cout << "请指定cpp文件" << endl;
		KCppCheck cppCheck("..\\cppchecker\\kcppchecker.cpp");
		cppCheck.checkCppFile();
	}
	else
	{
		KCppCheck cppCheck(argv[1]);
		if (argc == 3)
		{
			cppCheck.checkCppFile(true);
		}
		else
		{
			cppCheck.checkCppFile(false);
		}
	}
	std::wcout << "\n代码检查完毕~~~~" << endl;
	return 0;
}