#include "graphics.h"
#include "ui_graphics.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QVector>
#include <QMessageBox>
#include <QString>

Graphics::Graphics(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Graphics)
    , scene(nullptr)
    , saved(true)
{
    ui->setupUi(this);
    setUpScene();
    connect(scene, &CanvasView::figureAdded, this, &Graphics::handleFigureAdded);
}

Graphics::~Graphics()
{
    delete ui;
}

void Graphics::setUpScene()
{
    scene = new CanvasView(this);
    scene->setBackgroundBrush(Qt::white);
    ui->graphicsView->setScene(scene);
    scene->setCurrentShapeType(0);
    scene->setCurrentBorder(Qt::black);
    scene->setCurrentFill(Qt::white);
}

void Graphics::updateStatusBar()
{
    QVector <Shape*> copy = scene->getShapes();
    if (copy.empty()) return;
    Shape* s = copy[copy.size()-1];
    QString typeStr;
    switch (s->shapeType())
    {
        case 0:
        return;
        case 1:
        {
            typeStr = "Прямоугольник";
            break;
        }
        case 2:
        {
            typeStr = "Эллипс";
            break;
        }
        case 3:
        {
            typeStr = "Ромб";
            break;
        }
        case 4:
        {
            typeStr = "Треугольник";
            break;
        }
    }
    QString message = QString("%1, заливка: %2, контур: %3, S = %4, P = %5").arg(typeStr).arg(s->fillColor().name()).arg(s->borderColor().name()).arg(s->area(),0,'f',2).arg(s->perimeter(), 0, 'f', 2);
    ui->statusbar->showMessage(message);
}


void Graphics::on_actionRectangle_triggered()
{
    scene->setCurrentShapeType(1);
}


void Graphics::on_actionEllipse_triggered()
{
    scene->setCurrentShapeType(2);
}


void Graphics::on_actionRhomb_triggered()
{
    scene->setCurrentShapeType(3);
}


void Graphics::on_actionTriangle_equilateral_triggered()
{
    scene->setCurrentShapeType(4);
}


void Graphics::on_actionset_default_color_black_triggered()
{
    scene->setCurrentBorder(Qt::black);
}


void Graphics::on_actionuser_choice_triggered()
{
    QColor c = QColorDialog::getColor(nullptr, this, "Цвет контура");
    if (!c.isValid()) return;
    scene->setCurrentBorder(c);
}



void Graphics::on_action_0_triggered()
{
    scene->setCurrentFill(Qt::white);
}


void Graphics::on_action_2_triggered()
{
    QColor c = QColorDialog::getColor(nullptr, this, "Цвет заливки");
    if (!c.isValid()) return;
    scene->setCurrentFill(c);
}


void Graphics::on_actionSave_current_result_to_bin_file_triggered()
{
    QString fn = QFileDialog::getSaveFileName(nullptr, "Выберите или создайте бинарный файл");
    if (fn=="") return;
    if (!scene->saveToFile(fn))
    {
        QMessageBox::critical(nullptr, "Ошибка!", QString("Не удалось сохранить файл %1").arg(fn));
    }
    saved=true;
}


void Graphics::on_actionRestore_figures_from_bin_file_triggered()
{
    QString fn = QFileDialog::getOpenFileName(nullptr, "Выберите бинарный файл");
    if (fn=="") return;
    if (!scene->loadFromFile(fn))
    {
        QMessageBox::critical(nullptr, "Ошибка!", QString("Не удалось загрузить данные из файла %1").arg(fn));
    }
    saved=true;
}


void Graphics::on_action_triggered()
{
    if (!saved)
    {
        int ret=QMessageBox::warning(nullptr,"Последние изменения не сохранены в файле","Точно хотите выйти, не сохранив изменения?","Да","Нет");
        if (ret) return;
    }
    close();
}


void Graphics::on_action_3_triggered()//очистка
{
    scene->clearAllShapes();
    saved = false;
    updateStatusBar();
    scene->setCurrentShapeType(0);
    scene->setCurrentFill(Qt::white);
    scene->setCurrentBorder(Qt::black);
}


void Graphics::handleFigureAdded()
{
    saved = false;
    updateStatusBar();
}
