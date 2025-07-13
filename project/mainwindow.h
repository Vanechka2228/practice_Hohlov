#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "maze.h"
#include "mazefield.h"
#include <QColorDialog>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_4_triggered();

    void on_action_6_triggered();

    void on_action_7_triggered();

protected:

    void keyPressEvent(QKeyEvent *event) override;

    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void movePlayer(int dr, int dc);
    void makeMaze();
    Ui::MainWindow *ui;
    Maze *m_model = nullptr;
    MazeField *m_field = nullptr;
    int height = 8;
    int width = 8;
    int m_playerRow;
    int m_playerCol;
    QColor m_playerColor = Qt::red;
};
#endif // MAINWINDOW_H
