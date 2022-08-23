//
// Created by zxc02 on 2022/8/11.
//
#include "Global.h"

#define CORRECT 0
#define WRONG -1

int Digit1(int a[][COL], int i, int j)
{//递归填充数独元素
	if (i <= 8 && j <= 8)
	{
		int x, y, k;
		int check[10] = { CORRECT };//用于排除已经使用过的的数字
		for (x = 0; x < i; x++)
			check[a[x][j]] = WRONG;//列已使用的数字置为WRONG
		for (x = 0; x < j; x++)
			check[a[i][x]] = WRONG;//行使用过的数字置为WRONG
		for (x = i / 3 * 3; x <= i; x++)
		{
			if (x == i)
				for (y = j / 3 * 3; y < j; y++)
					check[a[x][y]] = WRONG;
			else
				for (y = j / 3 * 3; y < j / 3 * 3 + 3; y++)
					check[a[x][y]] = WRONG;
		}

		int flag = 0;
		for (k = 1; k <= 9 && flag == 0; k++)
		{//从check数组中查找安全的数字
			if (check[k] == CORRECT)
			{
				flag = 1;
				a[i][j] = k;
				if (j == 8 && i != 8)
				{
					if (Digit1(a, i + 1, 0) == CORRECT) return CORRECT;
					else flag = 0;
				}
				else if (j != 8)
				{
					if (Digit1(a, i, j + 1) == CORRECT) return CORRECT;
					else flag = 0;
				}
			}
		}
		if (flag == 0)
		{
			a[i][j] = 0;
			return WRONG;
		}
	}
	return CORRECT;
}

int Digit2(int a[][COL], int i, int j)
{//递归填充数独元素
	if (i < 15 && j < 15)
	{
		int x, y, k;
		int check[10] = { CORRECT };//用于排除已经使用过的的数字
		for (x = 6; x < i; x++)
			check[a[x][j]] = WRONG;//列已使用的数字置为WRONG
		for (x = 6; x < j; x++)
			check[a[i][x]] = WRONG;//行使用过的数字置为WRONG
		for (x = i / 3 * 3; x <= i; x++)
		{
			if (x == i)
				for (y = j / 3 * 3; y < j; y++)
					check[a[x][y]] = WRONG;
			else
				for (y = j / 3 * 3; y < j / 3 * 3 + 3; y++)
					check[a[x][y]] = WRONG;
		}

		int flag = 0;
		for (k = 1; k <= 9 && flag == 0; k++)
		{//从check数组中查找安全的数字
			if (check[k] == CORRECT)
			{
				flag = 1;
				a[i][j] = k;
				if (j == 14 && i < 8)
				{
					if (Digit2(a, i + 1, 9) == CORRECT) return CORRECT;
					else flag = 0;
				}
				else if (j == 14 && i < 14)
				{
					if (Digit2(a, i + 1, 6) == CORRECT) return CORRECT;
					else flag = 0;
				}
				else if (j != 14)
				{
					if (Digit2(a, i, j + 1) == CORRECT) return CORRECT;
					else flag = 0;
				}
			}
		}
		if (flag == 0)
		{
			a[i][j] = 0;
			return WRONG;
		}
	}
	return CORRECT;
}

void randomFirstRow(int a0[], int p1, int p2)
{//随机生成第一行
	int i, j;
	srand((unsigned)time(NULL));
	for (i = p1 - 1; i < p2; i++)
	{
		a0[i] = rand() % 9 + 1;
		j = p1 == 1 ? 0 : 6;
		while (j < i)
		{
			if (a0[i] == a0[j])
			{
				a0[i] = rand() % 9 + 1;
				j = p1 == 1 ? 0 : 6;
			}
			else j++;
		}
	}
}

void Reset()
{
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			sudoku[i][j] = 0;
			starting_grid[i][j] = 0;
		}
	}
}

void createSudoku(int a[][COL])
{ //生成数独
	randomFirstRow(a[0], 1, 9);//随机生成第一行
	Digit1(a, 1, 0);//递归生成后i行
	randomFirstRow(a[6], 10, 15);//随机生成第一行
	Digit2(a, 7, 9);
}

void createStartinggrid(const int a[][COL], int b[][COL], int numDigits)
{//随机生成初盘
	int i, j, k;
	srand((unsigned)time(NULL));
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
			b[i][j] = a[i][j];
	int** c = (int**)malloc(sizeof(int*) * numDigits);
	for (int p = 0; p < numDigits; p++) c[p] = (int*)malloc(sizeof(int) * 2);
	int m, flag;
	for (i = 0; i < numDigits; i++)
	{
		j = rand() % 15;
		k = rand() % 15;
		while (!((j < 9 && k < 9) || (j >= 6 && k >= 6)))
		{
			j = rand() % 15;
			k = rand() % 15;
		}
		flag = 0;
		for (m = 0; m < i; m++)
			if (j == c[m][0] && k == c[m][1])
				flag = 1;
		if (flag == 0)
		{
			b[j][k] = 0;
			c[i][0] = j;
			c[i][1] = k;
		}
		else
			i--;
	}
	for (int p = 0; p < numDigits; p++) free(c[p]);
}

void print(const int a[][COL])
{//打印数独数组
	int i, j;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
			if ((i >= 9 && j <= 5) || (j >= 9 && i <= 5))printf("  ");
			else printf("%d ", a[i][j]);
		printf("\n");
	}
}


void ToCnf(int a[][COL], int hole)
{
	FILE* fp = fopen("../sudoku/sudoku.cnf", "w");
	if (!fp)
		printf("Wrong!");
	int num = 0;
	for (int x = 0; x < ROW; ++x)
		for (int y = 0; y < COL; ++y)
			if (a[x][y] == 0)
				if ((x < 9 && x >= 6) && (y < 9 && y >= 6))
					num++;
	fprintf(fp, "%c %s %d %d \n", 'p', "cnf", 729 * 2, (8829 + 81 + 81) * 2 - hole - num);
	for (int x = 0; x < ROW; ++x)
	{
		for (int y = 0; y < COL; ++y)
			if (a[x][y] != 0)
			{
				if ((x < 9 && x >= 6) && (y < 9 && y >= 6))
				{
					fprintf(fp, "%d 0\n%d 0\n", 1000 + (x + 1) * 100 + (y + 1) * 10 + a[x][y],
							2000 + (x - 5) * 100 + (y - 5) * 10 + a[x][y]);
				}
				else if (x >= 9 || y >= 9)fprintf(fp, "%d 0\n", 2000 + (x - 5) * 100 + (y - 5) * 10 + a[x][y]);
				else fprintf(fp, "%d 0\n", 1000 + (x + 1) * 100 + (y + 1) * 10 + a[x][y]);
			}
	}
	for (int i = 1; i <= 2; ++i)
		for (int x = 1; x <= 9; ++x)
		{
			for (int y = 1; y <= 9; ++y)
			{
				for (int z = 1; z <= 9; ++z)
					fprintf(fp, "%d ", i * 1000 + x * 100 + y * 10 + z);
				fprintf(fp, "0\n");
			}
		}
	//row
	for (int p = 1; p <= 2; ++p)
		for (int y = 1; y <= 9; ++y)
		{
			for (int z = 1; z <= 9; ++z)
				for (int x = 1; x <= 8; ++x)
					for (int i = x + 1; i <= 9; ++i)
						fprintf(fp, "%d %d 0\n", -(p * 1000 + x * 100 + y * 10 + z),
								-(p * 1000 + i * 100 + y * 10 + z));
		}
	//column
	for (int p = 1; p <= 2; ++p)
		for (int x = 1; x <= 9; ++x)
		{
			for (int z = 1; z <= 9; ++z)
				for (int y = 1; y <= 8; ++y)
					for (int i = y + 1; i <= 9; ++i)
						fprintf(fp, "%d %d 0\n", -(p * 1000 + x * 100 + y * 10 + z),
								-(p * 1000 + x * 100 + i * 10 + z));
		}
	//3*3 sub-grids
	for (int p = 1; p <= 2; ++p)
		for (int z = 1; z <= 9; ++z)
		{
			for (int i = 0; i <= 2; ++i)
				for (int j = 0; j <= 2; ++j)
					for (int x = 1; x <= 3; ++x)
						for (int y = 1; y <= 3; ++y)
							for (int k = y + 1; k <= 3; ++k)
								fprintf(fp, "%d %d 0\n", -(p * 1000 + (3 * i + x) * 100 + (3 * j + y) * 10 + z),
										-(p * 1000 + (3 * i + x) * 100 + (3 * j + k) * 10 + z));
		}
	for (int p = 1; p <= 2; ++p)
		for (int z = 1; z <= 9; z++)
		{
			for (int i = 0; i <= 2; i++)
				for (int j = 0; j <= 2; j++)
					for (int x = 1; x <= 3; x++)
						for (int y = 1; y <= 3; y++)
							for (int k = x + 1; k <= 3; k++)
								for (int l = 1; l <= 3; l++)
									fprintf(fp, "%d %d 0\n", -(p * 1000 + (3 * i + x) * 100 + (3 * j + y) * 10 + z),
											-(p * 1000 + (3 * i + k) * 100 + (3 * j + l) * 10 + z));
		}
	for (int p = 1; p <= 9; ++p)
		for (int i = 1; i <= 3; ++i)
		{
			for (int j = 1; j <= 3; ++j)
			{
				fprintf(fp, "%d %d 0\n", 1000 + (i + 6) * 100 + (j + 6) * 10 + p, -(2000 + i * 100 + j * 10 + p));
				fprintf(fp, "%d %d 0\n", -(1000 + (i + 6) * 100 + (j + 6) * 10 + p), (2000 + i * 100 + j * 10 + p));
			}
		}
	fclose(fp);
}

int SudoDPLL(SATList* cnf, Value value[], int T)
{

	SATList* List = cnf;
	SATList* UnitClause = isUnitClause(List);
	while (UnitClause != NULL)
	{
		if (UnitClause->head->data > 0)
		{
			value[T].content = UnitClause->head->data;
			value[T++].value = 1;
		}
		int re = UnitClause->head->data;
		removeClause(UnitClause, &cnf);
		RemoveSATNode(re, &cnf);
		if (T == 162)return T;
		else if (emptyClause(cnf))
		{
			destroyClause(&cnf);
			return 0;
		}
		List = cnf;
		UnitClause = isUnitClause(List);
	}
	int Var = SudoKU_Max(cnf);
	SATList* replica = CopyClause(cnf);
	SATList* temp1 = CopyClause(cnf);
	SATList* temp2 = addClause(replica, -Var);
	temp1 = addClause(temp1, Var);
	int res;
	if ((res = SudoDPLL(temp1, value, T)) == 162)
	{
		destroyClause(&temp1);
		temp1 = NULL;
		return res;
	}
	else if ((res = SudoDPLL(temp2, value, T)) == 162)
	{
		destroyClause(&temp2);
		temp2 = NULL;
		return res;
	}
	return 0;
}

void Uniquejudge(const int a[][15], const int b[][16])
{
	int i, j;
	for (i = 1; i <= 15; i++)
	{
		for (j = 1; j <= 15; j++)
		{
			if (a[i - 1][j - 1] != b[i][j] && a[i - 1][j - 1] != 0)
			{
				printf("this result is not unique!\n");
				return;
			}
		}
	}
}

void SudokuShow(const Value value[])
{

	int res[16][16] = { 0 };
	for (int i = 0; i < 162; ++i)
	{
		int temp = value[i].content;
		if (value[i].value == 1)
		{
			if (value[i].content < 2000)
			{
				temp %= 1000;
				int x = temp / 100;
				int y = temp % 100 / 10;
				res[x][y] = temp % 10;
				if (res[x][y] == 0)
				{
					int flag = 1;
				}
			}
			else if (value[i].content > 2400 || (2140 < value[i].content && value[i].content <= 2199) ||
					 (2240 < value[i].content && value[i].content <= 2299) ||
					 (2340 < value[i].content && value[i].content <= 2399))
			{
				temp %= 1000;
				int x = temp / 100;
				int y = temp % 100 / 10;
				res[x + 6][y + 6] = temp % 10;
			}
		}
	}
	//输出result数组
	for (int i = 1; i <= 15; ++i)
	{
		for (int j = 1; j <= 15; ++j)
		{
			if (res[i][j] != 0)
				printf("%d ", res[i][j]);
			else if (res[i][j] == 0)
				printf("  ");
		}
		printf("\n");
	}
	Uniquejudge(sudoku, res);
}