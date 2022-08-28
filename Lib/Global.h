//
// Created by zxc02 on 2022/8/11.
//

#ifndef SUDOKU_GLOBAL_H
#define SUDOKU_GLOBAL_H

#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROW 15
#define COL 15
typedef struct Count
{
	int Negative;
	int Positive;
	int num;
} Count;
typedef struct SATNode
{
	int data;
	struct SATNode* next;
} * SATNODE, SATNode;
typedef struct SATList
{
	int length;
	SATNode* head;
	struct SATList* next;
} * SATLIST, SATList;
typedef struct Value
{
	int value;
	int content;
} Value;
extern int boolCount;
extern int clauseCount;
extern char FileName[150];
extern int sudoku[ROW][COL];
extern int starting_grid[ROW][COL];
extern int holes;
extern Count* count;

extern Value SudoResult[163];

void Menu();

void Reset();

void Sudoku();

int LoadFile(SATLIST* temp, char* fileName);

void ShowFile(SATList* List);

int WriteFile(int result, double time, const int value[]);

void Solution(SATList* List);

void RemoveSATNode(int re, SATLIST* List);

void destroyClause(SATLIST* cnf);

SATList* isUnitClause(SATList* List);

void removeClause(SATList* Clause, SATLIST* root);

int removeNode(SATNode* cnf, SATNODE* head);

void SudokuShow(const Value value[]);

SATList* addClause(SATList* cnf, int var);

int emptyClause(SATList* cnf);


SATList* CopyClause(SATList* List);

int Max(SATList* List);

int DPLL(SATList* cnf, int value[]);

int DPLL1(SATList* cnf, int value[]);

int Digit1(int a[][COL], int i, int j);

int Digit2(int a[][COL], int i, int j);

void randomFirstRow(int a0[], int p1, int p2);

void createSudoku(int a[][COL]);

void createStartinggrid(const int a[][COL], int b[][COL], int numDigits);

void print(const int a[][COL]);

void ToCnf(int a[][COL], int hole);


int SudoDPLL(SATList* cnf, Value value[],int T);

int SudoKU_Max(SATList* List);

void UniqueJudge(const int a[][COL], const int b[][16]);

void SudokuAns(const Value value[]);

#endif //SUDOKU_GLOBAL_H
