#pragma once
#include "stdafx.h"
#include "LT.h"
#define IN_MAX_LEN_TEXT 1024*1024		//������������ ������ ��������� ���� 1��
#define IN_CODE_ENDL	'\n'			//������ ����� ������
#define STR_NUMB_SEP	'|'				// ��������� ��� ����� ������
#define IN_CODE_SPACE	' '				//�������
#define IN_WORD_MAX_LEN 255				//������������ ������ �����

//������� �������� ������� ����������, ������ = ��� (Windows 1251) �������
//�������� IN::F - ����������� ������, IN::T  - ����������� ������,  IN::S - ���������,
//		���� 0<=�������� <256 - �� �������� ������ ��������
#define IN_CODE_TABLE {\
		 /*0*/	 /*1*/ /*2*/  /*3*/	 /*4*/	/*5*/  /*6*/   /*7*/ /*8*/	/*9*/  /*a*/  /*b*/	 /*c*/	/*d*/  /*e*/  /*f*/	 \
/*0*/    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*1*/    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*2*/	 IN::T, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, IN::S, IN::S, IN::S, IN::S, IN::S, IN::S, IN::T, IN::S, \
/*3*/    IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::S, IN::S, IN::S, IN::S, IN::T, \
/*4*/    IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
/*5*/    IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*6*/    IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
/*7*/    IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::S, IN::F, IN::S, IN::F, IN::F, \
     \
/*8*/    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*9*/    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*a*/    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*b*/    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*c*/    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*d*/    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*e*/    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
/*f*/    IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F \
}

// 0x0a - ������� ������,  0x22 - "
// IN::S -- ����������   (  )	*	+	,	-	;	=	{	}  /
namespace In
{
	struct IN
	{
		enum { T = 1, F = 2, S = 3 };		//� - ���������� ������, F - ������������, S - ���������
		int size;							//������ ��������� ����
		int lines;							//���-�� �����
		std::queue<std::string> Words;
		std::queue<int> Line;
		int code[256] = IN_CODE_TABLE;		//������� �������
	};
	IN getin(wchar_t infile[]);				//������ � ��������� ������� �����
};