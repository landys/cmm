%{
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

%}

digit [0-9]
number {digit}+
letter [a-zA-Z]
identifier {letter}+
newline \n
whitespace [ \t]+

%%
"/*" {           
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
}					
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MULT;}
"/" {return DIV;}
";" {return SEMI;}
"(" {return SLB;}
")" {return SRB;}
"{" {return BLB;}
"}" {return BRB;}
"=" {return ASSIGN;}
"main" {return MAIN;}
"return" {return RETURN;}
"int" {return INT;}
"void" {return VOID;}
"input" {return INPUT;}
"output" {return OUTPUT;}
{number} {
	strcpy(tokenString, yytext);	
	return NUM;
}
{identifier} {
	strcpy(tokenString, yytext);
	return ID;
}
{newline} {lineno++;}
{whitespace} {}
. {
	printf("ERROR %d: Line %d: Not identified characters.\n", ++nError, lineno);
	return ERROR;
}

%%

int yywrap()
{
	return 1;
}

