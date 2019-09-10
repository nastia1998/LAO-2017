#pragma once
#include "stdafx.h"
#include "IT.h"
#include "LT.h"
#include <iostream>
#include <stack>
#define LEX_NEWPROC '@'

namespace PN
{
	void PolishNotation(LT::LexTable* LexT, IT::IdTable* IdT);
	void Conversation(LT::LexTable* LexT, IT::IdTable* IdT, int position);
	int ArifmPriorities(char symb);
}