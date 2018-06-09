#ifndef SOMMET_H
#define SOMMET_H

#include <QGraphicsItem>
#include <QList>
#include <QGraphicsSceneMouseEvent>
#include <QLineEdit>
#include "arete.h"
#include <QMainWindow>
#include <QApplication>
class sommet : public QGraphicsItem
{
public:
    sommet();
    void ajouterArete(arete *arete);
    void ajouterArc(arc *arc);
    void supprimerArete(arete *arete);
    void supprimerAretes();
    void supprimerArc(arc *arc);
    void supprimerArcs();
    enum { Type = UserType + 15 };
    int type() const Q_DECL_OVERRIDE { return Type; }
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    QList<arete *> aretelist;
    QList<arc *> arclist;
    QList<arc *> arclist2;
    QList<arc *> arclist3;
    QString valSommet = "sommet";
    QString valMachine = "1";
    QLineEdit* pLineEdit;
    QGraphicsProxyWidget* pMyProxy;
    QLineEdit* pLineEdit2;
    QGraphicsProxyWidget* pMyProxy2;
    int indexSommet;
    int sommetJob;
    int modde = 0;
    int degre = 0;
    int degre_ = 0;
    int date_plutot;
    int date_plutard;
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;//Attention
   // void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void hoverEnterEvent (QGraphicsSceneHoverEvent *event) override
    {
      QGraphicsItem::hoverEnterEvent(event);
      QApplication::setOverrideCursor(Qt::PointingHandCursor);
    }

    virtual void hoverLeaveEvent (QGraphicsSceneHoverEvent *event) override
    {
      QGraphicsItem::hoverLeaveEvent(event);
      QApplication::setOverrideCursor(Qt::ArrowCursor);
    }
private:
    QPointF newPos;
};

#endif // SOMMET_H
