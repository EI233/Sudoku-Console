//
// Created by zxc02 on 2022/8/11.
//
//
// Created by zxc02 on 2022/8/2.
//
#include "Global.h"

/*
* 函数名称: WriteFile
* 接受参数: int double int []
* 函数功能: 保存文件
* 返回值: int
*/
int WriteFile(int result, double time, const int value[])
{
	FILE* fp;
	int i;
	char file[150] = "../res/";
	strcat(file, FileName + 7);
	for (i = 0; file[i] != '\0'; i++)
	{
		if (file[i] == '.' && file[i + 4] == '\0')
		{
			file[i + 1] = 'r';
			file[i + 2] = 'e';
			file[i + 3] = 's';
			break;
		}
	}
	if ((fp = fopen(file, "w")) == NULL)
	{
		printf("文件打开失败!\n");
		return 0;
	}
	fprintf(fp, "result %d", result);  //求解结果
	if (result == 1)
	{
		//保存解值
		fprintf(fp, "\nvalue ");
		for (i = 1; i <= boolCount; i++)
		{
			if (value[i] == 1) fprintf(fp, "%d ", i);
			else fprintf(fp, "%d ", -i);
		}
	}
	fprintf(fp, "\ntime %lf", time * 1000);  //运行时间/毫秒
	fclose(fp);
	return 1;
}

/*
* 函数名称: LoadFile
* 接受参数: SATList* char*
* 函数功能: 将cnf文件转换为十字链表
* 返回值: int
*/
int LoadFile(SATLIST* temp, char* fileName)
{
	FILE* fp;
	char Cnf[4], ch, buf[100];
	int number, i;
	SATList* lp, * cnf;
	SATNode* tp;
	if ((fp = fopen(fileName, "r")) == NULL)
	{
		printf("文件打开失败!\n");
		fclose(fp);
		return 0;
	}
	ch = getc(fp);
	while (ch != 'p')
	{
		fgets(buf, 100, fp);
		ch = getc(fp);
	}
	fscanf(fp, "%s%d%d", Cnf, &boolCount, &clauseCount);
	cnf = (SATList*)malloc(sizeof(SATList));
	cnf->next = NULL;
	cnf->head = (SATNode*)malloc(sizeof(SATNode));
	cnf->head->next = NULL;
	lp = cnf;
	tp = cnf->head;
	for (i = 0; i < clauseCount; i++, lp = lp->next, tp = lp->head)
	{
		lp->length = 1;
		fscanf(fp, "%d", &number);
		for (; number != 0; tp = tp->next)
		{
			tp->data = number;  //数据域赋
			tp->next = (SATNode*)malloc(sizeof(SATNode));  //开辟新结点
			fscanf(fp, "%d", &number);
			if (number == 0) tp->next = NULL;
			else lp->length++;
		}
		lp->next = (SATList*)malloc(sizeof(SATList));  //开辟新表
		lp->next->head = (SATNode*)malloc(sizeof(SATNode));
		if (i == clauseCount - 1)
		{
			lp->next = NULL;
			break;
		}
	}
	fclose(fp);
	*temp = cnf;
	return 1;
}

/*
* 函数名称: ShowFile
* 接受参数: SATList*
* 函数功能: 将转换好的狮子链表输出到控制台
* 返回值: void
*/
void ShowFile(SATList* List)
{
	SATList* lp;
	SATNode* tp;
	if (List == NULL)
	{
		printf("文件为空!\n");
	}
	else
	{
		printf("cnf子句如下：\n");
		for (lp = List; lp != NULL; lp = lp->next)
		{
			for (tp = lp->head; tp != NULL; tp = tp->next)
				printf("%d ", tp->data);
			printf("\n");
		}
		printf("读取完毕!");
	}
}
