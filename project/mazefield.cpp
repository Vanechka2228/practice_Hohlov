#include "mazefield.h"
#include <QVector>
#include <QColor>
#include <QGraphicsRectItem>

MazeField::MazeField(int cellSize, QObject *parent)
    : QGraphicsScene(parent)
    , m_cellSize(cellSize)
{}

void MazeField::setModel(Maze *model)
{
    m_model=model;
}

void MazeField::setCellSize(int cellSize)
{
    m_cellSize=cellSize;
}

void MazeField::draw()
{
    clear();
    m_playerItem = nullptr;
    const auto &grid = m_model->m_Grid();
    int rows = grid.size();
    if (rows == 0) return;
    int cols = grid[0].size();
    // рисуем стены
    QPen wallPen(QColor(110, 110, 110));
    wallPen.setWidth(2);
    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            const Cell &cell = grid[r][c];
            int x= c*m_cellSize;
            int y = r*m_cellSize;

            if (cell.topWall)
                addLine(x, y, x + m_cellSize, y, wallPen);
            if (cell.bottomWall)
                addLine(x, y + m_cellSize,x + m_cellSize, y + m_cellSize, wallPen);
            if (cell.leftWall)
                addLine(x, y, x, y + m_cellSize, wallPen);
            if (cell.rightWall)
                addLine(x + m_cellSize, y, x + m_cellSize, y + m_cellSize, wallPen);
        }
    }
    addRect(m_model->m_Exit().second * m_cellSize, m_model->m_Exit().first * m_cellSize, m_cellSize, m_cellSize, QPen(Qt::NoPen), QBrush(Qt::green));//помечаем выход
    setSceneRect(0, 0, cols * m_cellSize, rows * m_cellSize);//ДОРАБОТКА установка границ сцены
}

void MazeField::setPlayerPosition(int row, int col, QColor player_color)
{
    if (!m_playerItem)
        m_playerItem = addRect(0, 0, m_cellSize, m_cellSize,QPen(Qt::NoPen),QBrush(player_color));
    else
        m_playerItem->setBrush(QBrush(player_color));
    m_playerItem->setOpacity(0.65);
    m_playerItem->setPos(col * m_cellSize, row * m_cellSize);
}
