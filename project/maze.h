#ifndef MAZE_H
#define MAZE_H
#include <QVector>
#include <QPair>

struct Cell
{
    int row;
    int col;
    bool leftWall;
    bool rightWall;
    bool topWall;
    bool bottomWall;
    bool visited;
};

class Maze
{
private:
    int width;
    int height;
    QPair<int,int> entrance;
    QPair<int,int> exit;
    QVector<QVector<Cell>> grid;
public:
    Maze(int rows,int cols);
    void Generate();
    const QVector<QVector<Cell>>& m_Grid() const;
    void setEntranceExit();
    QPair<int,int> m_Entrance() const;
    QPair<int,int> m_Exit() const;
};

#endif // MAZE_H
