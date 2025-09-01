#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QColorDialog>
#include <QKeyEvent>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Лабиринт");
    m_field = new MazeField(65,this);
    ui->graphicsView->setBackgroundBrush(QBrush(QColor(245, 240, 230, 180)));
    ui->graphicsView->setScene(m_field);
    ui->graphicsView->setAlignment(Qt::AlignCenter); //ДОРАБОТКА добавлено центрирование лабиринта на экране
    ui->graphicsView->installEventFilter(this);
    makeMaze();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_model;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) //для перехвата и обработки нажатия стрелок именно в graphicsView
{
    if (watched == ui->graphicsView && event->type() == QEvent::KeyPress)
    {
        QKeyEvent* _key = static_cast<QKeyEvent*>(event); //приводим к QKeyEvent, чтобы обработать нажатия
        switch (_key->key())
        {
        case Qt::Key_Up: movePlayer(-1, 0);
            return true;
        case Qt::Key_Down: movePlayer(1, 0);
            return true;
        case Qt::Key_Left: movePlayer(0, -1);
            return true;
        case Qt::Key_Right: movePlayer(0, 1);
            return true;
        default:
            break;
        }
    }
    return QMainWindow::eventFilter(watched, event); // для остальных событий обычная маршрутизация
}

void MainWindow::makeMaze()
{
    delete m_model;
    m_model = new Maze(height, width);
    m_model->Generate();
    m_model->setEntranceExit();
    m_field->setModel(m_model);
    m_field->draw();
    m_playerRow = m_model->m_Entrance().first;
    m_playerCol= m_model->m_Entrance().second;
    m_field->setPlayerPosition(m_playerRow,m_playerCol,m_playerColor);
}

void MainWindow::movePlayer(int dr, int dc)
{
    if (!m_model)
        return;
    int newRow = m_playerRow + dr;
    int newCol = m_playerCol + dc;
    if (newRow < 0 || newCol < 0 ||newRow >= height ||newCol >= width) //проверка границ
        return;
    const Cell &current = m_model->m_Grid()[m_playerRow][m_playerCol];
    if ((dr == -1 && current.topWall) || (dr == +1 && current.bottomWall) || (dc == -1 && current.leftWall) || (dc == +1 && current.rightWall)) // проверка на наличие стенки
        return;
    m_playerRow = newRow;
    m_playerCol = newCol;
    m_field->setPlayerPosition(m_playerRow, m_playerCol, m_playerColor);
    if (m_playerRow == m_model->m_Exit().first && m_playerCol == m_model->m_Exit().second)
        if (QMessageBox::information(nullptr,"Поздарвляем!","Лабиринт пройден",QMessageBox::Ok)==QMessageBox::Ok) //ДОРАБОТКА автоматическое создание лабиринта прежнего размера после прохождения текущего
    makeMaze();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up: movePlayer(-1, 0);
        break;
    case Qt::Key_Down: movePlayer(1, 0);
        break;
    case Qt::Key_Left: movePlayer(0, -1);
        break;
    case Qt::Key_Right: movePlayer(0, 1);
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}


void MainWindow::on_action_triggered()
{
    Dialog dlg(height, width, this);
    if (dlg.exec() == QDialog::Accepted)
    {
        double free_area;
        if (std::max(height,width)<21)
            free_area = 520.0;
        else if (std::max(height,width)<36)
            free_area = 575.0;
        else
            free_area = 630.0;
        double size = free_area / std::max(height,width);
        m_field->setCellSize(size);
        makeMaze();
    }
}


void MainWindow::on_action_2_triggered()
{
    makeMaze();
}

void MainWindow::on_action_4_triggered()
{
    QColor c = QColorDialog::getColor(nullptr, this);
    if (!c.isValid()) return;
    m_playerColor = c;
    m_field->setPlayerPosition(m_playerRow, m_playerCol, m_playerColor);
}


void MainWindow::on_action_6_triggered()
{
    m_playerRow=m_model->m_Entrance().first;
    m_playerCol=m_model->m_Entrance().second;
    m_field->setPlayerPosition(m_playerRow,m_playerCol,m_playerColor);
}


void MainWindow::on_action_7_triggered()
{
    close();
}
