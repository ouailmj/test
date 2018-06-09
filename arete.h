#ifndef ARETE_H
#define ARETE_H
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QString>
class sommet;

class arete : public QGraphicsLineItem
{
public:
    arete(sommet *sourceSommet, sommet *destSommet);

    sommet *sourceSommet();
    sommet *destSommet();

    void adjust();

    enum { Type = UserType + 4 }; // !!!!!!!!
    int type() const override { return Type; }
    void updatePosition();
    QGraphicsTextItem *text = new QGraphicsTextItem("1",this);
    qreal valArete;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
private:
    sommet *source, *dest;
    QPointF sourcePoint;
    QPointF destPoint;
    qreal areteSize;
};

class arc : public QGraphicsLineItem
{
public:
    arc(sommet *sourceSommet, sommet *destSommet);

    sommet *sourceSommet();
    sommet *destSommet();

    void adjust();

    enum { Type = UserType + 5 }; // !!!!!!!!
    int type() const override { return Type; }
    void updatePosition();
    QGraphicsTextItem *text = new QGraphicsTextItem("1",this);
    qreal valarc;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
private:
    sommet *source, *dest;
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arcSize;
};
#endif // ARETE_H
