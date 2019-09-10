// LAOLib.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
extern "C"
{
	int __stdcall consolen(int num)
	{
		std::cout << num << std::endl;
		return 0;
	}
	int __stdcall consoles(char* str)
	{
		std::cout << str << std::endl;
		return 0;
	}
	
	/*int __stdcall lengths(char* str)
	{
		int i = 0;
		while (str[i] != '/0') i++;
		return i;
	}*/
	int _stdcall  sum(int a, int b)
	{
		return a + b;
	}
}