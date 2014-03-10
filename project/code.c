/************* ���ݷ��ű���﷨�����ɻ����� ****************/
/*************************************************************/

#include "code.h"
#include "cmmyacc.h"

/* ����� */
extern int nError;

/* ������տ�ʼ��һ�� */
#define CODE_BEGIN "STACK SEGMENT STACK\n\
\tDB 128 DUP(0)\n\
STACK ENDS\n\n\
DATA SEGMENT\n\
\tARRAY DB 256 DUP(0)\n"

/* ���ݶ���֮����һ��,λ�����������м�λ�� */
#define CODE_MID "DATA ENDS\n\n\
CODE SEGMENT 'CODE'\n\
INPUT PROC FAR\n\
\tMOV AH, 1\n\
\tINT 21H\n\
\tRET\n\
INPUT ENDP\n\n\
OUTPUT PROC FAR\n\
\tMOV AH, 06H\n\
\tINT 21H\n\
\tRET\n\
OUTPUT ENDP\n\n\
MAIN PROC FAR\n\
\tASSUME CS:CODE, DS:DATA, SS:STACK\n\
\tMOV BP, OFFSET ARRAY\n\n"

/* ���������λ�� */
#define CODE_END "MAIN ENDP\n\
CODE ENDS\n\
END MAIN\n"

static int flag[128];	/* ���128����ʱ������û��ʹ�� */

/* ��flag���ҳ�Ϊ0��һ��Ԫ�� */
int findInArray(void)
{
	int i=0;
	for (i=0; i<128; i++)
	{
		if (flag[i] == 0)
		{
			return i;
		}
	}

	return -1;
}

/* �ӷ��ű����������ݶ���Ļ����� */
void fromTable(TableNode* table, FILE* pf)
{
	while (table != NULL)
	{
		fprintf(pf, "\tDATA_%s DW ?\n", table->name);	/* ���ݶ����� */
		table = table->next;
	}
}

/* ���﷨�����ɻ�����,������� */
void fromTree(TreeNode* tree, FILE* pf)
{
	int i, j;
	char temp[20];
	while (tree != NULL)	/* ��������� */
	{
		for (i=0; i<MAXCHILDREN; i++)	/* ���������� */
		{
			if (tree->child[i] != NULL)
			{
				fromTree(tree->child[i], pf);	/* �ݹ� */
			}
		}

		/* ���ݲ�ͬ���͵Ľ�����ɲ�ͬ�Ļ����� */
		if (tree->nodekind == StmtK)
		{ 
			switch (tree->kind.stmt) 
			{
			case ReturnK:	/* ������� */
				fprintf(pf, "\tMOV AH, 4CH\n");
				fprintf(pf, "\tINT 21H\n");
				break;
			case AssignK:	/* ��ֵ��� */
				if (tree->child[0]->nodekind == AddrK)
				{
					fprintf(pf, "\tMOV CX, WORD PTR[BP+%d]\n", 2*tree->child[0]->attr.val);
					fprintf(pf, "\tMOV DATA_%s, CX\n", tree->attr.name);
					flag[tree->child[0]->attr.val] = 0;
				}
				else if (tree->child[0]->kind.exp == ConstK)
				{
					fprintf(pf, "\tMOV DATA_%s, %d\n", tree->attr.name, tree->child[0]->attr.val);
				}
				else if (tree->child[0]->kind.exp == IdK)
				{
					fprintf(pf, "\tMOV DATA_%s, DATA_%s\n",tree->attr.name, tree->child[0]->attr.name);
				}
				/* ���浽��ʱ�������� */
				if ((j=findInArray()) >= 0)
				{
					fprintf(pf, "\tMOV CX, DATA_%s\n", tree->attr.name);
					fprintf(pf, "\tMOV WORD PTR[BP+%d], CX\n", j*2);
					tree->nodekind = AddrK;
					tree->attr.val = j;
					flag[j] = 1;
				}
				break;
			case InputK:	/* ������� */
				fprintf(pf, "\tCALL INPUT\n");
				/* ���浽��ʱ�������� */
				if ((j=findInArray()) >= 0)
				{
					fprintf(pf, "\tMOV AH, 0\n");
					fprintf(pf, "\tMOV WORD PTR[BP+%d], AX\n", j*2);
					tree->nodekind = AddrK;
					tree->attr.val = j;
					flag[j] = 1;
				}
				break;
			case OutputK:	/* ������ */
				if (tree->child[0]->nodekind == AddrK)
				{
					fprintf(pf, "\tMOV DX, WORD PTR[BP+%d]\n", 2*tree->child[0]->attr.val);
					flag[tree->child[0]->attr.val] = 0;
				}
				else if (tree->child[0]->kind.exp == ConstK)
				{
					fprintf(pf, "\tMOV DX, %d\n", tree->child[0]->attr.val);
				}
				else if (tree->child[0]->kind.exp == IdK)
				{
					fprintf(pf, "\tMOV DX, DATA_%s\n", tree->child[0]->attr.name);
				}
				fprintf(pf, "\tMOV DH, 0\n");
				fprintf(pf, "\tCALL OUTPUT\n");
				break;
			default:
				fprintf(pf, "\t;Unknown ExpNode kind\n");
				break;
			}
		}
		else if (tree->nodekind == ExpK)
		{ 
			switch (tree->kind.exp) 
			{
			case OpK:	/* ������,�����Ӽ��˳� */
				if (tree->child[0]->nodekind == AddrK)	/* �����������浽�Ĵ���AX�� */
				{
					fprintf(pf, "\tMOV AX, WORD PTR[BP+%d]\n", 2*tree->child[0]->attr.val);
					flag[tree->child[0]->attr.val] = 0;
				}
				else if (tree->child[0]->kind.exp == ConstK)
				{
					fprintf(pf, "\tMOV AX, %d\n", tree->child[0]->attr.val);
				}
				else if (tree->child[0]->kind.exp == IdK)
				{
					fprintf(pf, "\tMOV AX, DATA_%s\n", tree->child[0]->attr.name);
				}

				if (tree->child[1]->nodekind == AddrK)	/* ������������ */
				{
					sprintf(temp, "WORD PTR[BP+%d]\0", 2*tree->child[1]->attr.val);
					flag[tree->child[1]->attr.val] = 0;
				}
				else if (tree->child[1]->kind.exp == ConstK)
				{
					sprintf(temp, "%d\0", tree->child[1]->attr.val);
				}
				else if (tree->child[1]->kind.exp == IdK)
				{
					sprintf(temp, "DATA_%s\0", tree->child[1]->attr.name);
				}

				switch (tree->attr.op)
				{
				case PLUS:	/* �ӷ� */
					fprintf(pf, "\tADD AX, %s\n", temp);
					break;
				case MINUS:	/* ���� */
					fprintf(pf, "\tSUB AX, %s\n", temp);
					break;
				case MULT:	/* �˷� */
					fprintf(pf, "\tMOV CX, %s\n", temp);
					fprintf(pf, "\tIMUL CX\n");
					break;
				case DIV:	/* ���� */
					fprintf(pf, "\tMOV DX, 0\n");
					fprintf(pf, "\tMOV CX, %s\n", temp);
					fprintf(pf, "\tIDIV CX\n");
					break;
				}

				/* ���浽��ʱ�������� */
				if ((j=findInArray()) >= 0)
				{
					fprintf(pf, "\tMOV WORD PTR[BP+%d], AX\n", j*2);
					tree->nodekind = AddrK;
					tree->attr.val = j;
					flag[j] = 1;
				}
				break;
			case ConstK:	/* �������ͱ�����㲻������ */
			case IdK:
				break;
			default:
				fprintf(pf, "\t;Unknown ExpNode kind\n");
				break;
			}
		}
		else if (tree->nodekind != AddrK)	/* AddrK���Ҳ�������� */
		{
			fprintf(pf, "\t;Unknown node kind\n");
		}
		
		tree = tree->sibling;	/* ת�Ƶ����ֵ���,����Ӧ����һ��C��� */
	}
}

/* ���ɻ����뺯��,�������ű�,�﷨��,�ļ��� */
void codeGen(TableNode* table, TreeNode* tree, char* fileName)
{
	FILE *pf;
	int i;

	for (i=0; i<128; i++)	/* ��ʼ�� */
	{
		flag[i] = 0;
	}

	pf = fopen(fileName, "w");
	if (pf == NULL)
	{
		printf("Error %d: Cannot open file %s.\n", ++nError, fileName);
		return;
	}
	
	fprintf(pf, CODE_BEGIN);	/* ��ʼ���ֻ����� */
	fromTable(table, pf);	/* �ӷ��ű��������ݶ�������� */
	fprintf(pf, CODE_MID);	/* �м䲿�ֻ����� */
	fromTree(tree, pf);	/* ���﷨������ִ�в��ֻ����� */
	fprintf(pf, CODE_END);	/* �������ֻ����� */		

	fclose(pf);
}
