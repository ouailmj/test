#include "arete.h"
#include "sommet.h"
#include <math.h>

#include <QPainter>
#include <QDebug>
static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

arete::arete(sommet *sourceSommet, sommet *destSommet)
{
    areteSize = 10;
    //setAcceptedMouseButtons();
    source = sourceSommet;
    dest = destSommet;
    //source->ajouterArete(this);
    //dest->ajouterArete(this);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    text->setPos(boundingRect ().center ());
    text->setTextInteractionFlags(Qt::TextEditorInteraction);
    adjust();
    updatePosition();
}

sommet *arete::sourceSommet()
{
    return source;
}

sommet *arete::destSommet()
{
    return dest;
}

void arete::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20)) {
        QPointF areteOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        sourcePoint = line.p1() + areteOffset;
        destPoint = line.p2() - areteOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
    updatePosition();
}

QRectF arete::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + areteSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);

}

void arete::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0)))
        return;

    // arete (line)
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter->drawLine(line);

    // arete (triangle)
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = TwoPi - angle;

    QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + Pi / 3) * areteSize,
                                                  cos(angle + Pi / 3) * areteSize);
    QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + Pi - Pi / 3) * areteSize,
                                                  cos(angle + Pi - Pi / 3) * areteSize);
    QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi /3 ) * areteSize,
                                              cos(angle - Pi /3) * areteSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi /3) * areteSize,
                                              cos(angle - Pi + Pi /3) * areteSize);

    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
    updatePosition();
}


void arete::updatePosition()
{
    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    setLine(line);
    text->setPos(this->boundingRect ().center ());

}

//********************************************************

arc::arc(sommet *sourceSommet, sommet *destSommet)
{
    arcSize = 10;
    //setAcceptedMouseButtons();
    source = sourceSommet;
    dest = destSommet;
    //source->ajouterarc(this);
    //dest->ajouterarc(this);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    text->setPos(boundingRect ().center ());
    text->setTextInteractionFlags(Qt::TextEditorInteraction);
    adjust();
    updatePosition();
}

sommet *arc::sourceSommet()
{
    return source;
}

sommet *arc::destSommet()
{
    return dest;
}

void arc::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20)) {
        QPointF arcOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        sourcePoint = line.p1() + arcOffset;
        destPoint = line.p2() - arcOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
    updatePosition();
}

QRectF arc::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arcSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);

}

void arc::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0)))
        return;

    // arc (line)
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter->drawLine(line);

    // arc (triangle)
    double angle = ::acos(line.dx() / line.length());
   if (line.dy() >= 0)
        angle = TwoPi - angle;

   //QPointF sourceArrowP1 = sourcePoint; //+ QPointF(sin(angle + Pi / 3) * arcSize,
                                       //           cos(angle + Pi / 3) * arcSize);
   //QPointF sourceArrowP2 = sourcePoint;// + QPointF(sin(angle + Pi - Pi / 3) * arcSize,
                                       //           cos(angle + Pi - Pi / 3) * arcSize);
    QPointF destArrowP1 = destPoint + QPointF(sin(angle - Pi /3 ) * arcSize,
                                              cos(angle - Pi /3) * arcSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - Pi + Pi /3) * arcSize,
                                              cos(angle - Pi + Pi /3) * arcSize);

    painter->setBrush(Qt::black);
    //painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
    updatePosition();
}

void arc::updatePosition()
{
    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    setLine(line);
    text->setPos(this->boundingRect ().center ());

}
