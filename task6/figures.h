#ifndef FIGURES_H
#define FIGURES_H

#include <QPointF>
#include <QColor>
#include <QPainter>
#include <QPainterPath>
#include <QDataStream>
#include <QRectF>

class Shape
{
protected:
    QPointF v1;
    QPointF v2;
    QColor _fillColor;
    QColor _borderColor;
public:
    Shape(const QPointF& p1,const QPointF& p2,const QColor& fill = Qt::white, const QColor& border = Qt::black);
    virtual ~Shape()=default;

    virtual void draw(QPainter& painter) const=0;
    virtual QPainterPath painterPath() const=0;

    virtual double area() const=0;
    virtual double perimeter() const=0;

    virtual void writeData(QDataStream& out) const=0;
    virtual void readData(QDataStream& in)=0;

    void setPoints(const QPointF& p1, const QPointF& p2);
    QRectF borderRect() const;

    void setFillColor(const QColor& c);
    QColor fillColor() const;

    void setBorderColor(const QColor& c);
    QColor borderColor() const;

    virtual int shapeType ()const=0;
};

class Rectangle: public Shape
{
public:
    Rectangle(const QPointF& p1,const QPointF& p2,const QColor& fill = Qt::white, const QColor& border = Qt::black);
    ~Rectangle()=default;

    void draw(QPainter& painter) const override;
    QPainterPath painterPath() const override;

    double area() const override;
    double perimeter() const override;

    void writeData(QDataStream& out) const override;
    void readData(QDataStream& in) override;

    int shapeType() const override;
};

class Ellipse: public Shape
{
public:
    Ellipse(const QPointF& p1,const QPointF& p2,const QColor& fill = Qt::white, const QColor& border = Qt::black);
    ~Ellipse()=default;

    void draw(QPainter& painter) const override;
    QPainterPath painterPath() const override;

    double area() const override;
    double perimeter() const override;

    void writeData(QDataStream& out) const override;
    void readData(QDataStream& in) override;

    int shapeType() const override;
};

class Rhomb: public Shape
{
public:
    Rhomb(const QPointF& p1,const QPointF& p2,const QColor& fill = Qt::white, const QColor& border = Qt::black);
    ~Rhomb()=default;

    void draw(QPainter& painter) const override;
    QPainterPath painterPath() const override;

    double area() const override;
    double perimeter() const override;

    void writeData(QDataStream& out) const override;
    void readData(QDataStream& in) override;

    int shapeType() const override;
};


class Triangle: public Shape //правильный треугольник
{
private:
    void vertices(QPointF& p1,QPointF& p2,QPointF& p3) const;// вычисляем вершины равностороннего треугольника

public:
    Triangle(const QPointF& p1,const QPointF& p2,const QColor& fill = Qt::white, const QColor& border = Qt::black);
    ~Triangle()=default;

    void draw(QPainter& painter) const override;
    QPainterPath painterPath() const override;

    double area() const override;
    double perimeter() const override;

    void writeData(QDataStream& out) const override;
    void readData(QDataStream& in) override;

    int shapeType() const override;
};

#endif // FIGURES_H
