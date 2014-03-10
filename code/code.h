/************* ���ݷ��ű���﷨�����ɻ����� ****************/
/*************************************************************/

#ifndef _CODE_H
#define _CODE_H

#include "types.h"
#include <stdio.h>

/* ��flag���ҳ�Ϊ0��һ��Ԫ�� */
int findInArray(void);
/* �ӷ��ű����������ݶ���Ļ����� */
void fromTable(TableNode* table, FILE* pf);
/* ���﷨�����ɻ�����,������� */
void fromTree(TreeNode* tree, FILE* pf);
/* ���ɻ����뺯��,�������ű�,�﷨��,�ļ��� */
void codeGen(TableNode* table, TreeNode* tree, char* fileName);

#endif	// _CODE_H
