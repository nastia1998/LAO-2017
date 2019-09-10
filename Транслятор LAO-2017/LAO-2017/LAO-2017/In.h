#pragma once
#include "stdafx.h"
#include "LT.h"
#define IN_MAX_LEN_TEXT 1024*1024		//максимальный размер исходного кода 1МБ
#define IN_CODE_ENDL	'\n'			//символ конца строки
#define STR_NUMB_SEP	'|'				// сепаратор для новой строки
#define IN_CODE_SPACE	' '				//проблем
#define IN_WORD_MAX_LEN 255				//максимальный размер слова

//таблица проверки взодной информации, индекс = код (Windows 1251) символа
//значение IN::F - запрещенный символ, IN::T  - разрешенный символ,  IN::S - сепаратор,
//		если 0<=значение <256 - то вводится данное значение
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

// 0x0a - перевод строки,  0x22 - "
// IN::S -- сепараторы   (  )	*	+	,	-	;	=	{	}  /
namespace In
{
	struct IN
	{
		enum { T = 1, F = 2, S = 3 };		//Т - допустимый символ, F - недопустимый, S - сепаратор
		int size;							//размер исходного кода
		int lines;							//кол-во строк
		std::queue<std::string> Words;
		std::queue<int> Line;
		int code[256] = IN_CODE_TABLE;		//таблица проврки
	};
	IN getin(wchar_t infile[]);				//ввести и проверить входной поток
};