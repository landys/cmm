/* һЩ���ݽṹ�Ķ��� */
#ifndef _TYPES_H
#define _TYPES_H

/* һ���﷨����������ӽ����� */
#define MAXCHILDREN 2

/* Token���� */
typedef int TokenType;	
/* AddrKֻ�������ɻ�����ʱʹ��,��һ��������Ľ��,
���attr.value���������ʱ������ƫ�� */
typedef enum {StmtK, ExpK, AddrK} NodeKind;
typedef enum {AssignK, InputK, OutputK, ReturnK} StmtKind;
typedef enum {OpK, ConstK, IdK} ExpKind;

/* �������� */
typedef enum {VoidT, IntT} ExpType;

/* ���ű��еĽ�� */
typedef struct node
{
	char name[255];/*MAXTOKENLEN];*/
	ExpType eType;
	struct node* next;
} TableNode;

/* �﷨���еĽ�� */
typedef struct treeNode
{ 
	struct treeNode* child[MAXCHILDREN];	/* �ӽ�� */
	struct treeNode* sibling;	/* �ֵܽ�� */
	int lineno;	/* C����е��к�,�������������Ϣ */
	NodeKind nodekind;	/* ������� */
	union 
	{ 
		StmtKind stmt; 
		ExpKind exp; 
	} kind;	/* ��־����仹�Ǳ��ʽ */
	union
	{ 
		TokenType op;
		int val;
		char* name;
	} attr;	/* ����ֵ */
	ExpType type; /* �������� */
} TreeNode;

#endif	// _TYPES_H