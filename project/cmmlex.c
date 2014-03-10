/****************************************************************************
*                     U N R E G I S T E R E D   C O P Y
* 
* You are on day 105 of your 30 day trial period.
* 
* This file was produced by an UNREGISTERED COPY of Parser Generator. It is
* for evaluation purposes only. If you continue to use Parser Generator 30
* days after installation then you are required to purchase a license. For
* more information see the online help or go to the Bumble-Bee Software
* homepage at:
* 
* http://www.bumblebeesoftware.com
* 
* This notice must remain present in the file. It cannot be removed.
****************************************************************************/

/****************************************************************************
* cmmlex.c
* C source file generated from cmmlex.l.
* 
* Date: 06/26/06
* Time: 17:06:07
* 
* ALex Version: 2.07
****************************************************************************/

#include <yylex.h>

/* namespaces */
#if defined(__cplusplus) && defined(YYSTDCPPLIB)
using namespace std;
#endif
#if defined(__cplusplus) && defined(YYNAMESPACE)
using namespace yl;
#endif

#define YYFASTLEXER

#line 1 ".\\cmmlex.l"

/****************************************************************************
cmmlex.l
ParserWizard generated Lex file.
Author: Jinde Wang
Date: 2006年6月26日
****************************************************************************/

#include "cmmyacc.h"
#include <stdlib.h>
#include <string.h>

/* 记录错误号 */
extern int nError;	
/* 当前Token名 */
extern char tokenString[256];
/* 当前行号 */
extern int lineno;


#line 61 "cmmlex.c"
/* repeated because of possible precompiled header */
#include <yylex.h>

/* namespaces */
#if defined(__cplusplus) && defined(YYSTDCPPLIB)
using namespace std;
#endif
#if defined(__cplusplus) && defined(YYNAMESPACE)
using namespace yl;
#endif

#define YYFASTLEXER

#include ".\cmmlex.h"

#ifndef YYTEXT_SIZE
#define YYTEXT_SIZE 100
#endif
#ifndef YYUNPUT_SIZE
#define YYUNPUT_SIZE YYTEXT_SIZE
#endif
#ifndef YYTEXT_MAX
#define YYTEXT_MAX 0
#endif
#ifndef YYUNPUT_MAX
#define YYUNPUT_MAX YYTEXT_MAX
#endif

/* yytext */
static char YYNEAR yysatext[(YYTEXT_SIZE) + 1];		/* extra char for \0 */
char YYFAR *YYNEAR YYDCDECL yystext = yysatext;
char YYFAR *YYNEAR YYDCDECL yytext = yysatext;
int YYNEAR YYDCDECL yystext_size = (YYTEXT_SIZE);
int YYNEAR YYDCDECL yytext_size = (YYTEXT_SIZE);
int YYNEAR YYDCDECL yytext_max = (YYTEXT_MAX);

/* yystatebuf */
#if (YYTEXT_SIZE) != 0
static int YYNEAR yysastatebuf[(YYTEXT_SIZE)];
int YYFAR *YYNEAR YYDCDECL yysstatebuf = yysastatebuf;
int YYFAR *YYNEAR YYDCDECL yystatebuf = yysastatebuf;
#else
int YYFAR *YYNEAR YYDCDECL yysstatebuf = NULL;
int YYFAR *YYNEAR YYDCDECL yystatebuf = NULL;
#endif

/* yyunputbuf */
#if (YYUNPUT_SIZE) != 0
static int YYNEAR yysaunputbuf[(YYUNPUT_SIZE)];
int YYFAR *YYNEAR YYDCDECL yysunputbufptr = yysaunputbuf;
int YYFAR *YYNEAR YYDCDECL yyunputbufptr = yysaunputbuf;
#else
int YYFAR *YYNEAR YYDCDECL yysunputbufptr = NULL;
int YYFAR *YYNEAR YYDCDECL yyunputbufptr = NULL;
#endif
int YYNEAR YYDCDECL yysunput_size = (YYUNPUT_SIZE);
int YYNEAR YYDCDECL yyunput_size = (YYUNPUT_SIZE);
int YYNEAR YYDCDECL yyunput_max = (YYUNPUT_MAX);

/* backwards compatability with lex */
#ifdef input
#ifdef YYPROTOTYPE
int YYCDECL yyinput(void)
#else
int YYCDECL yyinput()
#endif
{
	return input();
}
#else
#define input yyinput
#endif

#ifdef output
#ifdef YYPROTOTYPE
void YYCDECL yyoutput(int ch)
#else
void YYCDECL yyoutput(ch)
int ch;
#endif
{
	output(ch);
}
#else
#define output yyoutput
#endif

#ifdef unput
#ifdef YYPROTOTYPE
void YYCDECL yyunput(int ch)
#else
void YYCDECL yyunput(ch)
int ch;
#endif
{
	unput(ch);
}
#else
#define unput yyunput
#endif

#ifndef YYNBORLANDWARN
#ifdef __BORLANDC__
#pragma warn -rch		/* <warning: unreachable code> off */
#endif
#endif

#ifdef YYPROTOTYPE
int YYCDECL yylexeraction(int action)
#else
int YYCDECL yylexeraction(action)
int action;
#endif
{
	yyreturnflg = YYTRUE;
	switch (action) {
	case 1:
		{
#line 30 ".\\cmmlex.l"
           
	char c;
	int done = 0;
	do
	{
		while ((c=input()) != '*')
		{
			if (c == '\n')
			{
				lineno++;
			}
		};
		while ((c=input()) == '*');
		if (c == '/')
		{
			done = 1;
		}
	}
	while (!done);

#line 201 "cmmlex.c"
		}
		break;
	case 2:
		{
#line 50 ".\\cmmlex.l"
return PLUS;
#line 208 "cmmlex.c"
		}
		break;
	case 3:
		{
#line 51 ".\\cmmlex.l"
return MINUS;
#line 215 "cmmlex.c"
		}
		break;
	case 4:
		{
#line 52 ".\\cmmlex.l"
return MULT;
#line 222 "cmmlex.c"
		}
		break;
	case 5:
		{
#line 53 ".\\cmmlex.l"
return DIV;
#line 229 "cmmlex.c"
		}
		break;
	case 6:
		{
#line 54 ".\\cmmlex.l"
return SEMI;
#line 236 "cmmlex.c"
		}
		break;
	case 7:
		{
#line 55 ".\\cmmlex.l"
return SLB;
#line 243 "cmmlex.c"
		}
		break;
	case 8:
		{
#line 56 ".\\cmmlex.l"
return SRB;
#line 250 "cmmlex.c"
		}
		break;
	case 9:
		{
#line 57 ".\\cmmlex.l"
return BLB;
#line 257 "cmmlex.c"
		}
		break;
	case 10:
		{
#line 58 ".\\cmmlex.l"
return BRB;
#line 264 "cmmlex.c"
		}
		break;
	case 11:
		{
#line 59 ".\\cmmlex.l"
return ASSIGN;
#line 271 "cmmlex.c"
		}
		break;
	case 12:
		{
#line 60 ".\\cmmlex.l"
return MAIN;
#line 278 "cmmlex.c"
		}
		break;
	case 13:
		{
#line 61 ".\\cmmlex.l"
return RETURN;
#line 285 "cmmlex.c"
		}
		break;
	case 14:
		{
#line 62 ".\\cmmlex.l"
return INT;
#line 292 "cmmlex.c"
		}
		break;
	case 15:
		{
#line 63 ".\\cmmlex.l"
return VOID;
#line 299 "cmmlex.c"
		}
		break;
	case 16:
		{
#line 64 ".\\cmmlex.l"
return INPUT;
#line 306 "cmmlex.c"
		}
		break;
	case 17:
		{
#line 65 ".\\cmmlex.l"
return OUTPUT;
#line 313 "cmmlex.c"
		}
		break;
	case 18:
		{
#line 66 ".\\cmmlex.l"

	strcpy(tokenString, yytext);	
	return NUM;

#line 323 "cmmlex.c"
		}
		break;
	case 19:
		{
#line 70 ".\\cmmlex.l"

	strcpy(tokenString, yytext);
	return ID;

#line 333 "cmmlex.c"
		}
		break;
	case 20:
		{
#line 74 ".\\cmmlex.l"
lineno++;
#line 340 "cmmlex.c"
		}
		break;
	case 21:
		{
#line 75 ".\\cmmlex.l"

#line 347 "cmmlex.c"
		}
		break;
	case 22:
		{
#line 76 ".\\cmmlex.l"

	printf("ERROR %d: Line %d: Not identified characters.\n", ++nError, lineno);
	return ERROR;

#line 357 "cmmlex.c"
		}
		break;
	default:
		yyassert(0);
		break;
	}
	yyreturnflg = YYFALSE;
	return 0;
}

#ifndef YYNBORLANDWARN
#ifdef __BORLANDC__
#pragma warn .rch		/* <warning: unreachable code> to the old state */
#endif
#endif
YYCONST yymatch_t YYNEARFAR YYBASED_CODE YYDCDECL yymatch[] = {
	0
};

int YYNEAR YYDCDECL yytransitionmax = 176;
YYCONST yytransition_t YYNEARFAR YYBASED_CODE YYDCDECL yytransition[] = {
	{ 0, 0 },
	{ 4, 1 },
	{ 5, 1 },
	{ 4, 4 },
	{ 12, 12 },
	{ 12, 12 },
	{ 12, 12 },
	{ 12, 12 },
	{ 12, 12 },
	{ 12, 12 },
	{ 12, 12 },
	{ 12, 12 },
	{ 12, 12 },
	{ 12, 12 },
	{ 29, 24 },
	{ 25, 17 },
	{ 26, 18 },
	{ 27, 19 },
	{ 30, 24 },
	{ 28, 20 },
	{ 23, 11 },
	{ 31, 25 },
	{ 32, 26 },
	{ 33, 27 },
	{ 4, 1 },
	{ 34, 28 },
	{ 4, 4 },
	{ 35, 29 },
	{ 36, 31 },
	{ 37, 32 },
	{ 38, 33 },
	{ 39, 34 },
	{ 6, 1 },
	{ 7, 1 },
	{ 8, 1 },
	{ 9, 1 },
	{ 40, 35 },
	{ 10, 1 },
	{ 41, 37 },
	{ 11, 1 },
	{ 12, 1 },
	{ 12, 1 },
	{ 12, 1 },
	{ 12, 1 },
	{ 12, 1 },
	{ 12, 1 },
	{ 12, 1 },
	{ 12, 1 },
	{ 12, 1 },
	{ 12, 1 },
	{ 42, 38 },
	{ 13, 1 },
	{ 43, 41 },
	{ 14, 1 },
	{ 44, 42 },
	{ 24, 16 },
	{ 0, 0 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 16, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 17, 1 },
	{ 15, 1 },
	{ 18, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 19, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 20, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 15, 1 },
	{ 21, 1 },
	{ 0, 0 },
	{ 22, 1 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 0, 0 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 },
	{ 15, 44 }
};

YYCONST yystate_t YYNEARFAR YYBASED_CODE YYDCDECL yystate[] = {
	{ 0, 0, 0 },
	{ -3, -8, 0 },
	{ 1, 0, 0 },
	{ 0, 0, 22 },
	{ 0, -6, 21 },
	{ 0, 0, 20 },
	{ 0, 0, 7 },
	{ 0, 0, 8 },
	{ 0, 0, 4 },
	{ 0, 0, 2 },
	{ 0, 0, 3 },
	{ 0, -22, 5 },
	{ 0, -44, 18 },
	{ 0, 0, 6 },
	{ 0, 0, 11 },
	{ 44, 0, 19 },
	{ 44, -55, 19 },
	{ 44, -82, 19 },
	{ 44, -101, 19 },
	{ 44, -84, 19 },
	{ 44, -92, 19 },
	{ 0, 0, 9 },
	{ 0, 0, 10 },
	{ 0, 0, 1 },
	{ 44, -98, 19 },
	{ 44, -84, 19 },
	{ 44, -94, 19 },
	{ 44, -93, 19 },
	{ 44, -80, 19 },
	{ 44, -90, 19 },
	{ 44, 0, 14 },
	{ 44, -82, 19 },
	{ 44, -83, 19 },
	{ 44, -87, 19 },
	{ 44, -69, 19 },
	{ 44, -80, 19 },
	{ 44, 0, 12 },
	{ 44, -79, 19 },
	{ 44, -64, 19 },
	{ 44, 0, 15 },
	{ 44, 0, 16 },
	{ 44, -64, 19 },
	{ 44, -56, 19 },
	{ 44, 0, 17 },
	{ 0, 53, 13 }
};

YYCONST yybackup_t YYNEARFAR YYBASED_CODE YYDCDECL yybackup[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};

#line 81 ".\\cmmlex.l"


int yywrap()
{
	return 1;
}


