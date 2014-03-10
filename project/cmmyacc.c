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
* cmmyacc.c
* C source file generated from cmmyacc.y.
* 
* Date: 06/26/06
* Time: 19:14:11
* 
* AYACC Version: 2.07
****************************************************************************/

#include <yypars.h>

/* namespaces */
#if defined(__cplusplus) && defined(YYSTDCPPLIB)
using namespace std;
#endif
#if defined(__cplusplus) && defined(YYNAMESPACE)
using namespace yl;
#endif

#define YYFASTPARSER

/* repeated because of possible precompiled header */
#include <yypars.h>

/* namespaces */
#if defined(__cplusplus) && defined(YYSTDCPPLIB)
using namespace std;
#endif
#if defined(__cplusplus) && defined(YYNAMESPACE)
using namespace yl;
#endif

#define YYFASTPARSER

#include ".\cmmyacc.h"

#line 5 ".\\cmmyacc.y"

/****************************************************************************
cmmyacc.y
ParserWizard generated YACC file.
Author: Jinde Wang
Date: 2006年6月26日
****************************************************************************/

#include "code.h"
#include "cmmlex.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YYSTYPE TreeNode*

int nError = 0;	/* 记录错误号 */
static int hasReturn = 0;	/* 标志程序中有无return语句 */
static TableNode* tableHead = NULL;	/* 符号表头结点 */
static TreeNode* treeHead = NULL;	/* 语法树头结点 */
static indentno = 0;	/* 打印语法树时的缩进 */
static char* tempToken[64];	/* 保存临时Token名 */
static int tempno[64];	/* 保存对应的Token对应的行号 */
static int top = -1;	/* 上面两个数组中的当前下标,实现堆栈功能 */
char tokenString[255];	/* 当前Token名 */
int lineno = 1;	/* 当前行号 */

/* 查询符号表,返回数据类型,查不到,返加VoidT */
int lookup(char* name)
{
	TableNode* p = tableHead;
	
	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0)
		{
			return p->eType;
		}
		p = p->next;
	}
	return VoidT;
}

/* 插入到符号表,成功返回1,否则返回0 */
int insert(char* name, int a)
{
	TableNode* p;
	if (lookup(name) != VoidT)
	{
		return 0;
	}
	
	p = (TableNode*)malloc(sizeof(TableNode));
	if (p == NULL)
	{
		printf("ERROR %d: Malloc--Out of memory.\n", ++nError);
		exit(-1);
	}
	
	strcpy(p->name, name);
	p->eType = a;
	p->next = tableHead;
	tableHead = p;

	return 1;
}

/*　打印出符号表到文件 */
void printTable(TableNode* table, FILE* pf)
{
	while (table != NULL)
	{
		fprintf(pf, "  %s ", table->name);
		switch (table->eType)
		{
			case IntT:
				fprintf(pf, "IntT\n");
				break;
			case VoidT:
				fprintf(pf, "VoidT\n");
				break;
			default:
				fprintf(pf, "Not identified type\n");
				break;
		}
		table = table->next;
	}
}

/* 创建新的表达式结点，返回指向结点的指针 */
TreeNode* newExpNode(ExpKind kind)
{
	TreeNode* t = (TreeNode*)malloc(sizeof(TreeNode));
	int i;
	
	if (t == NULL)
	{
		printf("Error %d: Malloc--Out of memory.\n", ++nError);
		return NULL;
	}
	
	for (i=0; i<MAXCHILDREN; i++)
	{
		t->child[i] = NULL;
	}
	t->sibling = NULL;
	t->nodekind = ExpK;
	t->kind.stmt = kind;
	t->lineno = lineno;
	t->type = VoidT;
	
	return t;
}

/* 创建新的语句结点，返回指向结点的指针 */
TreeNode* newStmtNode(StmtKind kind)
{
	TreeNode* t = (TreeNode*)malloc(sizeof(TreeNode));
	int i;
	
	if (t == NULL)
	{
		printf("ERROR %d: Malloc--Out of memory.\n", ++nError);
		return NULL;
	}
	
	for (i=0; i<MAXCHILDREN; i++)
	{
		t->child[i] = NULL;
	}
	t->sibling = NULL;
	t->nodekind = StmtK;
	t->kind.stmt = kind;
	t->lineno = lineno;
	
	return t;
}

/* 拷备字符串，返回新创建的字符串的指针 */
char* copyString(char* s)
{ 
	int n;
	char * t;
	
	if (s == NULL)
	{
		return NULL;
	}
	n = strlen(s)+1;
	t = (char*)malloc(n);
	if (t == NULL)
	{
		printf("ERROR %d: Malloc--Out of memory.\n", ++nError);
		return NULL;
	}
	
	strcpy(t, s);
	return t;
}

/* 打印一个语法树结点到文件中 */
void printToken(TokenType token, const char* tokenString, FILE* pf)
{
	switch (token)
	{
	case RETURN:
	case INPUT:
	case OUTPUT:
		fprintf(pf, "reserved word: %s\n", tokenString);
		break;
	case ASSIGN: fprintf(pf, "=\n"); break;
	case SLB: fprintf(pf, "(\n"); break;
	case SRB: fprintf(pf, ")\n"); break;
	case SEMI: fprintf(pf, ";\n"); break;
	case PLUS: fprintf(pf, "+\n"); break;
	case MINUS: fprintf(pf, "-\n"); break;
	case MULT: fprintf(pf, "*\n"); break;
	case DIV: fprintf(pf, "/\n"); break;
	case NUM:
		fprintf(pf, "NUM, val= %s\n",tokenString);
		break;
	case ID:
		fprintf(pf, "ID, name= %s\n",tokenString);
		break;
	case ERROR:
		fprintf(pf, "ERROR: %s\n",tokenString);
		break;
	default: /* should never happen */
		fprintf(pf, "Unknown token: %d\n", token);
	}
}

/* 打印空格到文件中 */
static void printSpaces(FILE* pf)
{
	int i;
	for (i=0; i<indentno; i++)
	{
		fprintf(pf, " ");
	}
}

/* 打印语法树到文件中，前序遍历,子结点比父结点缩进两格 */
void printTree(TreeNode* tree, FILE* pf)
{ 
	int i;
	indentno += 2;	/* 缩进加2 */
	while (tree != NULL)
	{
		printSpaces(pf);	/* 打印空格 */
		if (tree->nodekind == StmtK)
		{ 
			switch (tree->kind.stmt) 
			{
			case ReturnK:	/* 返回语句 */
				fprintf(pf, "ReturnK\n");
				break;
			case AssignK:	/* 赋值语句 */
				fprintf(pf, "Assign to: %s\n",tree->attr.name);
				break;
			case InputK:	/* 输入语句 */
				fprintf(pf, "Input\n");
				break;
			case OutputK:	/* 输出语句 */
				fprintf(pf, "Output\n");
				break;
			default:
				fprintf(pf, "Unknown ExpNode kind\n");
				break;
			}
		}
		else if (tree->nodekind == ExpK)
		{ 
			switch (tree->kind.exp) 
			{
			case OpK:	/* 动算结点,包括加减乘除 */
				fprintf(pf, "Op: ");
				printToken(tree->attr.op,"\0", pf);
				break;
			case ConstK:	/* 常数结点 */
				fprintf(pf, "Const: %d\n",tree->attr.val);
				break;
			case IdK:	/* 变量结点 */
				fprintf(pf, "Id: %s\n",tree->attr.name);
				break;
			default:
				fprintf(pf, "Unknown ExpNode kind\n");
				break;
			}
		}
		else
		{
			fprintf(pf, "Unknown node kind\n");
		}
		for (i=0; i<MAXCHILDREN; i++)	/* 遍历子树 */
		{
			printTree(tree->child[i], pf);	/* 递归 */
		}
		tree = tree->sibling;	/* 转移到其兄弟树,即对应的下一条C语句 */
	}
	indentno -= 2;	/* 缩进减2 */
 }



#line 322 "cmmyacc.c"
#ifndef YYSTYPE
#define YYSTYPE int
#endif
#ifndef YYSTACK_SIZE
#define YYSTACK_SIZE 100
#endif
#ifndef YYSTACK_MAX
#define YYSTACK_MAX 0
#endif

/* (state) stack */
#if (YYSTACK_SIZE) != 0
static yystack_t YYNEAR yystack[(YYSTACK_SIZE)];
yystack_t YYFAR *YYNEAR YYDCDECL yysstackptr = yystack;
yystack_t YYFAR *YYNEAR YYDCDECL yystackptr = yystack;
#else
yystack_t YYFAR *YYNEAR YYDCDECL yysstackptr = NULL;
yystack_t YYFAR *YYNEAR YYDCDECL yystackptr = NULL;
#endif

/* attribute stack */
#if (YYSTACK_SIZE) != 0
static YYSTYPE YYNEAR yyattributestack[(YYSTACK_SIZE)];
#ifdef YYPROTOTYPE
void YYFAR *YYNEAR YYDCDECL yysattributestackptr = yyattributestack;
void YYFAR *YYNEAR YYDCDECL yyattributestackptr = yyattributestack;
#else
char YYFAR *YYNEAR YYDCDECL yysattributestackptr = (char YYFAR *) yyattributestack;
char YYFAR *YYNEAR YYDCDECL yyattributestackptr = (char YYFAR *) yyattributestack;
#endif
#else
#ifdef YYPROTOTYPE
void YYFAR *YYNEAR YYDCDECL yysattributestackptr = NULL;
void YYFAR *YYNEAR YYDCDECL yyattributestackptr = NULL;
#else
char YYFAR *YYNEAR YYDCDECL yysattributestackptr = NULL;
char YYFAR *YYNEAR YYDCDECL yyattributestackptr = NULL;
#endif
#endif

int YYNEAR YYDCDECL yysstack_size = (YYSTACK_SIZE);
int YYNEAR YYDCDECL yystack_size = (YYSTACK_SIZE);
int YYNEAR YYDCDECL yystack_max = (YYSTACK_MAX);

/* attributes */
YYSTYPE YYNEAR yyval;
YYSTYPE YYNEAR yylval;
#ifdef YYPROTOTYPE
void YYFAR *YYNEAR YYDCDECL yyvalptr = &yyval;
void YYFAR *YYNEAR YYDCDECL yylvalptr = &yylval;
#else
char YYFAR *YYNEAR YYDCDECL yyvalptr = (char *) &yyval;
char YYFAR *YYNEAR YYDCDECL yylvalptr = (char *) &yylval;
#endif

size_t YYNEAR YYDCDECL yyattribute_size = sizeof(YYSTYPE);

/* yyattribute */
#ifdef YYDEBUG
#ifdef YYPROTOTYPE
static YYSTYPE YYFAR *yyattribute1(int index)
#else
static YYSTYPE YYFAR *yyattribute1(index)
int index;
#endif
{
	YYSTYPE YYFAR *p = &((YYSTYPE YYFAR *) yyattributestackptr)[yytop + index];
	return p;
}
#define yyattribute(index) (*yyattribute1(index))
#else
#define yyattribute(index) (((YYSTYPE YYFAR *) yyattributestackptr)[yytop + (index)])
#endif

#ifdef YYDEBUG
#ifdef YYPROTOTYPE
static void yyinitdebug(YYSTYPE YYFAR **p, int count)
#else
static void yyinitdebug(p, count)
YYSTYPE YYFAR **p;
int count;
#endif
{
	int i;
	yyassert(p != NULL);
	yyassert(count >= 1);

	for (i = 0; i < count; i++) {
		p[i] = &((YYSTYPE YYFAR *) yyattributestackptr)[yytop + i - (count - 1)];
	}
}
#endif

#ifdef YYPROTOTYPE
void YYCDECL yyparseraction(int action)
#else
void YYCDECL yyparseraction(action)
int action;
#endif
{
	switch (action) {
	case 0:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[5];
			yyinitdebug(yya, 5);
#endif
			{
#line 291 ".\\cmmyacc.y"

		treeHead = yyattribute(3 - 4);	
	
#line 435 "cmmyacc.c"
			}
		}
		break;
	case 1:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 301 ".\\cmmyacc.y"

		if (insert(tokenString, IntT) == 0)
		{
			printf("ERROR %d: Line %d Duplicated definition.\n", ++nError, lineno);
		}
	
#line 453 "cmmyacc.c"
			}
		}
		break;
	case 2:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 311 ".\\cmmyacc.y"

		YYSTYPE t = yyattribute(1 - 2);
		if (t != NULL)
		{
			while (t->sibling != NULL)
			{
				t = t->sibling;
			}
			t->sibling = yyattribute(2 - 2);
			yyval = yyattribute(1 - 2);
		}
		else
		{
			yyval = yyattribute(2 - 2);
		}
	
#line 481 "cmmyacc.c"
			}
		}
		break;
	case 3:
		{
#line 327 ".\\cmmyacc.y"
 yyval = NULL; 
#line 489 "cmmyacc.c"
		}
		break;
	case 4:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 330 ".\\cmmyacc.y"
 yyval = yyattribute(1 - 1); 
#line 501 "cmmyacc.c"
			}
		}
		break;
	case 5:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 331 ".\\cmmyacc.y"
 yyval = yyattribute(1 - 1); 
#line 514 "cmmyacc.c"
			}
		}
		break;
	case 6:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 332 ".\\cmmyacc.y"
 yyval = yyattribute(1 - 1); 
#line 527 "cmmyacc.c"
			}
		}
		break;
	case 7:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 333 ".\\cmmyacc.y"
 yyval = yyattribute(1 - 1); 
#line 540 "cmmyacc.c"
			}
		}
		break;
	case 8:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 336 ".\\cmmyacc.y"
 yyval = yyattribute(1 - 2); 
#line 553 "cmmyacc.c"
			}
		}
		break;
	case 9:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 337 ".\\cmmyacc.y"
 yyval = NULL; 
#line 566 "cmmyacc.c"
			}
		}
		break;
	case 10:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 341 ".\\cmmyacc.y"

		yyval = newStmtNode(ReturnK);
		yyval->child[0] = yyattribute(2 - 3);
		hasReturn = 1;
	
#line 583 "cmmyacc.c"
			}
		}
		break;
	case 11:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[3];
			yyinitdebug(yya, 3);
#endif
			{
#line 348 ".\\cmmyacc.y"
 yyval = yyattribute(1 - 2); 
#line 596 "cmmyacc.c"
			}
		}
		break;
	case 12:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 352 ".\\cmmyacc.y"

		yyval = newStmtNode(InputK);
	
#line 611 "cmmyacc.c"
			}
		}
		break;
	case 13:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[6];
			yyinitdebug(yya, 6);
#endif
			{
#line 358 ".\\cmmyacc.y"

		yyval = newStmtNode(OutputK);
		yyval->child[0] = yyattribute(3 - 5);
	
#line 627 "cmmyacc.c"
			}
		}
		break;
	case 14:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 364 ".\\cmmyacc.y"
 yyval = yyattribute(1 - 1); 
#line 640 "cmmyacc.c"
			}
		}
		break;
	case 15:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 365 ".\\cmmyacc.y"
 yyval = yyattribute(1 - 1); 
#line 653 "cmmyacc.c"
			}
		}
		break;
	case 16:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 369 ".\\cmmyacc.y"

		tempToken[++top] = copyString(tokenString);
		tempno[top] = lineno;
		if (lookup(tokenString) == VoidT)
		{
			printf("ERROR %d: Line %d: ID %s is not defined.\n", ++nError, lineno, tokenString);
		}
	
#line 673 "cmmyacc.c"
			}
		}
		break;
	case 17:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[5];
			yyinitdebug(yya, 5);
#endif
			{
#line 378 ".\\cmmyacc.y"

		yyval = newStmtNode(AssignK);
		yyval->child[0] = yyattribute(4 - 4);
		yyval->lineno = tempno[top];
		yyval->attr.name = tempToken[top--];
	
#line 691 "cmmyacc.c"
			}
		}
		break;
	case 18:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 387 ".\\cmmyacc.y"

		yyval = yyattribute(2 - 3);
		yyval->child[0] = yyattribute(1 - 3);
		yyval->child[1] = yyattribute(3 - 3);
	
#line 708 "cmmyacc.c"
			}
		}
		break;
	case 19:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 393 ".\\cmmyacc.y"

		yyval = yyattribute(1 - 1);
	
#line 723 "cmmyacc.c"
			}
		}
		break;
	case 20:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 399 ".\\cmmyacc.y"

		yyval = newExpNode(OpK);
		yyval->attr.op = PLUS;
	
#line 739 "cmmyacc.c"
			}
		}
		break;
	case 21:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 404 ".\\cmmyacc.y"

		yyval = newExpNode(OpK);
		yyval->attr.op = MINUS;
	
#line 755 "cmmyacc.c"
			}
		}
		break;
	case 22:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 411 ".\\cmmyacc.y"

		yyval = yyattribute(2 - 3);
		yyval->child[0] = yyattribute(1 - 3);
		yyval->child[1] = yyattribute(3 - 3);
	
#line 772 "cmmyacc.c"
			}
		}
		break;
	case 23:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 417 ".\\cmmyacc.y"

		yyval = yyattribute(1 - 1);
	
#line 787 "cmmyacc.c"
			}
		}
		break;
	case 24:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 423 ".\\cmmyacc.y"

		yyval = newExpNode(OpK);
		yyval->attr.op = MULT;
	
#line 803 "cmmyacc.c"
			}
		}
		break;
	case 25:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 428 ".\\cmmyacc.y"

		yyval = newExpNode(OpK);
		yyval->attr.op = DIV;
	
#line 819 "cmmyacc.c"
			}
		}
		break;
	case 26:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 435 ".\\cmmyacc.y"

		yyval = newExpNode(ConstK);
		yyval->attr.val = atoi(tokenString);
	
#line 835 "cmmyacc.c"
			}
		}
		break;
	case 27:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 440 ".\\cmmyacc.y"

		if (lookup(tokenString) == VoidT)
		{
			printf("ERROR %d: Line %d: ID %s is not defined.\n", ++nError, lineno, tokenString);
		}
		yyval = newExpNode(IdK);
		yyval->attr.name = copyString(tokenString);
	
#line 855 "cmmyacc.c"
			}
		}
		break;
	case 28:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[4];
			yyinitdebug(yya, 4);
#endif
			{
#line 449 ".\\cmmyacc.y"

		yyval = yyattribute(2 - 3);
	
#line 870 "cmmyacc.c"
			}
		}
		break;
	case 29:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 453 ".\\cmmyacc.y"

		yyval = yyattribute(1 - 1);
	
#line 885 "cmmyacc.c"
			}
		}
		break;
	case 30:
		{
#ifdef YYDEBUG
			YYSTYPE YYFAR *yya[2];
			yyinitdebug(yya, 2);
#endif
			{
#line 457 ".\\cmmyacc.y"

		yyval = NULL;
	
#line 900 "cmmyacc.c"
			}
		}
		break;
	default:
		yyassert(0);
		break;
	}
}
#ifdef YYDEBUG
YYCONST yysymbol_t YYNEARFAR YYBASED_CODE YYDCDECL yysymbol[] = {
	{ "$end", 0 },
	{ "error", 256 },
	{ "SEMI", 257 },
	{ "SLB", 258 },
	{ "SRB", 259 },
	{ "BLB", 260 },
	{ "BRB", 261 },
	{ "MAIN", 262 },
	{ "RETURN", 263 },
	{ "INT", 264 },
	{ "VOID", 265 },
	{ "INPUT", 266 },
	{ "OUTPUT", 267 },
	{ "PLUS", 268 },
	{ "MINUS", 269 },
	{ "MULT", 270 },
	{ "DIV", 271 },
	{ "ASSIGN", 272 },
	{ "ID", 273 },
	{ "NUM", 274 },
	{ "ERROR", 275 },
	{ NULL, 0 }
};

YYCONST char *YYCONST YYNEARFAR YYBASED_CODE YYDCDECL yyrule[] = {
	"$accept: program",
	"program: main_decl",
	"main_decl: type_spec fun_ID SLB params SRB compound_stmt",
	"type_spec: INT",
	"fun_ID: MAIN",
	"params: VOID",
	"params:",
	"compound_stmt: BLB var_decl_list stmt_list BRB",
	"var_decl_list: var_decl_list var_decl",
	"var_decl_list:",
	"$$1:",
	"var_decl: type_spec ID $$1 SEMI",
	"stmt_list: stmt_list stmt",
	"stmt_list:",
	"stmt: exp_stmt",
	"stmt: I_stmt",
	"stmt: O_stmt",
	"stmt: ret_stmt",
	"exp_stmt: exp SEMI",
	"exp_stmt: SEMI",
	"ret_stmt: RETURN exp SEMI",
	"I_stmt: I_exp SEMI",
	"I_exp: INPUT SLB SRB",
	"O_stmt: OUTPUT SLB exp SRB SEMI",
	"exp: asgn_exp",
	"exp: algo_exp",
	"$$2:",
	"asgn_exp: ID $$2 ASSIGN exp",
	"algo_exp: algo_exp addop term",
	"algo_exp: term",
	"addop: PLUS",
	"addop: MINUS",
	"term: term multop factor",
	"term: factor",
	"multop: MULT",
	"multop: DIV",
	"factor: NUM",
	"factor: ID",
	"factor: SLB exp SRB",
	"factor: I_exp",
	"factor: ERROR"
};
#endif

YYCONST yyreduction_t YYNEARFAR YYBASED_CODE YYDCDECL yyreduction[] = {
	{ 0, 1, -1 },
	{ 1, 1, -1 },
	{ 2, 6, -1 },
	{ 3, 1, -1 },
	{ 4, 1, -1 },
	{ 5, 1, -1 },
	{ 5, 0, -1 },
	{ 6, 4, 0 },
	{ 7, 2, -1 },
	{ 7, 0, -1 },
	{ 9, 0, 1 },
	{ 8, 4, -1 },
	{ 10, 2, 2 },
	{ 10, 0, 3 },
	{ 11, 1, 4 },
	{ 11, 1, 5 },
	{ 11, 1, 6 },
	{ 11, 1, 7 },
	{ 12, 2, 8 },
	{ 12, 1, 9 },
	{ 13, 3, 10 },
	{ 14, 2, 11 },
	{ 15, 3, 12 },
	{ 16, 5, 13 },
	{ 17, 1, 14 },
	{ 17, 1, 15 },
	{ 19, 0, 16 },
	{ 18, 4, 17 },
	{ 20, 3, 18 },
	{ 20, 1, 19 },
	{ 21, 1, 20 },
	{ 21, 1, 21 },
	{ 22, 3, 22 },
	{ 22, 1, 23 },
	{ 23, 1, 24 },
	{ 23, 1, 25 },
	{ 24, 1, 26 },
	{ 24, 1, 27 },
	{ 24, 3, 28 },
	{ 24, 1, 29 },
	{ 24, 1, 30 }
};

int YYNEAR YYDCDECL yytokenaction_size = 37;
YYCONST yytokenaction_t YYNEARFAR YYBASED_CODE YYDCDECL yytokenaction[] = {
	{ 58, YYAT_SHIFT, 19 },
	{ 15, YYAT_SHIFT, 18 },
	{ 60, YYAT_SHIFT, 50 },
	{ 60, YYAT_SHIFT, 51 },
	{ 62, YYAT_SHIFT, 64 },
	{ 15, YYAT_SHIFT, 20 },
	{ 57, YYAT_SHIFT, 62 },
	{ 15, YYAT_SHIFT, 21 },
	{ 58, YYAT_SHIFT, 22 },
	{ 36, YYAT_SHIFT, 50 },
	{ 36, YYAT_SHIFT, 51 },
	{ 15, YYAT_SHIFT, 23 },
	{ 35, YYAT_SHIFT, 47 },
	{ 35, YYAT_SHIFT, 48 },
	{ 52, YYAT_SHIFT, 59 },
	{ 58, YYAT_SHIFT, 24 },
	{ 58, YYAT_SHIFT, 25 },
	{ 58, YYAT_SHIFT, 26 },
	{ 44, YYAT_SHIFT, 58 },
	{ 42, YYAT_SHIFT, 56 },
	{ 41, YYAT_SHIFT, 55 },
	{ 39, YYAT_SHIFT, 54 },
	{ 38, YYAT_SHIFT, 53 },
	{ 33, YYAT_SHIFT, 46 },
	{ 32, YYAT_SHIFT, 45 },
	{ 24, YYAT_REDUCE, 26 },
	{ 23, YYAT_SHIFT, 43 },
	{ 22, YYAT_SHIFT, 42 },
	{ 14, YYAT_SHIFT, 17 },
	{ 13, YYAT_SHIFT, 1 },
	{ 10, YYAT_SHIFT, 11 },
	{ 9, YYAT_SHIFT, 10 },
	{ 7, YYAT_SHIFT, 8 },
	{ 6, YYAT_SHIFT, 7 },
	{ 4, YYAT_SHIFT, 5 },
	{ 2, YYAT_ACCEPT, 0 },
	{ 0, YYAT_SHIFT, 1 }
};

YYCONST yystateaction_t YYNEARFAR YYBASED_CODE YYDCDECL yystateaction[] = {
	{ -228, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 3 },
	{ 35, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 1 },
	{ -228, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 4 },
	{ -225, 1, YYAT_ERROR, 0 },
	{ -233, 1, YYAT_REDUCE, 6 },
	{ 0, 0, YYAT_REDUCE, 5 },
	{ -228, 1, YYAT_ERROR, 0 },
	{ -230, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 9 },
	{ 0, 0, YYAT_REDUCE, 2 },
	{ -235, 1, YYAT_REDUCE, 13 },
	{ -245, 1, YYAT_ERROR, 0 },
	{ -256, 1, YYAT_DEFAULT, 58 },
	{ 0, 0, YYAT_REDUCE, 8 },
	{ 0, 0, YYAT_REDUCE, 10 },
	{ 0, 0, YYAT_REDUCE, 19 },
	{ 0, 0, YYAT_DEFAULT, 58 },
	{ 0, 0, YYAT_REDUCE, 7 },
	{ 0, 0, YYAT_DEFAULT, 58 },
	{ -231, 1, YYAT_ERROR, 0 },
	{ -232, 1, YYAT_ERROR, 0 },
	{ -247, 1, YYAT_REDUCE, 37 },
	{ 0, 0, YYAT_REDUCE, 36 },
	{ 0, 0, YYAT_REDUCE, 40 },
	{ 0, 0, YYAT_REDUCE, 12 },
	{ 0, 0, YYAT_REDUCE, 14 },
	{ 0, 0, YYAT_REDUCE, 15 },
	{ 0, 0, YYAT_REDUCE, 16 },
	{ 0, 0, YYAT_REDUCE, 17 },
	{ -233, 1, YYAT_ERROR, 0 },
	{ -234, 1, YYAT_REDUCE, 39 },
	{ 0, 0, YYAT_REDUCE, 24 },
	{ -256, 1, YYAT_REDUCE, 25 },
	{ -261, 1, YYAT_REDUCE, 29 },
	{ 0, 0, YYAT_REDUCE, 33 },
	{ -235, 1, YYAT_ERROR, 0 },
	{ -238, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 39 },
	{ -237, 1, YYAT_ERROR, 0 },
	{ -240, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_DEFAULT, 58 },
	{ -254, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 18 },
	{ 0, 0, YYAT_REDUCE, 21 },
	{ 0, 0, YYAT_REDUCE, 30 },
	{ 0, 0, YYAT_REDUCE, 31 },
	{ 0, 0, YYAT_DEFAULT, 52 },
	{ 0, 0, YYAT_REDUCE, 34 },
	{ 0, 0, YYAT_REDUCE, 35 },
	{ -259, 1, YYAT_DEFAULT, 58 },
	{ 0, 0, YYAT_REDUCE, 11 },
	{ 0, 0, YYAT_REDUCE, 38 },
	{ 0, 0, YYAT_REDUCE, 20 },
	{ 0, 0, YYAT_REDUCE, 22 },
	{ -253, 1, YYAT_ERROR, 0 },
	{ -258, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 37 },
	{ -268, 1, YYAT_REDUCE, 28 },
	{ 0, 0, YYAT_REDUCE, 32 },
	{ -253, 1, YYAT_ERROR, 0 },
	{ 0, 0, YYAT_REDUCE, 27 },
	{ 0, 0, YYAT_REDUCE, 23 }
};

int YYNEAR YYDCDECL yynontermgoto_size = 32;

YYCONST yynontermgoto_t YYNEARFAR YYBASED_CODE YYDCDECL yynontermgoto[] = {
	{ 15, 27 },
	{ 15, 28 },
	{ 15, 31 },
	{ 15, 29 },
	{ 15, 33 },
	{ 15, 30 },
	{ 15, 32 },
	{ 58, 63 },
	{ 58, 34 },
	{ 13, 14 },
	{ 58, 35 },
	{ 52, 40 },
	{ 58, 36 },
	{ 49, 60 },
	{ 13, 16 },
	{ 49, 37 },
	{ 13, 15 },
	{ 0, 2 },
	{ 0, 3 },
	{ 0, 4 },
	{ 52, 61 },
	{ 60, 52 },
	{ 43, 57 },
	{ 35, 49 },
	{ 24, 44 },
	{ 21, 41 },
	{ 19, 39 },
	{ 17, 38 },
	{ 11, 13 },
	{ 10, 12 },
	{ 7, 9 },
	{ 4, 6 }
};

YYCONST yystategoto_t YYNEARFAR YYBASED_CODE YYDCDECL yystategoto[] = {
	{ 16, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 27, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 25, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 23, -1 },
	{ 21, -1 },
	{ 0, -1 },
	{ 6, -1 },
	{ 0, -1 },
	{ -11, 58 },
	{ 0, -1 },
	{ 18, -1 },
	{ 0, -1 },
	{ 9, 58 },
	{ 0, -1 },
	{ 8, 58 },
	{ 0, -1 },
	{ 0, -1 },
	{ 5, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 2, -1 },
	{ 0, 60 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 5, 58 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ -9, 52 },
	{ 0, -1 },
	{ 0, -1 },
	{ -4, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ -10, 49 },
	{ 0, -1 },
	{ -2, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 },
	{ 0, -1 }
};

YYCONST yydestructor_t YYNEARFAR *YYNEAR YYDCDECL yydestructorptr = NULL;

YYCONST yytokendest_t YYNEARFAR *YYNEAR YYDCDECL yytokendestptr = NULL;
int YYNEAR YYDCDECL yytokendest_size = 0;

YYCONST yytokendestbase_t YYNEARFAR *YYNEAR YYDCDECL yytokendestbaseptr = NULL;
int YYNEAR YYDCDECL yytokendestbase_size = 0;
#line 462 ".\\cmmyacc.y"


void yyerror(char* message)
{
	printf("ERROR %d: Line %d: Syntax error from yacc.\n", ++nError, lineno);
}

/* 主函数 */
int main(int argc, char** argv)
{
	FILE* pf;
	char fileName[255];
	int i;
	
	fileName[0] = '\0';
	/* 判断传给main函数的参数 */
	if (argc < 2)
	{
		printf("Input the source file:\n");
		scanf("%s", fileName);		
	}
	else
	{
		strcpy(fileName, argv[1]);
	}
	
	yyin = fopen(fileName, "r");
	if (yyin == NULL)
	{
		printf("ERROR: Cannot open file %s.\n", fileName);
		return 1;
	}
	
	/* 用来产生生成文件的文件名 */
	for (i=strlen(fileName)-1; i>=0; i--)
	{
		if (fileName[i] == '.')
		{
			fileName[i] = '\0';
			break;
		}
		if (fileName[i] == '/' || fileName[i] == '\\')
		{
			break;
		}
	}
	
	if (yyparse() == 0)
	{
		fclose(yyin);
		
		if (hasReturn == 0)
		{
			printf("ERROR %d: No return statement.\n", ++nError);
		}
		
		if (nError == 0)
		{
			printf("\nEnd of program, parse successfully.\n");
			printf("Continue to generate code files...\n\n");
		}
		else
		{
			printf("\nParse wrong.\n\n");
			return 0;
		}
		
		strcat(fileName, ".t");	/* 打印符号表和语法树的文件的文件名 */
		pf = fopen(fileName, "w");
		if (pf == NULL)
		{
			printf("ERROR %d: Cannot open file %s.\n", ++nError, fileName);
			printf("Cannot write symbol table and syntax tree to file %s.\n", fileName);
			return 1;
		}
		
		/* 打印符号表和语法树到文件 */
		fprintf(pf, "Symble Table as Below:\n");
		printTable(tableHead, pf);
		fprintf(pf, "\nSyntax Tree as Below:\n");
		printTree(treeHead, pf);
		
		fclose(pf);
		
		fileName[strlen(fileName)-1] = 's';	/* 汇编代码所在的文件名 */
		codeGen(tableHead, treeHead, fileName);	/* 生成汇编代码 */
		
		if (nError == 0)
		{
			printf("End of compile, all successfully.\n");
			fileName[strlen(fileName)-1] = '\0';
			printf("%st and %ss have been generated.\n\n", fileName, fileName);
		}
		else
		{
			/* 删除文件 */
			printf("Generate compiled files wrong.\n\n");
			_unlink(fileName);
			fileName[strlen(fileName)-1] = 't';
			_unlink(fileName);
		}
	}
	else
	{
		printf("\nParse wrong.\n\n");
	}
	return 0;
}

