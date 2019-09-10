#pragma once
#include "stdafx.h"
#include <iostream>
#define ARR_FST_SIZE 25
namespace FST
{
	struct RELATION			//ребро: символ -> вершина графа перехода КА
	{
		char symbol;		//символ перехода
		short nnode;		//номер смежной вершины
		RELATION(
			char c = 0x00,	//символ перехода
			short ns = NULL //новое состояние
		);
	};

	struct NODE	//вершина графа переходов
	{
		short n_relation;		//количество инцидентных рёбер
		RELATION *relations;	//инцидентные рёбра
		NODE();
		NODE(
			short n,			//количество инцидентных рёбер
			RELATION rel, ...	//список рёбер
		);
	};

	enum LEXAN
	{
		LEXEMS, TYPE, LIT, ID, LIB, ENTER, OPERATOR
	};
	struct FST	//недетерминированный конечный автомат
	{
		char* string;		//цепочка (строка, завершается 0х00)
		char  lex;			//лексема, соответствующая автомату
		short position;		//текущая позиция в цепочке
		short nstates;		//количество состояний автомата
		NODE* nodes;		//граф переходов: [0] -начальное состояние, [nstate-1] -конечное
		short* rstates;		//возможные состояния автомата на данной позиции
		LEXAN lexsw;
		FST(
			char* s,		//цепочка(строка, завершается 0х00)
			char  l,		//лексема, соответствующая автомату
			LEXAN plexsw,
			short ns,		//количество состояний автомата
			NODE  n, ...	//список состояний (граф переходов)
		);
		FST();
	};

	bool execute(		//выполнить распознавание цепочки
		FST& fst		//недетерминированный конечный автомат
	);
	NODE AllSymb();
	FST* ArrFst();		//массив автоматов
}