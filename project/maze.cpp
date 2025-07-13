#include "maze.h"
#include <QVector>
#include <ctime>
#include <QStack>
#include <QList>
#include <QPair>

Maze::Maze(int rows, int cols):height(rows),width(cols)
{
    grid.resize(height);
    for (int r = 0; r < height; ++r)
    {
        grid[r].resize(width);
        for (int c = 0; c < width; ++c)
        {
            grid[r][c].row = r;
            grid[r][c].col = c;
            grid[r][c].leftWall = true;
            grid[r][c].rightWall = true;
            grid[r][c].topWall = true;
            grid[r][c].bottomWall = true;
            grid[r][c].visited = false;
        }
    }
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Maze::Generate()
{
    for (int r = 0; r < height; ++r)
    {
        for (int c = 0; c < width; ++c)
        {
            grid[r][c].leftWall = true;
            grid[r][c].rightWall = true;
            grid[r][c].topWall = true;
            grid[r][c].bottomWall = true;
            grid[r][c].visited = false;
        }
    }
    int start_row = rand() % height;
    int start_col = rand() % width;
    grid[start_row][start_col].visited = true;
    QStack <Cell*> path;
    Cell *start = &grid[start_row][start_col];
    path.push(start);
    while (!path.isEmpty())
    {
        Cell *current=path.top();
        int r=current->row;
        int c=current->col;
        QList <Cell*> cur_Neighbours;
        if (c > 0) //слева
        {
            Cell *left = &grid[r][c - 1];
            if (!left->visited) cur_Neighbours.push_back(left);
        }
        if (c + 1 < width) //справа
        {
            Cell *right = &grid[r][c + 1];
            if (!right->visited) cur_Neighbours.push_back(right);
        }
        if (r > 0) //сверху
        {
            Cell *up = &grid[r - 1][c];
            if (!up->visited) cur_Neighbours.push_back(up);
        }
        if (r + 1 < height) // снизу
        {
            Cell *down = &grid[r + 1][c];
            if (!down->visited) cur_Neighbours.push_back(down);
        }
        if (!cur_Neighbours.isEmpty())
        {
            Cell *next = cur_Neighbours.at(std::rand() % cur_Neighbours.size());

            // удаляем стенки между current и next
            if (next->col < current->col) //сосед слева
            {
                current->leftWall = false;
                next->rightWall = false;
            }
            else
                if (next->col > current->col) //сосед справа
                {
                    current->rightWall = false;
                    next->leftWall = false;
                }
                else
                    if (next->row < current->row) //сосед сверху
                    {
                        current->topWall = false;
                        next->bottomWall = false;
                    }
                    else //сосед снизу
                    {
                        current->bottomWall = false;
                        next->topWall = false;
                    }
            // заносим нового соседа и погружаемся дальше
            next->visited = true;
            path.push(next);
        }
        // если тупик, то возвращаемся назад
        else
            path.pop();
    }
}

const QVector<QVector<Cell>>& Maze::m_Grid() const {return grid;}

void Maze::setEntranceExit()
{
    // вход в первой строке
    int ent_col = std::rand() % width;
    entrance.first = 0;
    entrance.second = ent_col;
    grid[0][ent_col].topWall = false;

    // выход в последней
    int ex_col = std::rand() % width;
    exit.first = height - 1;
    exit.second = ex_col;
    grid[height-1][ex_col].bottomWall = false;
}

QPair<int,int> Maze::m_Entrance() const
{
    return entrance;
}

QPair<int,int> Maze::m_Exit() const
{
    return exit;
}
