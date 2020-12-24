#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>

enum class ArrowKey {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct Coordinate
{
	int row;
	int col;
};

void ClearConsole();
void PrintCanvas(const int cv[4][4]);
void WaitEnterKey();
void ShuffleCanvas(int cv[4][4], Coordinate* cur);
void Swap(int* a, int* b);
ArrowKey GetArrowKey();
int GetInversionNum(const int arr[]);
bool CheckSolvable(int cv[4][4], Coordinate cursor);
bool DetectCleared(const int cv[4][4]);
void SetLeaderBoard(double arr[], int len, double new_score);
void PrintLeaderBoard(const double arr[], int len);