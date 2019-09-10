#include "stdafx.h"
#include "PolishNotation.h"

namespace PN
{
	void PolishNotation(LT::LexTable* LexT, IT::IdTable* IdT)
	{
		for (int i = 0; i < LexT->size; i++)
		{
			if (LexT->table[i].lexema == LEX_RAVNO)
			{
				Conversation(LexT, IdT, ++i);
			}
		}
	}
	void Conversation(LT::LexTable* lextable, IT::IdTable* idtable, int lextable_pos)
	{
		std::stack<LT::Entry> st;
		LT::Entry outstr[200];
		int len = 0,							//����� �����
			lenout = 0,							//����� �������� ������
			semicolonid;						//�� ��� �������� ������� � ������ � �������
		char t, oper, hesis = 0;				//������� ������/���� ���������/���-�� ������
		int indoffunk;							//������ ��� ������ �� ������� � ��������
		for (int i = lextable_pos; lextable->table[i].lexema != LEX_SEMICOLON; i++)
		{
			len = i;
			semicolonid = i + 1;
		}
		len++;
		for (int i = lextable_pos; i < len; i++)
		{
			t = lextable->table[i].lexema;
			if (lextable->table[i].lexema == LEX_PLUS || lextable->table[i].lexema == LEX_MINUS ||
				lextable->table[i].lexema == LEX_STAR)
				oper = idtable->table[lextable->table[i].idxTI].id[0];
			if (t == LEX_RIGHTHESIS)						//������������ ����� �� ������ ����� ������
			{
				while (st.top().lexema != LEX_LEFTHESIS)
				{
					outstr[lenout++] = st.top();			//���������� � �������� ������ ��������� ������ ����� ��������
					hesis++;
					st.pop();								//������� ������� �����
				}
				st.pop();									//������� ����� ������ � �����
			}
			if (t == LEX_ID || t == LEX_LITERALSTR || t == LEX_LITERALNUM || t == 'm')
			{
				if (lextable->table[i + 1].lexema == LEX_LEFTHESIS)
				{
					indoffunk = i;
					i += 2;
					while (lextable->table[i].lexema != LEX_RIGHTHESIS)
					{								//���� ������ ���������� �������, ������������ �� � ������
						if (lextable->table[i].lexema != LEX_COMMA)
						{
							outstr[lenout++] = lextable->table[i++];
						}
						else
						{
							hesis++;
							i++;
						}
					}
					outstr[lenout++] = lextable->table[indoffunk];
					outstr[lenout - 1].lexema = LEX_NEWPROC;
					hesis += 2;
				}
				else
					outstr[lenout++] = lextable->table[i];
			}
			if (t == LEX_LEFTHESIS)
			{
				st.push(lextable->table[i]);							//�������� � ���� ����� ������
				hesis++;
			}

			if (oper == '+' || oper == '-' || oper == '*')
			{
				if (!st.size())
					st.push(lextable->table[i]);
				else {
					int pr, id;
					if (st.top().lexema == '(' || st.top().lexema == ')')
						pr = 1;
					else {
						id = st.top().idxTI;
						pr = ArifmPriorities(idtable->table[id].id[0]);
					}
					if (ArifmPriorities(oper) > pr)																		//���� ��������� ����������� �������� ������ �������� �� ������� �����
						st.push(lextable->table[i]);																		//��������� �������� � ����
					else
					{
						while (st.size() && ArifmPriorities(oper) <= ArifmPriorities(idtable->table[id].id[0]))			//���� ������, �� ���������� � ������ ��� �������� � ������� ��� ������ �����������
						{
							outstr[lenout] = st.top();
							st.pop();
							lenout++;
						}
						st.push(lextable->table[i]);
					}
				}
			}
			oper = NULL;				//�������� ���� �����
		}
		while (st.size())
		{
			outstr[lenout++] = st.top();												//����� � ������ ���� ������ �� �����
			st.pop();
		}
		for (int i = lextable_pos, k = 0; i < lextable_pos + lenout; i++, k++)
		{
			lextable->table[i] = outstr[k];												//������ � ������� �������� ������
		}
		lextable->table[lextable_pos + lenout] = lextable->table[semicolonid];			//������� �������� � ������ � �������
		for (int i = 0; i < hesis; i++)
		{
			for (int j = lextable_pos + lenout + 1; j < lextable->size; j++)				//�������� �� ������ �����
			{
				lextable->table[j] = lextable->table[j + 1];
			}
			lextable->size--;
		}
	}
	int ArifmPriorities(char symb)
	{
		if (symb == LEX_LEFTHESIS || symb == LEX_RIGHTHESIS)
			return 1;
		if (symb == LEX_PLUS || symb == LEX_MINUS)
			return 2;
		if (symb == LEX_STAR)
			return 3;
	}
}