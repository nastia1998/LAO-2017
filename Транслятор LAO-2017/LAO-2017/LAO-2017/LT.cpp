#include "stdafx.h"
#include "LT.h"

namespace LT
{
	LexTable Create(int size)
	{
		LexTable *p = new LexTable;					//создание экзмепл€ра таблицы лексем
		p->maxize = size;							//задание максимального размера
		p->size = 0;								//начальный размер равен нулю
		p->table = new Entry[size];					//создание масссива строк таблицы лексем
		memset(p->table, 255, 255);					//заполнение экземпл€ров таблицы строк на 255
		return *p;
	}
	Entry Add(LexTable& lextable, Entry entry)
	{
		return(lextable.table[lextable.size++] = entry);			//добавление на позицию текущего размера таблицы лексем элемента таблицы тсрок лексем
	}
	Entry GetEntry(LexTable& lextable, int n)
	{
		return (lextable.table[n]);
	}
	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
	}
}