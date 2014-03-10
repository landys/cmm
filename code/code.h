/************* 根据符号表和语法树生成汇编代码 ****************/
/*************************************************************/

#ifndef _CODE_H
#define _CODE_H

#include "types.h"
#include <stdio.h>

/* 在flag中找出为0的一个元素 */
int findInArray(void);
/* 从符号表中生成数据定义的汇编代码 */
void fromTable(TableNode* table, FILE* pf);
/* 从语法树生成汇编代码,后序遍历 */
void fromTree(TreeNode* tree, FILE* pf);
/* 生成汇编代码函数,传进符号表,语法树,文件名 */
void codeGen(TableNode* table, TreeNode* tree, char* fileName);

#endif	// _CODE_H
