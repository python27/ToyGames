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


//0. ��ʼ�����������ӳ��������հ״�ʳ��
//1. ÿһ�� Move һ��, IsNextStepSafe(); IsNextHasFood();
//2. ��Ӧ�����¼����������ң��ı䷽��
//3. ���ǰ���Ƿ����Ѿ���ʳ�����гԽ�ʳ��
//   �ı�������ͷ (move ֮ǰ��, ÿ�γԽ�ʳ����ڿհ״������µ�ʳ��
//4. �����ײ����������ײ����ǽ����ײ, �������ײ, game over
//5. ������еĸ��Ӷ��Ѿ�ռ������game win