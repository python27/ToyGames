#include <deque>
#include <vector>

struct Point
{
    unsigned int x; 
    unsigned int y;
};

enum DIRECTION
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};



class Snake
{
public:
    Snake();
    ~Snake();
public:
    void TurnUp();
    void TurnDown();
    void TurnLeft();
    void TurnRight();

    bool IsNextSafe() const;
    bool IsNextHasFood() const;
    void EatFood();
    void MakeFoodRandomly();
    bool IsWin();
    bool IsLost();
private:
    std::deque<Point> m_body;
    Point m_food;
    DIRECTION m_direction;
private:
    static const unsigned int GRID_HEIGHT;
    static const unsigned int GRID_WIDTH;
};

const unsigned int Snake::GRID_WIDTH = 30;
const unsigned int Snake::GRID_HEIGHT = 40;


//0. 初始化，三个格子长的蛇身，空白处食物
//1. 每一秒 Move 一步, IsNextStepSafe(); IsNextHasFood();
//2. 响应键盘事件，上下左右，改变方向
//3. 检测前方是否有已经有食物，如果有吃进食物
//   改变身长，蛇头 (move 之前）, 每次吃进食物后在空白处产生新的食物
//4. 检测碰撞，与身体碰撞，与墙面碰撞, 如果有碰撞, game over
//5. 如果所有的格子都已经占满，则　game win