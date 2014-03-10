/* 一些数据结构的定义 */
#ifndef _TYPES_H
#define _TYPES_H

/* 一个语法树结点最多的子结点个数 */
#define MAXCHILDREN 2

/* Token类型 */
typedef int TokenType;	
/* AddrK只用来生成汇编代码时使用,是一个计算过的结点,
结点attr.value保存的是临时变量的偏移 */
typedef enum {StmtK, ExpK, AddrK} NodeKind;
typedef enum {AssignK, InputK, OutputK, ReturnK} StmtKind;
typedef enum {OpK, ConstK, IdK} ExpKind;

/* 数据类型 */
typedef enum {VoidT, IntT} ExpType;

/* 符号表中的结点 */
typedef struct node
{
	char name[255];/*MAXTOKENLEN];*/
	ExpType eType;
	struct node* next;
} TableNode;

/* 语法数中的结点 */
typedef struct treeNode
{ 
	struct treeNode* child[MAXCHILDREN];	/* 子结点 */
	struct treeNode* sibling;	/* 兄弟结点 */
	int lineno;	/* C语句中的行号,用来输出出错信息 */
	NodeKind nodekind;	/* 结点类型 */
	union 
	{ 
		StmtKind stmt; 
		ExpKind exp; 
	} kind;	/* 标志是语句还是表达式 */
	union
	{ 
		TokenType op;
		int val;
		char* name;
	} attr;	/* 属性值 */
	ExpType type; /* 数据类型 */
} TreeNode;

#endif	// _TYPES_H