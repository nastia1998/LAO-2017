// LAO2017.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

#include "LexicalAnalize.h"
#include "FST.h"
#include "GRB.h"
#include "MFST.h"
#include "SemAn.h"
#include "PolishNotation.h"
#include "Generation.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "Russian");
	Log::LOG log = Log::INITLOG;
	try
	{
	Parm::PARM parm = Parm::getparm(argc, argv);
	log = Log::GetLog(parm.log);
	Log::WriteLog(log);
	Log::WriteParm(log, parm);
	In::IN in = In::getin(parm.in);
	Log::WriteIn(log, in);

	/////////лексический анализ////////////
	Lex::TABLES tables = Lex::Lexic(in);

	if (parm.lex)
		Log::WriteLexTable(log, tables.Lex);
	if (parm.id)
		Log::WriteIdTable(log, tables.Id);

	/////////синтаксический анализ/////////
	MFST_TRACE_START(log);
	MFST::Mfst mfst(tables, GRB::getGreibach());

	if (!mfst.start(log))
		throw ERROR_THROW(609);
	mfst.savededucation();
	if (parm.tree)
		mfst.printrules(log);


	/////////семантический анализ//////////
	SemAn::SemAnalize sem(tables.Id, tables.Lex);

	/////////польская запись///////////////
	PN::PolishNotation(&tables.Lex, &tables.Id);

	///////////////генерация кода//////////
	CG::Gener(tables.Lex, tables.Id);
	Log::Close(log);
	std::cout << "Well done!" << std::endl;

	}
	catch (Error::ERROR e)
	{
	std::cout << "Error " << e.id << ": " << e.message;
	if (e.inext.line != -1)
	std::cout << "; Line: " << e.inext.line;
	if (e.inext.col != -1)
	std::cout << ", Column: " << e.inext.col << std::endl;
	std::cout << std::endl;
	if (e.id != 100)
	Log::WriteError(log, e);
	}
	catch (...)
	{
	std::cout << "Error 1 [SYSTEM]: System Failure" << std::endl;
	}
	return 0;
}
