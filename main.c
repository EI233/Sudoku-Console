#include "Lib/Global.h"

int boolCount;  /*布尔变元数量*/
int clauseCount;  /*子句数量*/
char FileName[150];
int sudoku[ROW][COL] = { 0 };
int starting_grid[ROW][COL] = { 0 };
int holes = 15;
Count* count = NULL;
Value SudoResult[163];

int main()
{
	int op = 1, res;
	while (op)
	{
		char temp[70];
		Menu();
		scanf("%d", &op);
		if (!op)break;
		else if (op == 1)
		{
			strcpy(FileName, "../src/");
			SATList* CNFList = NULL;
			printf("Please input the filename!\n");
			scanf("%s", temp);
			strcat(FileName, temp);
			res = LoadFile(&CNFList, FileName);
			if (!res)
			{
				system("pause");
				op = 1;
			}
			else
			{
				printf("Whether to Show the content of the cnf file?\n"
					   "1 for Yes::Others for NO\n");
				scanf("%d", &op);
				if (op == 1)ShowFile(CNFList);
				else op = 1;
				system("pause");
				system("cls");
				printf("Whether to process the DPLL?\n"
					   "1 for Yes::Others for NO\n");
				scanf("%d", &op);
				if (op == 1)Solution(CNFList);
				else op = 1;
			}
		}
		else if (op == 2)
		{
			Sudoku();
		}
		system("cls");
	}
	return 0;
}
