#include "sommet.h"
#include "fenetreprincipale.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
sommet::sommet()
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setAcceptHoverEvents(true);
}
void sommet::ajouterArete(arete *arete){
    aretelist.append(arete);
    arete->adjust();
    arete->updatePosition();
}
void sommet::ajouterArc(arc *arc){
    arclist.append(arc);
    arc->adjust();
    arc->updatePosition();

}
QRectF sommet::boundingRect() const
{
    qreal adjust = 16;
    return QRectF( -10 - adjust, -10 - adjust, 50 + adjust, 50 + adjust);
}
QPainterPath sommet::shape() const
{
    QPainterPath path;
    path.addEllipse(-20, -20, 40, 40);
    return path;
}
void sommet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    if(this->modde == 1){
        painter->setBrush(QBrush(Qt::green));
    }
    if(this->modde == 2){
        painter->setBrush(QBrush(Qt::red));
    }
    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);

}
QVariant sommet::itemChange(GraphicsItemChange change, const QVariant &value){
    switch (change) {
    case ItemPositionHasChanged:
        foreach (arete *arete, aretelist)
            arete->adjust();
        foreach (arc *arc, arclist)
            arc->adjust();
        break;
    default:
        break;
};

    return QGraphicsItem::itemChange(change, value);
}
void sommet::supprimerArete(arete *arete){

    int index = aretelist.indexOf(arete);

    if (index != -1)
        aretelist.removeAt(index);

}
void sommet::supprimerAretes(){
    foreach(arete *arete ,aretelist){
        arete->sourceSommet()->supprimerArete(arete);
        arete->destSommet()->supprimerArete(arete);
        scene()->removeItem(arete);   //scene() Returns the current scene for the item, or 0 if the item is not stored in a scene.
        delete arete;
    }
}
void sommet::supprimerArc(arc *arc){
    int index = arclist.indexOf(arc);
    if (index != -1)
        arclist.removeAt(index);
}
void sommet::supprimerArcs(){
    foreach(arc *arc ,arclist){
        arc->sourceSommet()->supprimerArc(arc);
        arc->destSommet()->supprimerArc(arc);
        scene()->removeItem(arc);   //scene() Returns the current scene for the item, or 0 if the item is not stored in a scene.
        delete arc;
    }
}


