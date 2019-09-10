#pragma once
#include <iostream>
#include "IT.h"
#include "LT.h"
#include "Error.h"
namespace SemAn
{
	struct SemAnalize
	{
		LT::LexTable lexT;
		IT::IdTable idT;
		Error::ARR_OF_ERRORS err;
		bool error = false;

		SemAnalize(IT::IdTable IdT, LT::LexTable LexT);
		void Init();
		void CheckRc();
		void ParOfProc();
		void ParOfStandProc();
		void TypesOfProc();
		void Types();
		void IsProc();
		void ParOfIf();
	};
}