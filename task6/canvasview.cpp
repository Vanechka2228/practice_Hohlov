#include "canvasview.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>

CanvasView::CanvasView(QObject* parent)
    : QGraphicsScene(parent)
{
    setSceneRect(0, 0, 700, 500);
}

CanvasView::~CanvasView()
{
    figures.clear();
}

void CanvasView::setCurrentShapeType(int type)
{
    currentType = type;
}

void CanvasView::setCurrentFill(const QColor& c)
{
    currentFill = c;
}

void CanvasView::setCurrentBorder(const QColor& c)
{
    currentBorder = c;
}

void CanvasView::mousePressEvent(QGraphicsSceneMouseEvent* ev)
{
    if (currentType == 0)
    {
        QGraphicsScene::mousePressEvent(ev);
        return;
    }
    if (ev->button() == Qt::LeftButton)
    {
        pressPos = ev->scenePos();
    }
    QGraphicsScene::mousePressEvent(ev);
}

void CanvasView::mouseReleaseEvent(QGraphicsSceneMouseEvent* ev)
{
    if (ev->button() != Qt::LeftButton || currentType==0)
    {
        QGraphicsScene::mouseReleaseEvent(ev);
        return;
    }
    releasePos = ev->scenePos();
    double base = fabs(releasePos.x() - pressPos.x());
    double height = fabs(releasePos.y() - pressPos.y());
    if (base <= 2 || height <= 2)
    {
        QGraphicsScene::mouseReleaseEvent(ev);
        return;
    }
    if (currentType == 4)
    {
        if (fabs(height - base * sqrt(3.0) / 2.0) > 1e-6)
        {
            int ch = QMessageBox::information(nullptr,"В данный прямоугольник невозможно вписать правильный треугольник",
            "Подогнать высоту под ширину или отменить рисование фигуры?", "Подогнать высоту","Отмена");
            if (ch == 0)
            {
                double newH = base * sqrt(3.0) / 2.0;
                if (releasePos.y() - pressPos.y() > 0)
                    releasePos.setY(pressPos.y() + newH);
                else
                    releasePos.setY(pressPos.y() - newH);
            }
            else
            {
                QGraphicsScene::mouseReleaseEvent(ev);
                return;
            }
        }
    }
    Shape *s;
    switch (currentType)
    {
    case 1:
    {
        s = new Rectangle(pressPos, releasePos, currentFill, currentBorder);
        break;
    }
    case 2:
    {
        s = new Ellipse(pressPos, releasePos, currentFill, currentBorder);
        break;
    }
    case 3:
    {
        s = new Rhomb(pressPos, releasePos, currentFill, currentBorder);
        break;
    }
    case 4:
    {
        s = new Triangle(pressPos, releasePos, currentFill, currentBorder);
        break;
    }
    }
    figures.push_back(s);
    update();
    emit figureAdded();
    QGraphicsScene::mouseReleaseEvent(ev);
}


void CanvasView::drawForeground(QPainter* painter, const QRectF&)
{
    painter->setRenderHint(QPainter::Antialiasing);
    for (Shape* s : figures)
    {
        s->draw(*painter);
    }
}

bool CanvasView::saveToFile(const QString& fileName)
{
    QFile f(fileName);
    if (!f.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        QMessageBox::critical(nullptr,"Ошибка!",QString("Не удалось открыть файл %1 для записи").arg(fileName));
        return false;
    }
    QDataStream out(&f);
    for (Shape* s : figures)
    {
        out <<s->shapeType();
        s->writeData(out);
    }
    return true;
}

bool CanvasView::loadFromFile(const QString& fileName)
{
    QFile f(fileName);
    if (!f.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(nullptr,"Ошибка!",QString("Не удалось открыть файл %1 для чтения").arg(fileName));
        return false;
    }
    figures.clear();
    QDataStream in(&f);
    int shapeCode;
    while (!in.atEnd())
    {
        in >> shapeCode;
        Shape* s = nullptr;
        switch (shapeCode)
        {
        case 1: s = new Rectangle({},{}); break;
        case 2: s = new Ellipse ({},{}); break;
        case 3: s = new Rhomb ({},{}); break;
        case 4: s = new Triangle ({},{}); break;
        }
        if (!s) break;
        s->readData(in);
        figures.push_back(s);
    }
    update();
    return true;
}

void CanvasView::clearAllShapes()
{
    qDeleteAll(figures);
    figures.clear();
    update();
}
