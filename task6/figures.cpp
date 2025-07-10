#include "figures.h"
#include <algorithm>
#include <cmath>

Shape::Shape(const QPointF& p1,const QPointF& p2,const QColor& fill,const QColor& border): v1(p1),v2(p2),_fillColor(fill),_borderColor(border){}

void Shape::setPoints(const QPointF& p1, const QPointF& p2)
{
    v1 = p1;
    v2 = p2;
}

QRectF Shape::borderRect() const
{
    double xMin = std::min(v1.x(), v2.x());
    double yMin = std::min(v1.y(), v2.y());
    double xMax = std::max(v1.x(), v2.x());
    double yMax = std::max(v1.y(), v2.y());
    return QRectF(QPointF(xMin, yMin), QPointF(xMax, yMax));
}

void Shape::setFillColor(const QColor& col) {_fillColor = col;}

QColor Shape::fillColor() const {return _fillColor;}

void Shape::setBorderColor(const QColor& col) {_borderColor = col;}

QColor Shape::borderColor() const {return _borderColor;}

//
Rectangle::Rectangle(const QPointF &p1, const QPointF &p2, const QColor &fill, const QColor &border):Shape(p1,p2,fill,border){}

void Rectangle::draw(QPainter& painter) const
{
    painter.setBrush(_fillColor);
    painter.setPen(_borderColor);
    painter.drawRect(borderRect());
}

double Rectangle::area() const
{
    return fabs((v1.x()-v2.x())*(v1.y()-v2.y()));
}

double Rectangle::perimeter() const
{
    return 2.0*(fabs(v1.x()-v2.x())+fabs(v1.y()-v2.y()));
}

void Rectangle::writeData(QDataStream &out) const
{
    out << v1 << v2 << _fillColor << _borderColor;
}

void Rectangle::readData(QDataStream &in)
{
    in >> v1 >> v2 >> _fillColor >> _borderColor;
}

int Rectangle::shapeType() const
{
    return 1;
}
//

Ellipse::Ellipse(const QPointF &p1, const QPointF &p2, const QColor &fill, const QColor &border):Shape(p1,p2,fill,border){}

void Ellipse::draw(QPainter& painter) const
{
    painter.setBrush(_fillColor);
    painter.setPen(_borderColor);
    painter.drawEllipse(borderRect());
}

double Ellipse::area() const
{
    return M_PI*fabs((v1.x()-v2.x())*(v1.y()-v2.y()))/4;
}

double Ellipse::perimeter() const //P=4*(pi*a*b+(a-b)^2)/(a+b)
{
    double a=fabs((v1.x()-v2.x()))/2;
    double b=fabs((v1.y()-v2.y()))/2;
    double P=4.0*(M_PI*a*b+pow(a-b,2))/(a+b);
    return P;
}

void Ellipse::writeData(QDataStream &out) const
{
    out << v1 << v2 << _fillColor << _borderColor;
}

void Ellipse::readData(QDataStream &in)
{
    in >> v1 >> v2 >> _fillColor >> _borderColor;
}

int Ellipse::shapeType() const
{
    return 2;
}

//
Rhomb::Rhomb(const QPointF &p1, const QPointF &p2, const QColor &fill, const QColor &border):Shape(p1,p2,fill,border){}

void Rhomb::draw(QPainter& painter) const
{
    painter.setBrush(_fillColor);
    painter.setPen(_borderColor);
    painter.drawPath(painterPath());
}

double Rhomb::area() const
{
    return fabs((v1.x()-v2.x())*(v1.y()-v2.y()))/2.0;
}

double Rhomb::perimeter() const
{
    QRectF r = borderRect();
    double a = r.width() / 2.0;
    double b = r.height() / 2.0;
    double c = hypot(a, b);
    return c*4.0;
}

void Rhomb::writeData(QDataStream& out) const
{
    out << v1 << v2 << _fillColor << _borderColor;
}

void Rhomb::readData(QDataStream& in)
{
    in >> v1 >> v2 >> _fillColor >> _borderColor;
}

int Rhomb::shapeType() const
{
    return 3;
}

//
Triangle::Triangle(const QPointF &p1, const QPointF &p2, const QColor &fill, const QColor &border):Shape(p1,p2,fill,border){}

void Triangle::vertices(QPointF &p1, QPointF &p2, QPointF &p3) const
{
    QRectF r = borderRect();
    double s = r.width(); //сторона равна ширине
    double h = r.height();//высота равна длине прямоугольника, т.к. мы передаём в конструктор только подходящий прямоугольник

    double x0 = r.x();
    double y0 = r.y() + r.height();

    p1 = QPointF(x0,y0);
    p2 = QPointF(x0 + s,y0);
    p3 = QPointF(x0 + s/2.0,y0 - h);
}

void Triangle::draw(QPainter& painter) const
{
    QPointF a, b, c;
    vertices(a, b, c);
    painter.setBrush(_fillColor);
    painter.setPen(_borderColor);
    QPolygonF triang {a,b,c};
    painter.drawPolygon(triang);
}

double Triangle::area() const
{
    double s = borderRect().width();
    return sqrt(3.0)/4.0*s*s;
}

double Triangle::perimeter() const
{
    double s = borderRect().width();
    return 3.0 * s;
}

void Triangle::writeData(QDataStream& out) const
{
    out << v1 << v2 << _fillColor << _borderColor;
}

void Triangle::readData(QDataStream& in)
{
    in >> v1 >> v2 >> _fillColor >> _borderColor;
}

int Triangle::shapeType() const
{
    return 4;
}
