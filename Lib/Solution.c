//
// Created by zxc02 on 2022/8/2.
//
#include "Global.h"


void Solution(SATList* List)
{
	clock_t start, finish;
	double t1, t2;
	int* value, result, op;
	if (List == NULL) printf("未成功导入文件\n");
	else
	{
		value = (int*)malloc(sizeof(int) * (boolCount + 1));
		for (int i = 1; i <= boolCount; i++) value[i] = 1;  //初始化，均赋为1
		start = clock();  //计时开始;
		result = DPLL1(List, value);
		finish = clock();//
		t1 = (double)(finish - start) / CLOCKS_PER_SEC;//计算运行时间
		for (int i = 1; i <= boolCount; i++) value[i] = 1;
		List = NULL;
		LoadFile(&List, FileName);
		start = clock();  //计时开始;
		result = DPLL(List, value);
		finish = clock();//结束
		t2 = (double)(finish - start) / CLOCKS_PER_SEC;//计算运行时间
		printf("运行时间:未优化:%lfms\n"
			   "运行时间:优化:%lfms\n", t1 * 1000, t2 * 1000);//输出运行时间
		if (result == 1)
		{
			printf("Mission Completed!\nWhether to show the result?(1 means Yes | 2 means NO)");
			scanf("%d", &op);
			if (op == 1)
			{
				for (int i = 1; i <= boolCount; i++)
				{
					if (value[i] == 1) printf("%d ", i);
					else printf("%d ", -i);
				}
				printf("\n");
			}
		}
		else printf("This Cnf file has no ans\n");
		printf("Whether You want to store the data to a res file?\n1 for Yes::Others for NO\n");
		scanf("%d", &op);
		if (op == 1)
		{
			if (WriteFile(result, t2, value) == 1)
				printf("The result has already been stored to the res file with a same name\n");
			else printf("Failed!\n");
		}
	}
	system("pause");
}

void Sudoku()
{
	printf("Please input the holes of the Sudoku You want to challenge.\n");
	scanf("%d", &holes);
	createSudoku(sudoku);
	print(sudoku);
	createStartinggrid(sudoku, starting_grid, holes);
	printf("Here is the original Sudoku\n");
	print(starting_grid);
	ToCnf(starting_grid, holes);
	SATList* CNFList = NULL;
	strcpy(FileName, "../sudoku/sudoku.cnf");
	LoadFile(&CNFList, FileName);
	for (int i = 0; i <= 162; i++)
	{
		SudoResult[i].value = 0;
		SudoResult[i].content = 1;
	}
	clock_t StartTime, EndTime;
	StartTime = clock();
	int value = SudoDPLL(CNFList, SudoResult, 0);
	EndTime = clock();
	if (value)
	{
		printf("And the DPLL mission is Completed!\nThe time is %lf ms\n",
				(double)(EndTime - StartTime) / CLOCKS_PER_SEC * 1000.0);
		printf("Now input 1 to Show ans\n");
		scanf("%d", &value);
		if (value == 1)
		{
			system("cls");
			printf("here is the ans\n");
			SudokuShow(SudoResult);
			Reset();
		}
		system("pause");
	}
	else
	{
		printf("Failed!");
	}
}