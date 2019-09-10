#pragma once
#define LEXEMA_FIXZISE 1				//������������� ������ �������
#define LT_MAXSIZE 4096					//������������ ���-�� ����� � ������� ������
#define LT_TI_NULLIDX 0xffffffff		//��� �������� ������� ���������������
#define LEX_NUM			'n'		//	������� ��� �����
#define LEX_STR			's'		//	������� ��� �����
#define LEX_VAR			'v'		//	������� ��� ���������� ���������������
#define LEX_FUN			'f'		//	������� ��� ���������� �������
#define LEX_RETURN		'r'		//	����������� ��������
#define LEX_ENTER		'e'		//	����� �����
#define LEX_CONSOLE		'c'		//	����� ������
#define LEX_ID			'i'		//	�������������
#define LEX_LITERALSTR	'l'		//	������� ���������
#define LEX_LITERALNUM	'k'		//	������� �������������
#define LEX_SEMICOLON	';'		//	;
#define LEX_COMMA		','		//	,
#define LEX_LEFTBRACE	'{'		//	{
#define LEX_RIGHTBRACE	'}'		//	}
#define LEX_LEFTHESIS	'('		//	(
#define LEX_RIGHTHESIS	')'		//	)
#define LEX_PLUS		'+'		//	+
#define LEX_MINUS		'-'		//	-
#define LEX_STAR		'*'		//	*
#define LEX_RAVNO		'='		//	=

namespace LT
{
	struct Entry			// ������ ������� ������
	{
		char lexema;		//�������
		int sn;				//����� ������ � �������� ����
		int idxTI;			//������ � ������� ��������������� 
	};
	struct LexTable
	{
		int maxize;							//������� ������� ������ 
		int size;							//������� ������ ������� ������
		Entry* table;						//������ ����� ������� ������	
	};
	LexTable Create(						//������� ������
		int size							//�������
	);
	Entry GetEntry(LexTable& lextable, int n);//�������� ������ ������� ������
	Entry Add(
		LexTable& lextable,					//��������� �������
		Entry entry							//������ ������� ������
	);
	void Delete(LexTable& lextable);		//������� ������� ������
}