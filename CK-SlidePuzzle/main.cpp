#include "myheader.h"
using namespace std;

int main()
{
	int canvas[4][4] = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 0}
	};

	const int SCORE_LEN = 5;
	double scores_time[SCORE_LEN] = { 0, };
	int scores_movement[SCORE_LEN] = { 0, };

	double cur_score = 0;
	srand((unsigned)time(NULL));

	while (true)
	{
		int input;
		cout << "CK Slide Puzzle\n";
		cout << "1. ���� ����\n2. ��ŷ Ȯ��\n3. ���� ����\n�Է�: ";

		cin >> input;
		ClearConsole();
		if (input == 1)
		{
			PrintCanvas(canvas);
			cout << "����Ű�� ������ �������� �����ϴ�.\n";

			WaitEnterKey();
			Coordinate cur = { 3,3 };
			for (int i = 0; i < 80; i++)
			{
				ShuffleCanvas(canvas, &cur);
				ClearConsole();
				PrintCanvas(canvas);
				cout << "�������� ���� ��...\n";
			}

			while (!CheckSolvable(canvas, cur))
			{
				ShuffleCanvas(canvas, &cur);
			}

			ClearConsole();
			PrintCanvas(canvas);

			clock_t t1 = clock();
			cout << "������ ���۵Ǿ����ϴ�. ����Ű�� �����Ͻʽÿ�.";

			while (true)
			{
				ArrowKey key = GetArrowKey();

				if (key == ArrowKey::UP && cur.row < 3)
				{
					Swap(&canvas[cur.row][cur.col], &canvas[cur.row + 1][cur.col]);
					cur.row++;
				}
				else if (key == ArrowKey::DOWN && cur.row > 0)
				{
					Swap(&canvas[cur.row][cur.col], &canvas[cur.row - 1][cur.col]);
					cur.row--;
				}
				else if (key == ArrowKey::LEFT && cur.col < 3)
				{
					Swap(&canvas[cur.row][cur.col], &canvas[cur.row][cur.col + 1]);
					cur.col++;
				}
				else if (key == ArrowKey::RIGHT && cur.col > 0)
				{
					Swap(&canvas[cur.row][cur.col], &canvas[cur.row][cur.col - 1]);
					cur.col--;
				}
				ClearConsole();
				PrintCanvas(canvas);
				if (DetectCleared(canvas)) break;
			}
			cout << "\n\nŬ���� �Ϸ�!\n���͸� ������ ��� ȭ������ �̵��մϴ�.";
			WaitEnterKey();

			clock_t t2 = clock();
			double duration = ((double)t2 - t1) / CLOCKS_PER_SEC;
			cur_score = duration;

			ClearConsole();
			cout << "�ҿ� �ð�: " << cur_score << "��\n";
			cout << "\n���͸� ������ ��ŷ ȭ������ �̵��մϴ�.";

			SetLeaderBoard(scores_time, SCORE_LEN, cur_score);

			WaitEnterKey();
			PrintLeaderBoard(scores_time, SCORE_LEN);
			cout << "\n���͸� ������ ���� ȭ������ �̵��մϴ�.";

			WaitEnterKey();
			ClearConsole();
		}
		else if (input == 2)
		{
			PrintLeaderBoard(scores_time, SCORE_LEN);
			cout << "\n���͸� ������ ���� ȭ������ �̵��մϴ�.";

			WaitEnterKey();
			ClearConsole();
		}
		else if (input == 3)
		{
			return 0;
		}
		else
		{
			cout << "�߸��� �Է��Դϴ�.\n";
			cin.clear();
			cin.ignore();
		}
	}
}

void ClearConsole()
{
	system("cls");
}

void PrintCanvas(const int cv[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cv[i][j] < 10) cout << " ";
			if (cv[i][j] != 0) cout << cv[i][j];
			cout << "\t";
		}
		cout << "\n";
	}
}

void WaitEnterKey()
{
	while (true)
	{
		char a = _getch();
		if (a == '\r') return;
	}
}

void ShuffleCanvas(int cv[4][4], Coordinate* cur)
{
	Coordinate a;
	Coordinate b;

	a.row = rand() % 4;
	a.col = rand() % 4;

	b.row = rand() % 4;
	b.col = rand() % 4;

	if (cv[a.row][a.col] == 0)
	{
		*cur = b;
	}
	else if (cv[b.row][b.col] == 0)
	{
		*cur = a;
	}

	Swap(&cv[a.row][a.col], &cv[b.row][b.col]);
	Sleep(8);
}

void Swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

ArrowKey GetArrowKey()
{
	while (true)
	{
		int input = 0;
		while (1)
		{
			if (_kbhit())
			{
				input = _getch();
				if (input == 224)
				{
					input = _getch();
					switch (input)
					{
					case 72:
						return ArrowKey::UP;
					case 80:
						return ArrowKey::DOWN;
					case 75:
						return ArrowKey::LEFT;
					case 77:
						return ArrowKey::RIGHT;
					}
				}
			}
		}
	}
}

int GetInversionNum(const int arr[])
{
	int count = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = i + 1; j < 16; j++)
		{
			if (arr[j] && arr[i] && arr[i] > arr[j])
				count++;
		}
	}
	return count;
}

bool CheckSolvable(int cv[4][4], Coordinate cursor)
{
	int invCount = GetInversionNum((int*)cv);

	if ((4 - cursor.row) % 2 == 0)
	{
		return invCount % 2 != 0;
	}
	else
	{
		return invCount % 2 == 0;
	}
}

bool DetectCleared(const int cv[4][4])
{
	const int target[4][4] = {
	{1, 2, 3, 4},
	{5, 6, 7, 8},
	{9, 10, 11, 12},
	{13, 14, 15, 0}
	};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cv[i][j] != target[i][j]) return false;
		}
	}
	return true;
}

void SetLeaderBoard(double arr[], int len, double new_score)
{
	if (new_score < arr[len - 1] || arr[len - 1] == 0)
	{
		arr[len - 1] = new_score;
		for (int i = len - 1; i > 0; i--)
		{
			if (new_score > arr[i - 1] && arr[i - 1] != 0)
			{
				return;
			}
			arr[i] = arr[i - 1];
			arr[i - 1] = new_score;
		}
	}
}

void PrintLeaderBoard(const double arr[], int len)
{
	ClearConsole();
	cout << "Hall Of Fame\n";
	cout << "����\t����\n";
	for (int i = 0; i < len; i++)
	{
		cout << i + 1 << "\t" << arr[i];
		cout << "\n";
	}
}