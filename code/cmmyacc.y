%token SEMI SLB SRB BLB BRB MAIN RETURN INT VOID INPUT OUTPUT
%token PLUS MINUS MULT DIV ASSIGN
%token ID NUM ERROR

%{
/****************************************************************************
cmmyacc.y
ParserWizard generated YACC file.
Author: Jinde Wang
Date: 2006��6��26��
****************************************************************************/

#include "code.h"
#include "cmmlex.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define YYSTYPE TreeNode*

int nError = 0;	/* ��¼����� */
static int hasReturn = 0;	/* ��־����������return��� */
static TableNode* tableHead = NULL;	/* ���ű�ͷ��� */
static TreeNode* treeHead = NULL;	/* �﷨��ͷ��� */
static indentno = 0;	/* ��ӡ�﷨��ʱ������ */
static char* tempToken[64];	/* ������ʱToken�� */
static int tempno[64];	/* �����Ӧ��Token��Ӧ���к� */
static int top = -1;	/* �������������еĵ�ǰ�±�,ʵ�ֶ�ջ���� */
char tokenString[255];	/* ��ǰToken�� */
int lineno = 1;	/* ��ǰ�к� */

/* ��ѯ���ű�,������������,�鲻��,����VoidT */
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

/* ���뵽���ű�,�ɹ�����1,���򷵻�0 */
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

/*����ӡ�����ű��ļ� */
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

/* �����µı��ʽ��㣬����ָ�����ָ�� */
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

/* �����µ�����㣬����ָ�����ָ�� */
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

/* �����ַ����������´������ַ�����ָ�� */
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

/* ��ӡһ���﷨����㵽�ļ��� */
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

/* ��ӡ�ո��ļ��� */
static void printSpaces(FILE* pf)
{
	int i;
	for (i=0; i<indentno; i++)
	{
		fprintf(pf, " ");
	}
}

/* ��ӡ�﷨�����ļ��У�ǰ�����,�ӽ��ȸ������������ */
void printTree(TreeNode* tree, FILE* pf)
{ 
	int i;
	indentno += 2;	/* ������2 */
	while (tree != NULL)
	{
		printSpaces(pf);	/* ��ӡ�ո� */
		if (tree->nodekind == StmtK)
		{ 
			switch (tree->kind.stmt) 
			{
			case ReturnK:	/* ������� */
				fprintf(pf, "ReturnK\n");
				break;
			case AssignK:	/* ��ֵ��� */
				fprintf(pf, "Assign to: %s\n",tree->attr.name);
				break;
			case InputK:	/* ������� */
				fprintf(pf, "Input\n");
				break;
			case OutputK:	/* ������ */
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
			case OpK:	/* ������,�����Ӽ��˳� */
				fprintf(pf, "Op: ");
				printToken(tree->attr.op,"\0", pf);
				break;
			case ConstK:	/* ������� */
				fprintf(pf, "Const: %d\n",tree->attr.val);
				break;
			case IdK:	/* ������� */
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
		for (i=0; i<MAXCHILDREN; i++)	/* �������� */
		{
			printTree(tree->child[i], pf);	/* �ݹ� */
		}
		tree = tree->sibling;	/* ת�Ƶ����ֵ���,����Ӧ����һ��C��� */
	}
	indentno -= 2;	/* ������2 */
 }


%}

%%

program : main_decl
	;

main_decl : type_spec fun_ID SLB params SRB compound_stmt
	;

type_spec : INT
	;

fun_ID : MAIN
	;

params : VOID
	| 
	;
	
compound_stmt : BLB var_decl_list stmt_list BRB
	{
		treeHead = $3;	
	}
	;
	
var_decl_list : var_decl_list var_decl
	|
	;
	
var_decl : type_spec ID
	{
		if (insert(tokenString, IntT) == 0)
		{
			printf("ERROR %d: Line %d Duplicated definition.\n", ++nError, lineno);
		}
	}
	SEMI
	;
	
stmt_list : stmt_list stmt
	{
		YYSTYPE t = $1;
		if (t != NULL)
		{
			while (t->sibling != NULL)
			{
				t = t->sibling;
			}
			t->sibling = $2;
			$$ = $1;
		}
		else
		{
			$$ = $2;
		}
	}
	| { $$ = NULL; }
	;

stmt : exp_stmt { $$ = $1; }
	| I_stmt { $$ = $1; }
	| O_stmt { $$ = $1; }
	| ret_stmt { $$ = $1; }
	;
	
exp_stmt : exp SEMI { $$ = $1; }
	| SEMI { $$ = NULL; }
	;

ret_stmt : RETURN exp SEMI
	{
		$$ = newStmtNode(ReturnK);
		$$->child[0] = $2;
		hasReturn = 1;
	}
	;

I_stmt : I_exp SEMI { $$ = $1; }
	;
	
I_exp : INPUT SLB SRB
	{
		$$ = newStmtNode(InputK);
	}
	;
	
O_stmt : OUTPUT SLB exp SRB SEMI
	{
		$$ = newStmtNode(OutputK);
		$$->child[0] = $3;
	}
	;
	
exp : asgn_exp { $$ = $1; }
	| algo_exp { $$ = $1; }
	;
	
asgn_exp : ID
	{
		tempToken[++top] = copyString(tokenString);
		tempno[top] = lineno;
		if (lookup(tokenString) == VoidT)
		{
			printf("ERROR %d: Line %d: ID %s is not defined.\n", ++nError, lineno, tokenString);
		}
	}
	ASSIGN exp
	{
		$$ = newStmtNode(AssignK);
		$$->child[0] = $4;
		$$->lineno = tempno[top];
		$$->attr.name = tempToken[top--];
	}
	;
	
algo_exp : algo_exp addop term
	{
		$$ = $2;
		$$->child[0] = $1;
		$$->child[1] = $3;
	}
	| term
	{
		$$ = $1;
	}
	;
	
addop : PLUS
	{
		$$ = newExpNode(OpK);
		$$->attr.op = PLUS;
	}
	| MINUS
	{
		$$ = newExpNode(OpK);
		$$->attr.op = MINUS;
	}
	;
	
term : term multop factor
	{
		$$ = $2;
		$$->child[0] = $1;
		$$->child[1] = $3;
	}
	| factor
	{
		$$ = $1;
	}
	;
	
multop : MULT
	{
		$$ = newExpNode(OpK);
		$$->attr.op = MULT;
	}
	| DIV
	{
		$$ = newExpNode(OpK);
		$$->attr.op = DIV;
	}
	;	

factor : NUM
	{
		$$ = newExpNode(ConstK);
		$$->attr.val = atoi(tokenString);
	}
	| ID
	{
		if (lookup(tokenString) == VoidT)
		{
			printf("ERROR %d: Line %d: ID %s is not defined.\n", ++nError, lineno, tokenString);
		}
		$$ = newExpNode(IdK);
		$$->attr.name = copyString(tokenString);
	}
	| SLB exp SRB
	{
		$$ = $2;
	}
	| I_exp
	{
		$$ = $1;
	}
	| ERROR
	{
		$$ = NULL;
	}
	;

%%

void yyerror(char* message)
{
	printf("ERROR %d: Line %d: Syntax error from yacc.\n", ++nError, lineno);
}

/* ������ */
int main(int argc, char** argv)
{
	FILE* pf;
	char fileName[255];
	int i;
	
	fileName[0] = '\0';
	/* �жϴ���main�����Ĳ��� */
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
	
	/* �������������ļ����ļ��� */
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
		
		strcat(fileName, ".t");	/* ��ӡ���ű���﷨�����ļ����ļ��� */
		pf = fopen(fileName, "w");
		if (pf == NULL)
		{
			printf("ERROR %d: Cannot open file %s.\n", ++nError, fileName);
			printf("Cannot write symbol table and syntax tree to file %s.\n", fileName);
			return 1;
		}
		
		/* ��ӡ���ű���﷨�����ļ� */
		fprintf(pf, "Symble Table as Below:\n");
		printTable(tableHead, pf);
		fprintf(pf, "\nSyntax Tree as Below:\n");
		printTree(treeHead, pf);
		
		fclose(pf);
		
		fileName[strlen(fileName)-1] = 's';	/* ���������ڵ��ļ��� */
		codeGen(tableHead, treeHead, fileName);	/* ���ɻ����� */
		
		if (nError == 0)
		{
			printf("End of compile, all successfully.\n");
			fileName[strlen(fileName)-1] = '\0';
			printf("%st and %ss have been generated.\n\n", fileName, fileName);
		}
		else
		{
			/* ɾ���ļ� */
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
