/************* 根据符号表和语法树生成汇编代码 ****************/
/*************************************************************/

#include "code.h"
#include "cmmyacc.h"

/* 错误号 */
extern int nError;

/* 汇编程序刚开始那一段 */
#define CODE_BEGIN "STACK SEGMENT STACK\n\
\tDB 128 DUP(0)\n\
STACK ENDS\n\n\
DATA SEGMENT\n\
\tARRAY DB 256 DUP(0)\n"

/* 数据定义之后那一段,位于整体代码的中间位置 */
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

/* 汇编代码结束位置 */
#define CODE_END "MAIN ENDP\n\
CODE ENDS\n\
END MAIN\n"

static int flag[128];	/* 标记128个临时变量有没被使用 */

/* 在flag中找出为0的一个元素 */
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

/* 从符号表中生成数据定义的汇编代码 */
void fromTable(TableNode* table, FILE* pf)
{
	while (table != NULL)
	{
		fprintf(pf, "\tDATA_%s DW ?\n", table->name);	/* 数据定义汇编 */
		table = table->next;
	}
}

/* 从语法树生成汇编代码,后序遍历 */
void fromTree(TreeNode* tree, FILE* pf)
{
	int i, j;
	char temp[20];
	while (tree != NULL)	/* 后序遍历树 */
	{
		for (i=0; i<MAXCHILDREN; i++)	/* 遍历子树先 */
		{
			if (tree->child[i] != NULL)
			{
				fromTree(tree->child[i], pf);	/* 递归 */
			}
		}

		/* 根据不同类型的结点生成不同的汇编代码 */
		if (tree->nodekind == StmtK)
		{ 
			switch (tree->kind.stmt) 
			{
			case ReturnK:	/* 返回语句 */
				fprintf(pf, "\tMOV AH, 4CH\n");
				fprintf(pf, "\tINT 21H\n");
				break;
			case AssignK:	/* 赋值语句 */
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
				/* 保存到临时数据区中 */
				if ((j=findInArray()) >= 0)
				{
					fprintf(pf, "\tMOV CX, DATA_%s\n", tree->attr.name);
					fprintf(pf, "\tMOV WORD PTR[BP+%d], CX\n", j*2);
					tree->nodekind = AddrK;
					tree->attr.val = j;
					flag[j] = 1;
				}
				break;
			case InputK:	/* 输入语句 */
				fprintf(pf, "\tCALL INPUT\n");
				/* 保存到临时数据区中 */
				if ((j=findInArray()) >= 0)
				{
					fprintf(pf, "\tMOV AH, 0\n");
					fprintf(pf, "\tMOV WORD PTR[BP+%d], AX\n", j*2);
					tree->nodekind = AddrK;
					tree->attr.val = j;
					flag[j] = 1;
				}
				break;
			case OutputK:	/* 输出语句 */
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
			case OpK:	/* 动算结点,包括加减乘除 */
				if (tree->child[0]->nodekind == AddrK)	/* 左运算数保存到寄存器AX中 */
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

				if (tree->child[1]->nodekind == AddrK)	/* 处理右运算数 */
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
				case PLUS:	/* 加法 */
					fprintf(pf, "\tADD AX, %s\n", temp);
					break;
				case MINUS:	/* 减法 */
					fprintf(pf, "\tSUB AX, %s\n", temp);
					break;
				case MULT:	/* 乘法 */
					fprintf(pf, "\tMOV CX, %s\n", temp);
					fprintf(pf, "\tIMUL CX\n");
					break;
				case DIV:	/* 除法 */
					fprintf(pf, "\tMOV DX, 0\n");
					fprintf(pf, "\tMOV CX, %s\n", temp);
					fprintf(pf, "\tIDIV CX\n");
					break;
				}

				/* 保存到临时数据区中 */
				if ((j=findInArray()) >= 0)
				{
					fprintf(pf, "\tMOV WORD PTR[BP+%d], AX\n", j*2);
					tree->nodekind = AddrK;
					tree->attr.val = j;
					flag[j] = 1;
				}
				break;
			case ConstK:	/* 常数结点和变量结点不做处理 */
			case IdK:
				break;
			default:
				fprintf(pf, "\t;Unknown ExpNode kind\n");
				break;
			}
		}
		else if (tree->nodekind != AddrK)	/* AddrK结点也不做处理 */
		{
			fprintf(pf, "\t;Unknown node kind\n");
		}
		
		tree = tree->sibling;	/* 转移到其兄弟树,即对应的下一条C语句 */
	}
}

/* 生成汇编代码函数,传进符号表,语法树,文件名 */
void codeGen(TableNode* table, TreeNode* tree, char* fileName)
{
	FILE *pf;
	int i;

	for (i=0; i<128; i++)	/* 初始化 */
	{
		flag[i] = 0;
	}

	pf = fopen(fileName, "w");
	if (pf == NULL)
	{
		printf("Error %d: Cannot open file %s.\n", ++nError, fileName);
		return;
	}
	
	fprintf(pf, CODE_BEGIN);	/* 开始部分汇编代码 */
	fromTable(table, pf);	/* 从符号表生成数据定义汇编代码 */
	fprintf(pf, CODE_MID);	/* 中间部分汇编代码 */
	fromTree(tree, pf);	/* 从语法树生成执行部分汇编代码 */
	fprintf(pf, CODE_END);	/* 结束部分汇编代码 */		

	fclose(pf);
}
