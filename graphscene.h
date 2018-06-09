#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsTextItem>
#include <QGraphicsProxyWidget>
#include <QMessageBox>
#include <QPointF>
#include <QLineEdit>
#include <random>
#include <QDebug>
#include "sommet.h"

class graphscene : public QGraphicsScene
{
    Q_OBJECT
public:
    graphscene();//constructeur
    enum modechoisi {insererSommet ,insererArete,
                     ins,insererArc,supp,insererJob,insererDebut,
                        insererFin};//afin d'etudier les cas des bouttons_slots
    void setModechoisi(modechoisi mode);//retourner le mode choisi
    bool isItemChange(int type);//afin de determiner si l'item est selectionner
    QList <sommet *> sommetListe;//qlist de sommet afin de connaitre notre sommet
    void fonctionAleatoire();
    void scene_struct(QString filename);
    void scene_open(QString filename);
    void algopert(QList<sommet *> maliste);
    int a , b ,c ,d;//variable aleatoire
    QPointF point[20];
    QPointF parcourt[40];
    QString textval;
    QList<arete *> areteliste;
    QList<arc *> arcliste;
    QList<arc *> arcliste2;
    QList<sommet *> jobSommet;
    QList<sommet *> sommetInitial;
    QList<sommet *> sommetFinal;
    QList<sommet *> sommetParcourt;
    QList< QList<sommet *> > population;
    QList<QPointF >points;
    QList<sommet *> sommetinit;
    QList<sommet *>sommetFin;
    QList<int> fitness;
    bool exist = false;
    bool exist2 = false;
    bool job = false;
    bool creerjob = false;
    int valJob;
    bool usedinit = false;
    bool usedFin = false;
    void generationInitial();
    bool cycle(QList<sommet *> Liste);
    //QList<QPoint > cout;
    int cmax =0;
    int nb_mach;
    QList<int > tab;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
private:
    modechoisi _mode;//mode choisi
    sommet *_sommet;//declaration de poiteur de sommet
    arete * _arete;//declaration de poiteur arete
    arc * _arc;//declaration de poiteur arc
    QPointF startPoint;
    QGraphicsLineItem *line;
    QLineEdit* pLineEdit;
    QGraphicsProxyWidget* pMyProxy;
    int val=0;
signals:
    void itemSelected(QGraphicsItem *item);
    void itemInserted(sommet *item);
};

#endif // GRAPHSCENE_H
