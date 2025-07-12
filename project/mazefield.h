#ifndef MAZEFIELD_H
#define MAZEFIELD_H
#include <QGraphicsScene>
#include <QColor>
#include "maze.h"

class MazeField: public QGraphicsScene {
    Q_OBJECT
public:
    MazeField(int cellSize, QObject *parent = nullptr);
    void setModel(Maze *model);
    void draw();
    void setPlayerPosition(int row, int col, QColor color);
    void setCellSize(int cellSize);
private:
    Maze *m_model = nullptr;
    int m_cellSize;
    QGraphicsRectItem *m_playerItem = nullptr;
};

#endif // MAZEFIELD_H
