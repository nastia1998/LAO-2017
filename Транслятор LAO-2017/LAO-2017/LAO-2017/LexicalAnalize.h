#pragma once
#include "IT.h"
#include "LT.h"
#include "FST.h"

namespace Lex
{
	struct TABLES
	{
		IT::IdTable  Id;
		LT::LexTable Lex;
	};

	TABLES Lexic(In::IN in);				//����������� ������
	int  SelectFst(char* word);				//����� ��������
	void AddId(char*, int, int, int);		//���������� ��������������
	void AddLit(char lex, int str, int id);	//���������� ��������
}
