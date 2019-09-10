#include "stdafx.h"
#include "Generation.h"
#include "FST.h"

namespace CG
{
	bool isInT(char r) 
	{
		return true;
	}

	Gener::Gener(LT::LexTable plexT, IT::IdTable pidT)
	{
		idT = pidT;
		lexT = plexT;
		out = std::ofstream("../../LAOAsmbl/LAOAsmbl/LAOAsmbl.asm");
		Head();
		Constants();
		Data();
		Code();
	}
	void Gener::Head()
	{
		out << ".586\n";
		out << "\t.model flat, stdcall\n";
		out << "\tincludelib libucrt.lib\n";
		out << "\tincludelib kernel32.lib\n";
		out << "\tExitProcess PROTO :DWORD\n\n";
		out << "\tincludelib ../Debug/LAOLib.lib\n";
		out << "\tconsoles PROTO :DWORD\n";
		out << "\tconsolen PROTO :DWORD\n";
		out << "\tsum PROTO :DWORD, :DWORD\n";
		out << "\n.stack 4096\n";
	}
	void Gener::Constants()
	{
		out << ".const\n";
		for (int i = 0; i < idT.size; i++)
		{
			if (idT.table[i].idtype == 4)			// если литерал
			{
				out << "\t" << idT.table[i].id;
				if (idT.table[i].iddatatype == 2)	// если STR
					out << " BYTE " << idT.table[i].value.vstr.str << ", 0";
				if (idT.table[i].iddatatype == 1)	// если NUM
					out << " DWORD " << idT.table[i].value.vint;
				out << '\n';
			}
		}
	}
	void Gener::Data()
	{
		out << ".data\n";
		for (int i = 0; i < lexT.size; i++)
		{
			if (lexT.table[i].lexema == 'v')
			{
				if (idT.table[lexT.table[i + 2].idxTI].idtype == 1)		// если переменная
				{
					out << "\t" << idT.table[lexT.table[i + 2].idxTI].id;
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype == 2)		// если STR
						out << " DWORD ?";
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype == 1)		// если NUM
						out << " DWORD ?";
					out << '\n';
				}
				for (int j = i; j < lexT.size; j++)
					lexT.table[j] = lexT.table[j + 4];
				lexT.size -= 4;
				i--;
			}
		}
	}
	void Gener::Code()
	{
		out << "\n.code\n";
		int indOfFun = 0;
		int indOflex = -1;
		int rhesis = -1;
		bool isif = false;

		bool proc = false;
		bool enter = false;
		int ColI = 0;
		for (int i = 0; i < lexT.size; i++)
		{
			if (lexT.table[i].lexema == 'f')
			{
				indOfFun = i + 2;
				out << idT.table[lexT.table[indOfFun].idxTI].id << " PROC ";
				proc = true;
				while (lexT.table[i].lexema != ')')
				{
					rhesis = i;
					i++;
				}
				while (lexT.table[i].lexema != '(')
				{
					if (lexT.table[i].lexema == 'i')
					{
						if (idT.table[lexT.table[i].idxTI].iddatatype == 1)		// если NUM
						{
							out << idT.table[lexT.table[i].idxTI].id << ":DWORD";
							if (lexT.table[i - 2].lexema != '(')
								out << ", ";
						}
						if (idT.table[lexT.table[i].idxTI].iddatatype == 2)		// если STR
						{
							out << idT.table[lexT.table[i].idxTI].id << ":DWORD";
							if (lexT.table[i - 2].lexema != '(')
								out << ", ";
						}
					}
					i--;
				}
				i = rhesis;
				out << std::endl;
			}
			if (lexT.table[i].lexema == 'e')
			{
				enter = true;
				out << "main PROC\n";
			}
			if (lexT.table[i].lexema == 'm')
			{
				out << "\tpush " << idT.table[lexT.table[i + 2].idxTI].id << "\n";
				out << "\tpush " << idT.table[lexT.table[i + 4].idxTI].id << "\n";
				out << "call sum\n";
			}
			if (lexT.table[i].lexema == '}')
			{
				
					if (proc)
					{
						if (!isif)//если иф отсутствует 
						{
							out << idT.table[lexT.table[indOfFun].idxTI].id << " ENDP\n\n";
							proc = false;
						}
						else if(lexT.table[i + 1].lexema == 'q')
						{
							out << "jmp flag" << ColI - 1 << "\n";
							out << "more" << ColI - 1 << ":\n";
						}
						else
						{
							out << "flag" << ColI - 1 << ":\n";
							isif = false;
						}
					}
					else if (lexT.table[i + 1].lexema == 'q')
					{
						out << "jmp flag" << ColI - 1 << "\n";
						out << "more" << ColI - 1 << ":\n";
					}
					else if(lexT.size<=i+1)
						out << "call ExitProcess\nmain ENDP\n";
					else
					{
						out << "flag" << ColI - 1 << ":\n";
						isif = false;
					}
					
					indOfFun = 0;
			
			}
			if (lexT.table[i].lexema == 'r')
			{
				if (enter)
					out << "push 0\n";
				else
				{
					if (idT.table[lexT.table[i + 1].idxTI].iddatatype == 1)
						out << "\tmov eax, " << idT.table[lexT.table[i + 1].idxTI].id << "\n\tret\n";
					if (idT.table[lexT.table[i + 1].idxTI].iddatatype == 2)
						out << "\tmov eax, offset " << idT.table[lexT.table[i + 1].idxTI].id << "\n\tret\n";
				}
			}
			if (lexT.table[i].lexema == 'c')	// если встретили console
			{
				if (lexT.table[i + 2].lexema == 'i')
				{
					if (idT.table[lexT.table[i + 2].idxTI].iddatatype == 1) // если NUM
					{
						out << "\tpush " << idT.table[lexT.table[i + 2].idxTI].id << "\n";
						out << "call consolen\n";
					}
					else													// если STR
					{
						out << "\tpush offset " << idT.table[lexT.table[i + 2].idxTI].id << "\n";
						out << "call consoles\n";
					}

				}
				else
				{
					if (lexT.table[i + 2].lexema == 'l')
					{
						out << "\tpush offset " << idT.table[lexT.table[i + 2].idxTI].id << "\n";
						out << "call consoles\n";
					}
					else
					{
						out << "\tpush " << idT.table[lexT.table[i + 2].idxTI].id << "\n";
						out << "call consolen\n";
					}
				}
				
			}
			if (lexT.table[i].lexema == 'h')		// если if
			{
				isif = true;
				out << "mov eax, " << idT.table[lexT.table[i + 2].idxTI].id << "\n";
				out << "cmp eax, " << idT.table[lexT.table[i + 4].idxTI].id << "\n";
				out << "jb less"<< ColI << std::endl << "ja more"<<ColI<<"\n";
				out << "less"<<ColI<<":\n";
				ColI++;
			}
			if (lexT.table[i].lexema == '=')
			{
				indOflex = i - 1;
				while (lexT.table[i].lexema != ';')
				{
					if (lexT.table[i].lexema == 'i')
					{
						out << "push " << idT.table[lexT.table[i].idxTI].id << "\n";
					}
					if (lexT.table[i].lexema == 'k')
						out << "push " << idT.table[lexT.table[i].idxTI].id << "\n";
					if (lexT.table[i].lexema == 'l')
						out << "push offset " << idT.table[lexT.table[i].idxTI].id << "\n";
					if (lexT.table[i].lexema == '@')
					{
						out << "call " << idT.table[lexT.table[i].idxTI].id << "\n";
						out << "push eax\n";
					}
					if (lexT.table[i].lexema == '+')
					{
						out << "pop eax\n";
						out << "pop ebx\n";
						out << "add eax, ebx\n";
						out << "push eax\n";
					}
					if (lexT.table[i].lexema == '-')
					{
						out << "pop ebx\n";
						out << "pop eax\n";
						out << "sub eax, ebx\n";
						out << "push eax\n";
					}
					if (lexT.table[i].lexema == '*')
					{
						out << "pop eax\n";
						out << "pop ebx\n";
						out << "mul ebx\n";
						out << "push eax\n";
					}
					i++;
				}
				out << "pop " << idT.table[lexT.table[indOflex].idxTI].id << "\n\n";
			}
		}
		out << "end main";
	}
}
//TODO: вставить стандартную либц в шапку