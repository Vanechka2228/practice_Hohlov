#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#pragma once

#include <QGraphicsScene>
#include <QVector>
#include <QRectF>
#include <QColor>
#include "figures.h"

class CanvasView : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit CanvasView(QObject* parent = nullptr);
    ~CanvasView() override;

    void setCurrentShapeType (int type);
    void setCurrentFill (const QColor& c);
    void setCurrentBorder (const QColor& c);

    bool saveToFile (const QString& fileName);
    bool loadFromFile (const QString& fileName);

    const QVector<Shape*>& getShapes() const{return figures;}

    void mousePressEvent (QGraphicsSceneMouseEvent* ev) override;
    void mouseReleaseEvent (QGraphicsSceneMouseEvent* ev) override;
    void drawForeground (QPainter* painter, const QRectF& rect) override;
    void clearAllShapes ();

signals:
    void figureAdded();

private:
    int currentType;
    QColor currentFill;
    QColor currentBorder;
    QPointF pressPos;
    QPointF releasePos;
    QVector<Shape*> figures;
};


#endif // CANVASVIEW_H
