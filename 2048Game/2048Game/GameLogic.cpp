#include "stdafx.h"
#include "GameLogic.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;


GameLogic::GameLogic()
{
	Init();
}


GameLogic::~GameLogic()
{
}

void GameLogic::Init()
{
	curStep = 0;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			grid[i][j] = 0;
		}
	}

	vector<int> v = GetEmptyGrids();
	random_shuffle(v.begin(), v.end());
	int n1 = v[0];
	int n2 = v[1];
	int x1 = Int2GridPos(n1).first;
	int y1 = Int2GridPos(n1).second;
	int x2 = Int2GridPos(n2).first;
	int y2 = Int2GridPos(n2).second;
	grid[x1][y1] = 2;
	grid[x2][y2] = 4;
}

vector<vector<int> > GameLogic::GetCurGrid() const
{
	vector<vector<int> > v(N, vector<int>(N, 0));
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			v[i][j] = grid[i][j];
		}
	}
	return v;
}

int GameLogic::GridPos2Int(int x, int y) const
{
	return x * N + y;
}

std::pair<int, int> GameLogic::Int2GridPos(int n) const
{
	int x = n / N;
	int y = n % N;
	return make_pair(x, y);
}

vector<int> GameLogic::GetEmptyGrids() const
{
	vector<int> v;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (grid[i][j] == 0)
			{
				v.push_back(GridPos2Int(i, j));
			}
		}
	}
	return v;
}

vector<int> GameLogic::CompressVector(const vector<int>& v) const
{
	vector<int> ret;
	for (size_t i = 0; i < v.size(); ++i)
	{
		if (v[i] != 0)
		{
			ret.push_back(v[i]);
		}
	}
	return ret;
}

std::vector<int> GameLogic::TransformRowOrCol(const std::vector<int>& v) const
{
	vector<int> curVector(v.begin(), v.end());
	vector<int> nextVector;
	while (true)
	{
		nextVector = CompressVector(curVector);
		bool hasEqual = false;
		for (size_t i = 1; i < nextVector.size(); ++i)
		{
			if (nextVector[i] == nextVector[i - 1])
			{
				hasEqual = true;
				nextVector[i - 1] *= 2;
				nextVector[i] = 0;
				break;
			}
		}

		if (!hasEqual)
		{
			break;
		}
		else
		{
			curVector.clear();
			curVector = nextVector;
		}
	}

	nextVector.resize(N, 0);
	return nextVector;
}

void GameLogic::PutRandomNumberInEmptyGrid()
{
	vector<int> emptyGrids = GetEmptyGrids();
	random_shuffle(emptyGrids.begin(), emptyGrids.end());
	if (emptyGrids.size() >= 1)
	{
		int n = emptyGrids[0];
		int x = Int2GridPos(n).first;
		int y = Int2GridPos(n).second;

		int r = rand() % 2;
		if (r == 0)
		{
			grid[x][y] = 2;
		}
		else
		{
			grid[x][y] = 4;
		}
	}
}

void GameLogic::MoveUp()
{
	for (int j = 0; j < N; ++j)
	{
		vector<int> col;
		for (int i = 0; i < N; ++i) col.push_back(grid[i][j]);
		vector<int> newcol = TransformRowOrCol(col);
		for (int i = 0; i < N; ++i) grid[i][j] = newcol[i];
	}
	PutRandomNumberInEmptyGrid();
	curStep++;
}


void GameLogic::MoveDown()
{
	for (int j = 0; j < N; ++j)
	{
		vector<int> col;
		for (int i = N - 1; i >= 0; --i) col.push_back(grid[i][j]);
		vector<int> newcol = TransformRowOrCol(col);
		for (int i = N - 1; i >= 0; --i) grid[i][j] = newcol[N - i - 1];
	}
	PutRandomNumberInEmptyGrid();
	curStep++;
}


void GameLogic::MoveLeft()
{
	for (int i = 0; i < N; ++i)
	{
		vector<int> row;
		for (int j = 0; j < N; ++j) row.push_back(grid[i][j]);
		vector<int> newrow = TransformRowOrCol(row);
		for (int j = 0; j < N; ++j) grid[i][j] = newrow[j];
	}
	PutRandomNumberInEmptyGrid();
	curStep++;
}


void GameLogic::MoveRight()
{
	for (int i = 0; i < N; ++i)
	{
		vector<int> row;
		for (int j = N - 1; j >= 0; --j)	 row.push_back(grid[i][j]);
		vector<int> newrow = TransformRowOrCol(row);
		for (int j = N - 1; j >= 0; --j) grid[i][j] = newrow[N - 1 - j];
	}
	PutRandomNumberInEmptyGrid();
	curStep++;
}

bool GameLogic::IsWin() const
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (grid[i][j] == 2048)
			{
				return true;
			}
		}
	}
	return false;
}


bool GameLogic::IsLose() const
{
	bool isFull = true;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (grid[i][j] == 0)
			{
				isFull = false;
				break;
			}
		}
	}

	bool hasEqual = false;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (j + 1 < N && grid[i][j] == grid[i][j + 1])
			{
				hasEqual = true;
				break;
			}
			else if (i + 1 < N && grid[i][j] == grid[i + 1][j])
			{
				hasEqual = true;
				break;
			}
		}
	}

	return (isFull && !hasEqual);
}


