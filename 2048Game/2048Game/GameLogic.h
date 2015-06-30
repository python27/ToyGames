#pragma once
#include <vector>
#include <utility>
class GameLogic
{
public:
	GameLogic();
	~GameLogic();
public:
	void Init();
	void clear();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	inline int GetSteps() const { return curStep; }
	bool IsWin() const;
	bool IsLose() const;
	bool IsEnd() const;
	std::vector<std::vector<int> > GetCurGrid() const;
private:
	int GridPos2Int(int x, int y) const;
	std::pair<int, int> Int2GridPos(int n) const;
	std::vector<int> GetEmptyGrids() const;
	std::vector<int> CompressVector(const std::vector<int>& v) const;
	std::vector<int> TransformRowOrCol(const std::vector<int>& v) const;
	void PutRandomNumberInEmptyGrid();
private:
	static const int N = 4;
	int grid[N][N];
	int curStep;
};