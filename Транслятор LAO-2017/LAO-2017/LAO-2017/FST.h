#pragma once
#include "stdafx.h"
#include <iostream>
#define ARR_FST_SIZE 25
namespace FST
{
	struct RELATION			//�����: ������ -> ������� ����� �������� ��
	{
		char symbol;		//������ ��������
		short nnode;		//����� ������� �������
		RELATION(
			char c = 0x00,	//������ ��������
			short ns = NULL //����� ���������
		);
	};

	struct NODE	//������� ����� ���������
	{
		short n_relation;		//���������� ����������� ����
		RELATION *relations;	//����������� ����
		NODE();
		NODE(
			short n,			//���������� ����������� ����
			RELATION rel, ...	//������ ����
		);
	};

	enum LEXAN
	{
		LEXEMS, TYPE, LIT, ID, LIB, ENTER, OPERATOR
	};
	struct FST	//������������������� �������� �������
	{
		char* string;		//������� (������, ����������� 0�00)
		char  lex;			//�������, ��������������� ��������
		short position;		//������� ������� � �������
		short nstates;		//���������� ��������� ��������
		NODE* nodes;		//���� ���������: [0] -��������� ���������, [nstate-1] -��������
		short* rstates;		//��������� ��������� �������� �� ������ �������
		LEXAN lexsw;
		FST(
			char* s,		//�������(������, ����������� 0�00)
			char  l,		//�������, ��������������� ��������
			LEXAN plexsw,
			short ns,		//���������� ��������� ��������
			NODE  n, ...	//������ ��������� (���� ���������)
		);
		FST();
	};

	bool execute(		//��������� ������������� �������
		FST& fst		//������������������� �������� �������
	);
	NODE AllSymb();
	FST* ArrFst();		//������ ���������
}