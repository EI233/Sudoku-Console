//
// Created by zxc02 on 2022/8/11.
//
//
// Created by zxc02 on 2022/8/2.
//
#include "Global.h"

/*
 * 函数名称: destroyClause
 * 接受参数: SATList*
 * 函数功能: 销毁所有子句
 * 返回值: 无
 */
void destroyClause(SATLIST* cnf)
{
	SATList* lp1, * lp2;
	SATNode* tp1, * tp2;
	for (lp1 = *cnf; lp1 != NULL; lp1 = lp2)
	{
		lp2 = lp1->next;
		for (tp1 = lp1->head; tp1 != NULL; tp1 = tp2)
		{
			tp2 = tp1->next;
			free(tp1);
		}
		free(lp1);
	}
	cnf = NULL;
}

/*
 * 函数名称: isUnitClause
 * 接受参数: SATNode*
 * 函数功能: 判断是否为单子句，是返回1，不是返回0
 * 返回值: int
 */
SATList* isUnitClause(SATList* List)
{
	while (List != NULL)
	{
		if (List->head != NULL && List->head->next == NULL)
			return List;
		List = List->next;
	}
	return NULL;
}

/*
 * 函数名称: RemoveSATNode
 * 接受参数: SATList*,SATList*
 * 函数功能: 在已有的十字链表中对指定数据进行简化句子的简化
 * 返回值: 无
 */
void RemoveSATNode(int re, SATLIST* List)
{
	for (SATList* lp = *List; lp != NULL; lp = lp->next)
	{
		for (SATNode* dp = lp->head; dp != NULL; dp = dp->next)
		{
			if (dp->data == re)
			{
				removeClause(lp, List);  //删除子句，简化式子
				break;
			}
			else if (dp->data == -re)
			{
				lp->length--;
				removeNode(dp, &lp->head);
				break;
			}
		}
	}
}

/*
 * 函数名称: removeClause
 * 接受参数: SATList*,SATList*
 * 函数功能: 在已有的十字链表中删除指定的子句，删除成功返回1，失败返回0
 * 返回值: int
 */
void removeClause(SATList* Clause, SATLIST* root)
{
	if (!Clause)return;
	SATList* t2 = *root;
	if (Clause == t2)
		*root = t2->next;
	else
	{
		for (SATList* front = t2; front != NULL; front = front->next)
			if (front->next == Clause)
			{
				front->next = (Clause)->next;
				break;
			}
	}
}

/*
 * 函数名称: removeNode
 * 接受参数: SATNode*,SATNode*
 * 函数功能: 在指定的子句中删除指定的文字，删除成功返回1，失败返回0
 * 返回值: int
 */
int removeNode(SATNode* cnf, SATNODE* head)
{
	SATNode* lp = *head;
	if (lp == cnf)
		*head = lp->next;
	else
		for (SATNode* front = *head; front != NULL; front = front->next)
			if (front->next == cnf)
				front->next = cnf->next;
	return 1;
}

/*
 * 函数名称: addClause
 * 接受参数: SATList*,SATList*
 * 函数功能: 在已有的十字链表中添加指定的子句，添加成功返回1，失败返回0
 * 返回值: int
 */
SATList* addClause(SATList* cnf, int var)
{
	SATList* newList;
	newList = (SATList*)malloc(sizeof(SATList));
	newList->head = (SATNode*)malloc(sizeof(SATNode));
	newList->head->data = var;
	newList->head->next = NULL;
	newList->next = cnf;
	newList->length = 1;
	cnf = newList;
	return cnf;
}

/*
 * 函数名称: emptyClause
 * 接受参数: SATList*
 * 函数功能: 判断是否含有空子句，是返回1，不是返回0
 * 返回值: int
 */
int emptyClause(SATList* List)
{
	SATList* lp = List;
	while (lp != NULL)
	{
		if (lp->head == NULL)
			return 1;
		lp = lp->next;
	}
	return 0;
}

/*
 * 函数名称: CopyClause
 * 接受参数: SATList*,SATList*
 * 函数功能: 将链表b的值复制到链表a中
 * 返回值: void
 */
SATList* CopyClause(SATList* List)
{
	SATList* SrcHead = List;
	SATList* ReHead = (SATList*)malloc(sizeof(SATList));
	SATList* Phead = ReHead;
	SATNode* ReData = (SATNode*)malloc(sizeof(SATNode)), * FirstSrcData = SrcHead->head;
	ReData->data = FirstSrcData->data;//新链表的第一个数据节点的数值
	Phead->head = ReData;
	Phead->length = SrcHead->length;
	for (FirstSrcData = FirstSrcData->next; FirstSrcData != NULL; FirstSrcData = FirstSrcData->next)
	{//第一行链表复制完成
		SATNode* NewDataNode = (SATNode*)malloc(sizeof(SATNode));
		NewDataNode->data = FirstSrcData->data;
		NewDataNode->next = NULL;
		ReData->next = NewDataNode;
		ReData = ReData->next;
	}
	for (SrcHead = SrcHead->next; SrcHead != NULL; SrcHead = SrcHead->next)
	{
		SATList* NewHead = (SATList*)malloc(sizeof(SATList));
		SATNode* NewData = (SATNode*)malloc(sizeof(SATNode));
		NewHead->length = SrcHead->length;
		Phead->next = NewHead;
		Phead = Phead->next;
		SATNode* SrcData = SrcHead->head;
		NewData->data = SrcData->data;
		Phead->head = NewData;//第一个数据节点
		for (SrcData = SrcData->next; SrcData != NULL; SrcData = SrcData->next)
		{//此行剩下的数据节点
			SATNode* node = (SATNode*)malloc(sizeof(SATNode));
			node->data = SrcData->data;
			NewData->next = node;
			NewData = NewData->next;
		}
		NewData->next = NULL;
	}
	Phead->next = NULL;
	return ReHead;
}

/*
 * 函数名称: Max
 * 接受参数: SATList*
 * 函数功能: 求取出现最多次数的文字
 * 返回值: int
 */
int Max(SATList* List)
{
	int i, MaxWord = 0, max = 0; //count记录每个文字出现次数,MaxWord记录出现最多次数的文字
	count = (Count*)malloc(sizeof(Count) * (boolCount + 1));
	for (int j = 0; j <= boolCount; ++j)
	{
		count[j].Negative = 0;
		count[j].Positive = 0;
	}
	for (SATList* lp = List; lp != NULL; lp = lp->next)
	{
		for (SATNode* dp = lp->head; dp != NULL; dp = dp->next)
		{
			if (dp->data > 0) count[dp->data].Positive++;
			else count[-dp->data].Negative++;
		}
	}
	for (i = 0; i <= boolCount; i++)
	{
		if (max < count[i].Positive + count[i].Negative)
		{
			max = count[i].Positive + count[i].Negative;
			MaxWord = i;
		}
	}
	if (count[MaxWord].Positive < count[MaxWord].Negative)MaxWord = -MaxWord;
	free(count);
	count = NULL;
	return MaxWord;
}

int SudoKU_Max(SATList* List)
{
	int i, MaxWord = 0, max = 0; //count记录每个文字出现次数,MaxWord记录出现最多次数的文字
	count = (Count*)malloc(sizeof(Count) * (3001));
	for (int j = 1111; j <= 3000; ++j)
	{
		count[j].Negative = 0;
		count[j].Positive = 0;
	}
	for (SATList* lp = List; lp != NULL; lp = lp->next)
	{
		for (SATNode* dp = lp->head; dp != NULL; dp = dp->next)
		{
			if (dp->data > 0) count[dp->data].Positive++;
			else count[-dp->data].Negative++;
		}
	}
	for (i = 1111; i <= 3000; i++)
	{
		if (max < count[i].Positive + count[i].Negative)
		{
			max = count[i].Positive + count[i].Negative;
			MaxWord = i;
		}
	}
	if (count[MaxWord].Positive <= count[MaxWord].Negative)MaxWord = -MaxWord;
	free(count);
	count = NULL;
	return MaxWord;
}

/*
* 函数名称: DPLL
* 接受参数: SATList *
* 函数功能: 选择出现最多次数的文字为策略的DPLL
* 返回值: int
*/
int DPLL(SATList* cnf, int value[])
{
	SATList* List = cnf;
	SATList* UnitClause = isUnitClause(List);
	while (UnitClause != NULL)
	{
		if (UnitClause->head->data > 0) value[UnitClause->head->data] = 1;
		else value[-UnitClause->head->data] = 0;
		int re = UnitClause->head->data;
		removeClause(UnitClause, &cnf);
		RemoveSATNode(re, &cnf);
		if (!cnf)return 1;
		else if (emptyClause(cnf))
		{
			destroyClause(&cnf);
			return 0;
		}
		List = cnf;
		UnitClause = isUnitClause(List);
	}
	int Var = Max(cnf);
	SATList* replica = CopyClause(cnf);
	SATList* temp1 = CopyClause(cnf);
	SATList* temp2 = addClause(replica, -Var);
	temp1 = addClause(temp1, Var);
	if (DPLL(temp1, value))
	{
		destroyClause(&temp1);
		temp1 = NULL;
		return 1;
	}  //在第一分支中搜索
	else if (DPLL(temp2, value))
	{
		destroyClause(&temp2);
		temp2 = NULL;
		return 1;
	}
	return 0;
}

/*
* 函数名称: DPLL1
* 接受参数: SATList *
* 函数功能: 基础版DPLL
* 返回值: int
*/
int DPLL1(SATList* cnf, int value[])
{
	SATList* List = cnf;
	SATList* UnitClause = isUnitClause(List);
	while (UnitClause != NULL)
	{
		if (UnitClause->head->data > 0) value[UnitClause->head->data] = 1;
		else value[-UnitClause->head->data] = 0;
		int re = UnitClause->head->data;
		removeClause(UnitClause, &cnf);
		RemoveSATNode(re, &cnf);
		if (!cnf)return 1;
		else if (emptyClause(cnf))
		{
			destroyClause(&cnf);
			cnf = NULL;
			return 0;
		}
		List = cnf;
		UnitClause = isUnitClause(List);
	}
	int Var = cnf->head->data;
	SATList* replica = CopyClause(cnf);
	SATList* temp1 = CopyClause(cnf);
	SATList* temp2 = addClause(replica, -Var);
	temp1 = addClause(temp1, Var);
	if (DPLL1(temp1, value))
	{
		destroyClause(&temp1);
		temp1 = NULL;
		return 1;
	}  //在第一分支中搜索
	else if (DPLL1(temp2, value))
	{
		destroyClause(&temp2);
		temp2 = NULL;
		return 1;
	}
	return 0;
}
