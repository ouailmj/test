#include <QFileDialog>
#include "graphscene.h"
#include "arete.h"
#include "sommet.h"
#include "fenetreprincipale.h"
graphscene::graphscene(){
    //qApp->setStyleSheet("QLineEdit#nameEdit {  }");
    //on n'a rien fait en constructeur afin d'appeler le constructeur de la class QGraphicsScene
}

void graphscene::setModechoisi(modechoisi mode){
    _mode = mode;//_mode est private
}

void graphscene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if (mouseEvent->button() != Qt::LeftButton)//click != click_gauche
        return;
    foreach (sommet *som, sommetListe) {
        if (som->isSelected()){
            som->valSommet = som->pLineEdit->text();
            som->valMachine = som->pLineEdit2->text();
            update();
        }
    }
    switch (_mode ) {
    case insererArete://areteSlot
        foreach (sommet *som, sommetListe) {
            som->pMyProxy->hide();
            som->pMyProxy2->hide();
        }
        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                            mouseEvent->scenePos()));
        addItem(line);
        break;

    case insererArc://arcslot
        foreach (sommet *som, sommetListe) {
            som->pMyProxy->hide();
            som->pMyProxy2->hide();
        }
        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                            mouseEvent->scenePos()));
        addItem(line);
        break;

    default:

        break;
    }

    QGraphicsScene::mousePressEvent(mouseEvent);

}

void graphscene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent){

    qDebug() << mouseEvent->scenePos();
    if(!sommetListe.empty()){
        foreach (sommet *som, sommetListe) {
            if (som->isSelected()){
                som->valSommet = som->pLineEdit->text();
                som->valMachine = som->pLineEdit2->text();
            }
        }
    }

    if (_mode == insererArete && line != 0) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    }

    else if (_mode == insererArc && line != 0) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    }

    else if (_mode == ins) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }

}

void graphscene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent){

    if(_mode == insererJob && creerjob == false){
        return;
    }
    else if(_mode == insererSommet){//creation de sommet
        if(!isItemChange(sommet::Type)){
            foreach (sommet *som, sommetListe) {
                if(som->isSelected()){
                    som->setSelected(false);
                }
            }
            _sommet = new sommet();//definition du pointeur
            sommetListe << _sommet;
            _sommet->indexSommet = sommetListe.indexOf(_sommet);
            qDebug() << _sommet->indexSommet;
            _sommet->setPos(mouseEvent->scenePos());
            addItem(_sommet);//pour ajouter à la scene
            _sommet->valSommet.append(QString("%1").arg(val));
            _sommet->pLineEdit = new QLineEdit(_sommet->valSommet);
            _sommet->pLineEdit->setObjectName("nameEdit");
            _sommet->pMyProxy = new QGraphicsProxyWidget(_sommet);
            _sommet->pLineEdit->setMaximumWidth(50);
            _sommet->pMyProxy->setWidget(_sommet->pLineEdit);
            _sommet->pMyProxy->hide();
            _sommet->pLineEdit2 = new QLineEdit(_sommet->valMachine);
            _sommet->pMyProxy2 = new QGraphicsProxyWidget(_sommet);
            _sommet->pLineEdit2->setMaximumWidth(30);
            _sommet->pMyProxy2->setWidget(_sommet->pLineEdit2);
            _sommet->setSelected(true);
            _sommet->pMyProxy2->hide();
            val++;
        }
    }
    else if(_mode == insererJob  && creerjob == true){
        if(mouseEvent->button() != Qt::RightButton){
            if(!isItemChange(sommet::Type)){
                foreach (sommet *som, sommetListe) {
                    if(som->isSelected()){
                        som->setSelected(false);
                    }
                }
                _sommet = new sommet();//definition du pointeur
                _sommet->indexSommet = sommetListe.indexOf(_sommet);
                qDebug() << _sommet->indexSommet;
                _sommet->setPos(mouseEvent->scenePos());
                addItem(_sommet);//pour ajouter à la scene
                _sommet->valSommet.append(QString("%1").arg(val));
                _sommet->pLineEdit = new QLineEdit(_sommet->valSommet);
                _sommet->pLineEdit->setObjectName("nameEdit");
                _sommet->pMyProxy = new QGraphicsProxyWidget(_sommet);
                _sommet->pLineEdit->setMaximumWidth(50);
                _sommet->pMyProxy->setWidget(_sommet->pLineEdit);
                _sommet->pMyProxy->hide();
                _sommet->pLineEdit2 = new QLineEdit(_sommet->valMachine);
                _sommet->pMyProxy2 = new QGraphicsProxyWidget(_sommet);
                _sommet->pLineEdit2->setMaximumWidth(30);
                _sommet->pMyProxy2->setWidget(_sommet->pLineEdit2);
                _sommet->setSelected(true);
                _sommet->pMyProxy2->hide();
                _sommet->sommetJob = this->valJob;
                jobSommet << _sommet;
                sommetListe << _sommet;
                val++;
            }
        }
        else if(mouseEvent->button() == Qt::RightButton){
            creerjob = false;
            qDebug() << "rightbutton";
            int i = 0;
            sommetInitial.append(jobSommet.at(0));
            sommetFinal.append(jobSommet.last());
            if(usedinit){
                _arc = new arc(sommetinit.first(), sommetInitial.last());
                arcliste.append(_arc);
                sommetinit.first()->ajouterArc(_arc);
                sommetInitial.last()->ajouterArc(_arc);
                addItem(_arc);
                _arc->adjust();
                _arc->updatePosition();
            }
            if(usedFin){
                _arc = new arc(sommetFinal.last(), sommetFin.first());
                arcliste.append(_arc);
                sommetFinal.last()->ajouterArc(_arc);
                sommetFin.first()->ajouterArc(_arc);
                addItem(_arc);
                _arc->adjust();
                _arc->updatePosition();
            }
            while(i != (jobSommet.length()-1)){
                sommet *somm = jobSommet.at(i);
                sommet *somm2 = jobSommet.at(i+1);
                _arc = new arc(somm , somm2);
                arcliste.append(_arc);
                somm->ajouterArc(_arc);
                jobSommet.at(i+1)->ajouterArc(_arc);
                addItem(_arc);
                _arc->adjust();
                _arc->updatePosition();
                i++;
            }
            jobSommet.clear();
        }
    }

    else if(_mode == insererDebut && usedinit == false){
        if(mouseEvent->button() != Qt::RightButton){
            if(!isItemChange(sommet::Type)){
                foreach (sommet *som, sommetListe) {
                    if(som->isSelected()){
                        som->setSelected(false);
                    }
                }
                _sommet = new sommet();//definition du pointeur
                _sommet->modde = 1;
                sommetListe << _sommet;
                _sommet->indexSommet = sommetListe.indexOf(_sommet);
                qDebug() << _sommet->indexSommet;
                _sommet->setPos(mouseEvent->scenePos());
                addItem(_sommet);//pour ajouter à la scene
                _sommet->valSommet.append(QString("%1").arg(" initiale"));
                _sommet->pLineEdit = new QLineEdit(_sommet->valSommet);
                _sommet->pLineEdit->setObjectName("nameEdit");
                _sommet->pMyProxy = new QGraphicsProxyWidget(_sommet);
                _sommet->pLineEdit->setMaximumWidth(50);
                _sommet->pMyProxy->setWidget(_sommet->pLineEdit);
                _sommet->pMyProxy->hide();
                _sommet->pLineEdit2 = new QLineEdit("-1");
                _sommet->valMachine = "-1";
                _sommet->pMyProxy2 = new QGraphicsProxyWidget(_sommet);
                _sommet->pLineEdit2->setMaximumWidth(30);
                _sommet->pMyProxy2->setWidget(_sommet->pLineEdit2);
                _sommet->setSelected(true);
                _sommet->pMyProxy2->hide();
                _sommet->sommetJob = 0;
                sommetinit << _sommet;
                usedinit = true;
                foreach(sommet *som,sommetInitial){
                    _arc = new arc(_sommet, som);
                    arcliste.append(_arc);
                    _sommet->ajouterArc(_arc);
                    som->ajouterArc(_arc);
                    addItem(_arc);
                    _arc->adjust();
                    _arc->updatePosition();
                }
            }
        }
    }

    else if(_mode == insererFin && usedFin == false){
        if(mouseEvent->button() != Qt::RightButton){
            if(!isItemChange(sommet::Type)){
                foreach (sommet *som, sommetListe) {
                    if(som->isSelected()){
                        som->setSelected(false);
                    }
                }
                _sommet = new sommet();//definition du pointeur
                _sommet->modde = 2;
                sommetListe << _sommet;
                _sommet->indexSommet = sommetListe.indexOf(_sommet);
                qDebug() << _sommet->indexSommet;
                _sommet->setPos(mouseEvent->scenePos());
                addItem(_sommet);//pour ajouter à la scene
                _sommet->valSommet.append(QString("%1").arg(" final"));
                _sommet->pLineEdit = new QLineEdit(_sommet->valSommet);
                _sommet->pLineEdit->setObjectName("nameEdit");
                _sommet->pMyProxy = new QGraphicsProxyWidget(_sommet);
                _sommet->pLineEdit->setMaximumWidth(50);
                _sommet->pMyProxy->setWidget(_sommet->pLineEdit);
                _sommet->pMyProxy->hide();
                _sommet->pLineEdit2 = new QLineEdit("-1");
                _sommet->valMachine = "-1";
                _sommet->pMyProxy2 = new QGraphicsProxyWidget(_sommet);
                _sommet->pLineEdit2->setMaximumWidth(30);
                _sommet->pMyProxy2->setWidget(_sommet->pLineEdit2);
                _sommet->setSelected(true);
                _sommet->pMyProxy2->hide();
                _sommet->sommetJob = 0;
                usedFin = true;
                sommetFin << _sommet;
                foreach(sommet *som,sommetFinal){
                    _arc = new arc(som, _sommet);
                    arcliste.append(_arc);
                    _sommet->ajouterArc(_arc);
                    som->ajouterArc(_arc);
                    addItem(_arc);
                    _arc->adjust();
                    _arc->updatePosition();
                }
            }
        }
    }

    else if (line != 0 && _mode == insererArete) {//creation de l'arete
        foreach (sommet *som, sommetListe) {
            som->pMyProxy->hide();
            som->pMyProxy2->hide();
        }
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();
        removeItem(line);
        delete line;


        if (startItems.count() > 0 && endItems.count() > 0 &&
                startItems.first()->type() == sommet::Type &&
                endItems.first()->type() == sommet::Type &&
                startItems.first() != endItems.first()) {
            sommet *startItem = qgraphicsitem_cast<sommet *>(startItems.first());
            sommet *endItem = qgraphicsitem_cast<sommet *>(endItems.first());
            foreach (arete * ar, areteliste){
                if((ar->sourceSommet() == startItem && ar->destSommet() == endItem)
                        || (ar->sourceSommet() == endItem && ar->destSommet() ==startItem)){
                    exist = true;
                }

            }
            foreach (arc * ac, arcliste){
                if((ac->sourceSommet() == startItem && ac->destSommet() == endItem)
                        || (ac->sourceSommet() == endItem && ac->destSommet() ==startItem)){
                    exist2 = true;
                }

            }

            if(exist ==false && exist2 == false){
                _arete = new arete(startItem, endItem);
                areteliste.append(_arete);
                startItem->ajouterArete(_arete);
                endItem->ajouterArete(_arete);
                _arete->valArete = _arete->text->toPlainText().toDouble();
                addItem(_arete);
                _arete->adjust();
                _arete->updatePosition();
            }
            else if(exist == true && exist == false){
                exist = false;
            }
            else if(exist == false && exist2 == true){
                exist2 = false;
                foreach(arc * ac,arcliste){
                    if((ac->sourceSommet() == startItem && ac->destSommet() == endItem) ||
                            (ac->sourceSommet() == endItem && ac->destSommet() == startItem)){
                        int index = arcliste.indexOf(ac);
                        this->removeItem(ac);
                        ac->sourceSommet()->supprimerArc(ac);
                        ac->destSommet()->supprimerArc(ac);
                        if (index != -1)
                            arcliste.removeAt(index);
                        delete ac;
                    }
                }
                _arete = new arete(startItem, endItem);
                areteliste.append(_arete);
                startItem->ajouterArete(_arete);
                endItem->ajouterArete(_arete);
                _arete->valArete = _arete->text->toPlainText().toDouble();
                addItem(_arete);
                _arete->adjust();
                _arete->updatePosition();
            }
        }
    }

    else if (line != 0 && _mode == insererArc) {//creation de l'arc
        foreach (sommet *som, sommetListe) {
            som->pMyProxy->hide();
            som->pMyProxy2->hide();
        }
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();
        removeItem(line);
        delete line;

        if (startItems.count() > 0 && endItems.count() > 0 &&
                startItems.first()->type() == sommet::Type &&
                endItems.first()->type() == sommet::Type &&
                startItems.first() != endItems.first()) {
            sommet *startItem = qgraphicsitem_cast<sommet *>(startItems.first());
            sommet *endItem = qgraphicsitem_cast<sommet *>(endItems.first());
            if(!areteliste.empty()){
                foreach (arc * ac, arcliste){
                    if((ac->sourceSommet() == startItem && ac->destSommet() == endItem)){
                        exist = true;
                        qDebug() << "oki";

                    }
                }
                foreach (arete * ar, areteliste) {
                    if((ar->sourceSommet() == startItem && ar->destSommet() == endItem) ||
                            (ar->sourceSommet() == endItem && ar->destSommet() == startItem)){
                        exist = true;
                        qDebug() << "oki";
                    }

                }
            }
            else{
                foreach (arc * ac, arcliste){
                    if((ac->sourceSommet() == startItem && ac->destSommet() == endItem)
                            //(ar->sourceSommet() == startItem && ar->destSommet() == endItem) ||
                            ){
                        exist = true;
                        qDebug() << "oki";

                    }
                }
            }
            if(exist == false){
                _arc = new arc(startItem, endItem);
                arcliste.append(_arc);
                startItem->ajouterArc(_arc);
                endItem->ajouterArc(_arc);
                addItem(_arc);
                _arc->adjust();
                _arc->updatePosition();
            }
            else{
                exist = false;
            }
        }
    }

    else if(_mode == supp){//mode supprimer
        foreach (sommet *som, sommetListe) {
            som->pMyProxy->hide();
            som->pMyProxy2->hide();

        }
        foreach (QGraphicsItem *item, this->selectedItems()) {
            if (item->type() == arc::Type) {

                removeItem(item);
                arc * _arc = qgraphicsitem_cast<arc *>(item);  // (item) why
                _arc->sourceSommet()->supprimerArc(_arc);
                _arc->destSommet()->supprimerArc(_arc);
                int index_arc = arcliste.indexOf(_arc);
                if (index_arc != -1)
                    arcliste.removeAt(index_arc);
                qDebug() << "supprimmer arc";
                delete _arc;                }
        }
        foreach (QGraphicsItem *item, this->selectedItems()) {
            if (item->type() == arete::Type) {

                removeItem(item);
                arete * _arete = qgraphicsitem_cast<arete *>(item);  // (item) why
                _arete->sourceSommet()->supprimerArete(_arete);
                _arete->destSommet()->supprimerArete(_arete);
                int index_arete = areteliste.indexOf(_arete);
                if (index_arete != -1)
                    areteliste.removeAt(index_arete);
                qDebug() << "supprimmer arete";
                delete _arete;
            }
        }
        foreach (QGraphicsItem *item, this->selectedItems()) {
            if (item->type() == sommet::Type){
                foreach(sommet *som , sommetListe){
                    if(som->isSelected()){
                        int index = sommetListe.indexOf(som);
                        if (index != -1)
                            sommetListe.removeAt(index);
                    }
                    else {
                        som->indexSommet = sommetListe.indexOf(som);
                    }
                }

                sommet * somm = qgraphicsitem_cast<sommet *>(item);
                foreach(arete *_arete ,somm->aretelist){
                    int index_arete = areteliste.indexOf(_arete);
                    if (index_arete != -1)
                        areteliste.removeAt(index_arete);
                }
                foreach(arc * _arc , somm->arclist){
                    int index_arc = arcliste.indexOf(_arc);
                    if (index_arc != -1)
                        arcliste.removeAt(index_arc);
                }
                somm->supprimerArcs();
                somm->supprimerAretes();
                this->removeItem(item);
                delete item;
            }
        }
    }
    if(!areteliste.empty()){
        foreach (arete *art, areteliste) {

            art->valArete = art->text->toPlainText().toDouble();

        }
    }
    if(!arcliste.empty()){
        foreach (arc *arx, arcliste) {

            arx->valarc = arx->text->toPlainText().toFloat();


        }
    }
    line = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void graphscene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if (mouseEvent->button() != Qt::LeftButton)//click != click_gauche
        return;
    if(_mode == ins && job == false){
        if(!sommetListe.empty()){
            foreach (sommet *som, sommetListe) {
                if (som->isSelected()){
                    som->pMyProxy->show();
                    som->valSommet = som->pLineEdit->text();
                }
                else{
                    som->pMyProxy->hide();
                }
            }
        }
    }
    else if(_mode == ins && job == true){
        if(!sommetListe.empty()){
            foreach (sommet *som, sommetListe) {
                if (som->isSelected()){
                    som->pMyProxy2->show();
                    som->valMachine = som->pLineEdit2->text();
                }
                else{
                    som->pMyProxy2->hide();
                }
            }
        }
    }
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}

bool graphscene::isItemChange(int type){//verifie si l'item estselectionner

    foreach (QGraphicsItem *item, selectedItems()) {
        if (item->type() == type){
            return true;
        }
    }

    return false;
}

void graphscene::fonctionAleatoire(){
    if(this->items().isEmpty()){
        int k,l,m,n;
        d=0;
        for(int j=0;j<a;j++){
            l = (rand() % 570)+10;
            k = (rand() % 1000)+10;
            _sommet = new sommet();
            _sommet->setPos(k,l);
            addItem(_sommet);
            sommetListe.append(_sommet);
            points.append(QPointF(k,l));

            _sommet->indexSommet = sommetListe.indexOf(_sommet);
            qDebug() << _sommet->indexSommet;
            _sommet->valSommet.append(QString("%1").arg(val));
            _sommet->pLineEdit = new QLineEdit(_sommet->valSommet);
            _sommet->pLineEdit->setObjectName("nameEdit");
            _sommet->pMyProxy = new QGraphicsProxyWidget(_sommet);
            _sommet->pLineEdit->setMaximumWidth(50);
            _sommet->pMyProxy->setWidget(_sommet->pLineEdit);
            _sommet->setSelected(true);
            _sommet->pMyProxy->hide();

            val++;
        }

        for(int j=0;j<b;j++){
            m = (rand() % a);
            n = (rand() % a);
            while(n==m){
                m = (rand() % a);
                n = (rand() % a);
            }

            _arete = new arete(sommetListe.at(m),sommetListe.at(n));
            sommetListe.at(m)->ajouterArete(_arete);
            sommetListe.at(n)->ajouterArete(_arete);
            addItem(_arete);
            _arete->adjust();

        }
        for(int j=0;j<c;j++){
            m = (rand() % a);
            n = (rand() % a);
            while(n==m){
                m = (rand() % a);
                n = (rand() % a);
            }

            _arc = new arc(sommetListe.at(m),sommetListe.at(n));
            sommetListe.at(m)->ajouterArc(_arc);
            sommetListe.at(n)->ajouterArc(_arc);
            addItem(_arc);
            _arc->adjust();

        }

    }

}

void graphscene::scene_struct(QString filename){

    int j = sommetListe.size();

    int **matrice_adjacence = new int*[j];
    for(int i = 0  ;i < j;i++){
        matrice_adjacence[i] = new int[j];
        for(int k = 0; k < j ; k++){
            matrice_adjacence[i][k] = 0;
        }
    }

    foreach(QGraphicsItem *item, items()){

        if (item->type() == arete::Type){
            arete *_arete = qgraphicsitem_cast<arete *>(item);
            matrice_adjacence[_arete->sourceSommet()->indexSommet][_arete->destSommet()->indexSommet] = _arete->valArete;
            matrice_adjacence[_arete->destSommet()->indexSommet][_arete->sourceSommet()->indexSommet] = _arete->valArete;
        }

        if (item->type() == arc::Type){
            arc *_arc = qgraphicsitem_cast<arc *>(item);
            matrice_adjacence[_arc->sourceSommet()->indexSommet][_arc->destSommet()->indexSommet] = _arc->valarc;
        }
    }


    QFile file( filename );
    if ( file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        QTextStream stream( &file );

        stream << sommetListe.size() << endl;

        foreach (sommet *pos, sommetListe) {
            stream << pos->x() << ";" << pos->y() << ";" << pos->valSommet << ";" <<endl;
        }

        for(int i = 0 ; i < j ; i++ ){
            for (int k = 0; k < j ; k++){
                stream << matrice_adjacence[i][k]<<" ";
            }
            stream << endl;
        }

        file.close();

    }else {
        qDebug() << "impossible d'ouvrir le fichier";
    }
}

void graphscene::scene_open(QString filename){

    bool deja = true;

    QFile file( filename );
    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {

        foreach(arc * _arc , arcliste){
            _arc->sourceSommet()->supprimerArc(_arc);
            _arc->destSommet()->supprimerArc(_arc);
            int index_arc = arcliste.indexOf(_arc);
            if (index_arc != -1)
                arcliste.removeAt(index_arc);
            removeItem(_arc);
            delete _arc;

        }

        foreach(arete * _arete , areteliste){
            _arete->sourceSommet()->supprimerArete(_arete);
            _arete->destSommet()->supprimerArete(_arete);
            int index_arete = areteliste.indexOf(_arete);
            if (index_arete != -1)
                areteliste.removeAt(index_arete);
            removeItem(_arete);
            delete _arete;

        }

        foreach(sommet * _sommet ,sommetListe ){
            _sommet->supprimerArcs();
            _sommet->supprimerAretes();
            int index_sommet = sommetListe.indexOf(_sommet);
            if (index_sommet != -1)
                sommetListe.removeAt(index_sommet);

            this->removeItem(_sommet);
            delete _sommet;
        }



        QString data;

        data = file.readLine();
        int r = data.toInt();
        val = r + 1;
        for(int i = 0 ; i < r; i++){

            data = file.readLine();

            QStringList list = data.split(';');

            qreal x = list.at(0).toDouble();
            qreal y = list.at(1).toDouble();
            QString valeur = list.at(2);

            sommet *som = new sommet();

            som->setPos(x,y);

            addItem(som);
            sommetListe.append(som);

            som->indexSommet = sommetListe.indexOf(som);
            qDebug() << som->indexSommet;
            som->valSommet=valeur;
            som->pLineEdit = new QLineEdit(som->valSommet);
            //sommet->pLineEdit->setObjectName("nameEdit");
            som->pMyProxy = new QGraphicsProxyWidget(som);
            som->pLineEdit->setMaximumWidth(50);
            som->pMyProxy->setWidget(som->pLineEdit);
            //sommet->setSelected(true);
            som->pMyProxy->hide();

        }
        for(int i = 0 ; i < r ;i++){

            data = file.readLine();

            QStringList list = data.split(" ");



            for(int K = 0;K < r ;K++){
                if(list.at(K).toDouble() != 0){

                    foreach(sommet *_sommet1, sommetListe){
                        if (_sommet1->indexSommet == i){
                            foreach(sommet *_sommet2, sommetListe){
                                if(_sommet2->indexSommet == K){
                                    foreach(arc *arx ,arcliste){
                                        if(arx->sourceSommet() == _sommet2 && arx->destSommet() == _sommet1 && arx->valarc == list.at(K).toDouble()){
                                            arx->sourceSommet()->supprimerArc(arx);
                                            arx->destSommet()->supprimerArc(arx);
                                            int index_arx = arcliste.indexOf(arx);
                                            if (index_arx != -1)
                                                arcliste.removeAt(index_arx);
                                            delete arx;
                                            deja = false;

                                        }}
                                    if(deja == false){

                                        arete *_arete = new arete(_sommet1,_sommet2);
                                        areteliste.append(_arete);
                                        _sommet1->ajouterArete(_arete);
                                        qDebug() << "ajoute arete start";
                                        _sommet2->ajouterArete(_arete);
                                        qDebug() <<"ajouter arete dest";
                                        _arete->valArete = list.at(K).toDouble();
                                        _arete->text->setPlainText(QString::number(_arete->valArete));
                                        addItem(_arete);
                                        _arete->adjust();
                                    }


                                    else {
                                        arc *_arc =new arc(_sommet1,_sommet2);
                                        arcliste.append(_arc);
                                        _arc->valarc = list.at(K).toDouble();
                                        _arc->text->setPlainText(QString::number(_arc->valarc));
                                        _sommet1->ajouterArc(_arc);
                                        qDebug() << "ajout1";
                                        _sommet2->ajouterArc(_arc);
                                        qDebug() << "ajout2";
                                        addItem(_arc);
                                        qDebug() <<"il est ajouté";
                                        _arc->adjust();
                                    }
                                    deja = true;

                                }
                            }//
                        }

                    }
                }
            }
        }

        file.close();

    } else {
        qDebug() << "impossible d'ouvrir le fichier";
    }


}

bool graphscene::cycle(QList<sommet *> Liste){
    foreach(sommet *som , Liste){
        som->degre = 0;
    }

    foreach(sommet * som , Liste){
        foreach(arc * ac , som->arclist2)
        {
            if(ac->sourceSommet() == som){
                ac->destSommet()->degre++;
            }
        }
    }
    QList<sommet *> a_traiter;
    int nmbr = 0;
    foreach(sommet * som,Liste){
        if(som->degre == 0){
            a_traiter.append(som);
            nmbr++;
        }
    }
    while(!a_traiter.isEmpty()){
        sommet *sommet = a_traiter.first();
        a_traiter.removeAt(0);
        foreach(arc * ac , sommet->arclist2){
            if(ac->sourceSommet() == sommet ){
                ac->destSommet()->degre--;
                if(ac->destSommet()->degre == 0){
                    a_traiter.append(ac->destSommet());
                    nmbr++;
                }
            }
        }

    }

    if (nmbr == Liste.length()){
        //qDebug() << "sans cycle";
        return false;
    }
    else{
        //qDebug() << "cycle";
        return true;
    }
}

void graphscene::algopert(QList<sommet *> maliste){
        foreach(sommet *som, maliste){
            som->date_plutot = 0;
        }
        foreach(sommet * som,maliste){
            foreach(arc * ac,som->arclist){
                if(som == ac->destSommet()){
                   int date = ac->valarc + ac->sourceSommet()->date_plutot;
                   if(date > som->date_plutot)
                       som->date_plutot = date;
                       som->date_plutard = date;
                }
            }
        }
        foreach (sommet *som, maliste) {
            foreach(arc * ac,som->arclist){
                if(som == ac->sourceSommet()){
                   int date =   ac->destSommet()->date_plutot - ac->valarc;
                   if(date < som->date_plutard)
                       som->date_plutard = date;
                }

            }
            QList<sommet *> chemincritique;
            cmax=0;
            //int cmin =0;
            chemincritique.append(maliste.at(0));
            foreach (sommet * som, maliste) {
                if(som->date_plutard == som->date_plutot)
                    foreach(arc * ac,arcliste){
                        if(ac->destSommet()==som && ac->sourceSommet()->date_plutot < som->date_plutot){
                            chemincritique.append(som);
                             cmax = som->date_plutot;
                             //cmin = som->date_plutard;
                        }

                    }

            }
        }
        fitness.append(cmax);
        qDebug() << cmax;
}

void graphscene::generationInitial(){
    //nombre de machines

    if(!sommetListe.isEmpty()){

        foreach(sommet *som ,sommetListe){
            if(som->valMachine.toInt() > nb_mach){
                nb_mach = som->valMachine.toInt();
            }
        }


        int i = 1;
        // la premiere proposition de solution
        while(i != nb_mach + 1 ){
            foreach(sommet *som , sommetListe){
                if(som->valMachine.toInt() == i){
                    sommetParcourt.append(som);
                }
            }
            tab.append(sommetParcourt.length());
            i++;
        }

        if(!arcliste2.isEmpty()){
            arcliste2.clear();
        }

        // ajouter les arcs
        int n = 0;
        int j = 0;
        int k = tab.at(n) - 1;
        while(n != nb_mach){

            for(int i = j ; i < k ;i++){
                _arc = new arc(sommetParcourt.at(i), sommetParcourt.at(i+1));
                arcliste2.append(_arc);
            }

            j = tab.at(n);
            n++;
            if(n < tab.length())
                k = tab.at(n) - 1;
        }

        foreach(arc * ac , arcliste){
            ac->destSommet()->arclist2.append(ac);
            ac->sourceSommet()->arclist2.append(ac);
        }
        foreach(arc * ac , arcliste2){
            ac->destSommet()->arclist2.append(ac);
            ac->sourceSommet()->arclist2.append(ac);
        }
        //test de solution
        int nmbre_population = 0;
        int a =0;

        while (nmbre_population != 20) {
            //Si valide on ajoute a la population
            //qDebug() << a++;
            if(!cycle(sommetParcourt) && population.contains(sommetParcourt) == false){
                qDebug() << sommetParcourt.length();
                algopert(sommetParcourt);
                population.append(sommetParcourt);
                nmbre_population++;
            }
            //sinon on cherchre un autre

            foreach(arc *ac, arcliste2){
                int indice_ac1 = ac->destSommet()->arclist2.indexOf(ac);
                ac->destSommet()->arclist2.removeAt(indice_ac1);
                int indice_ac2 = ac->sourceSommet()->arclist2.indexOf(ac);
                ac->sourceSommet()->arclist2.removeAt(indice_ac2);
                arcliste2.removeAt(arcliste2.indexOf(ac));
                delete ac;
            }



            if( nmbre_population != 20)  // stoper creation des individus et des arcs
            {

                int m3 = 0;
                int j3 = 0;
                int k3 = tab.at(m3) - 1;

                while(m3 != nb_mach){

                    int rand1 = qrand() % (k3 + 1 - j3) + j3 ;
                    int rand2 = qrand() % (k3 + 1 - j3) + j3 ;
                    while(rand2 == rand1){
                        rand1 = qrand() % (k3 + 1 - j3) + j3 ;
                        rand2 = qrand() % (k3 + 1 - j3) + j3 ;
                    }

                    //PErmutation de deux valeurs
                    sommetParcourt.swap(rand1,rand2);

                    j3 = tab.at(m3);
                    m3++;
                    if(m3 < tab.length())
                        k3 = tab.at(m3) - 1;
                }

                // ajouter a nouveau les arcs
                int n2 = 0;
                int j2 = 0;
                int k2 = tab.at(n2) - 1;
                while(n2 != nb_mach){


                    for(int i = j2 ; i < k2 ;i++){
                        _arc = new arc(sommetParcourt.at(i), sommetParcourt.at(i+1));
                        arcliste2.append(_arc);
                    }

                    j2 = tab.at(n2);
                    n2++;
                    if(n2 < tab.length())
                        k2 = tab.at(n2) - 1;
                }

                foreach(arc * ac , arcliste){
                    ac->destSommet()->arclist2.append(ac);
                    ac->sourceSommet()->arclist2.append(ac);
                }
                foreach(arc * ac , arcliste2){
                    ac->destSommet()->arclist2.append(ac);
                    ac->sourceSommet()->arclist2.append(ac);
                }
            }
        }
    }
}
