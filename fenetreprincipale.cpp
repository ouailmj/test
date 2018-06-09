#include "fenetreprincipale.h"
#include "arete.h"
fenetrePrincipale::fenetrePrincipale(){
    afficheMenu();//affiche le menubar
    affichetoolTop();//affiche le toolbar
    afficheWidgetPrincipale();//affiche widget Principale
    affichetoolbox();//ajout de toolbox
    ajoutVue();
    ajoutValeur();
    this->setMinimumHeight(550);
    vue->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);
    vue->setDragMode(QGraphicsView::RubberBandDrag);
}

void fenetrePrincipale::afficheMenu(){
    fichier = menuBar()->addMenu("&Fichier");
//*************************************************
            nouveau = new QAction("&Nouveau fichier",this);
            nouveau->setShortcut(QKeySequence("Ctrl+B"));
            //signal_nouvelle_page
                connect(nouveau, SIGNAL(triggered()), this, SLOT(nouvelPage()));
                QPixmap imagedisplaynouveau(":/img/img/nouveau.png");
                QIcon icon_nouveau(imagedisplaynouveau);
                nouveau->setIcon(icon_nouveau);
            fichier ->addAction(nouveau);
//**************************************************
            ouvrir = new QAction("&Ouvrir un dossier",this);
            ouvrir->setShortcut(QKeySequence("Ctrl+O"));
                QPixmap imagedisplayouvrir(":/img/img/ouvrir.png");
                QIcon iconouvrir(imagedisplayouvrir);
                ouvrir->setIcon(iconouvrir);
                connect (ouvrir, SIGNAL (triggered()), this , SLOT (ouvrirSlot()));
            fichier ->addAction(ouvrir);
//**************************************************
            enregistrer = new QAction("&Enregistrer fichier",this);
            enregistrer->setShortcut(QKeySequence("Ctrl+S"));
                //signal_enregistrer
                connect(enregistrer, SIGNAL(triggered()), this, SLOT(enregistrerSlot()));
                QPixmap imagedisplayenregistrer(":/img/img/enregistre.png");
                QIcon iconenregistrer(imagedisplayenregistrer);
                enregistrer->setIcon(iconenregistrer);
            fichier ->addAction(enregistrer);
//**************************************************
            quitter = new QAction("&Quitter",this);
            quitter->setShortcut(QKeySequence("Ctrl+Q"));
                QPixmap imagedisplayquitter(":/img/img/quitter.png");
                QIcon iconquitter(imagedisplayquitter);
                quitter->setIcon(iconquitter);
                //signal_quitter
                connect(quitter, SIGNAL(triggered()), qApp, SLOT(quit()));
            fichier ->addAction(quitter);
//*****************************************************
//*****************************************************
        edition = menuBar()->addMenu("&Edition");
            revenir = new QAction("&Revenir en arriere",this);
            revenir->setShortcut(QKeySequence("Ctrl+Z"));
                QPixmap imagedisplayrevenir(":/img/img/back.png");
                QIcon iconrevenir(imagedisplayrevenir);
                revenir->setIcon(iconrevenir);
            edition ->addAction(revenir);
//*********************************************************
//*********************************************************
        affichage = menuBar()->addMenu("&Affichage");
//*********************************************************
//*********************************************************
        aide = menuBar()->addMenu("A&ide");
            visiter = new QAction("&besoin d'aide",this);
            visiter->setShortcut(QKeySequence("Ctrl+V"));
                QPixmap imagedisplayvisiter(":/img/img/help.png");
                QIcon iconvisiter(imagedisplayvisiter);
                visiter->setIcon(iconvisiter);
            aide ->addAction(visiter);
//*********************************************************
//*********************************************************
    propos = menuBar()->addMenu("A &propos");
        Apropos = new QAction("&A propos",this);
        Apropos->setShortcut(QKeySequence("Ctrl+P"));
            QPixmap imagedisplaypropos(":/img/img/help.png");
            QIcon iconpropos(imagedisplaypropos);
            Apropos->setIcon(iconpropos);
            propos->addAction(Apropos);
        //signal_apropos
        connect(Apropos, SIGNAL(triggered()), this, SLOT(explication()));
}

void fenetrePrincipale::nouvelPage(){
    fenetrePrincipale *nouvelFenetre = new fenetrePrincipale();//class fenetrePrincipale
    nouvelFenetre->show();
}

void fenetrePrincipale::explication(){
    fenetrePropos *Prs = new fenetrePropos;//class fenetrePropos deja definie
}

void fenetrePrincipale::affichetoolTop(){
        newAct = new QAction(QIcon(":/img/img/nouveau.png"), "&Nouveau", this);
        newAct->setShortcuts(QKeySequence::New);
        connect(newAct,SIGNAL(triggered()),this,SLOT(nouvelPage()));

        openAct = new QAction(QIcon(":/img/img/ouvrir.png" ), "&Ouvrir", this);
        openAct->setShortcuts(QKeySequence::Open);
        connect(openAct,SIGNAL(triggered()),this,SLOT(ouvrirSlot()));

        saveAct = new QAction(QIcon(":/img/img/enregistre.png" ), "&Enregistrer", this);
        saveAct->setShortcuts(QKeySequence::Save);
        connect(saveAct,SIGNAL(triggered()),this,SLOT(enregistrerSlot()));

        deleteAct = new QAction(QIcon(":/img/img/supp.ico" ), "&Supprimer", this);
        deleteAct->setShortcuts(QKeySequence::Delete);
        connect(deleteAct,SIGNAL(triggered()),this,SLOT(suppSlot()));

        copyAct = new QAction(QIcon(":/img/img/couper.png"), "&Couper", this);
        copyAct->setShortcuts(QKeySequence::Cut);
        connect(copyAct,SIGNAL(triggered()),this,SLOT(selectSlot()));

        backAct = new QAction(QIcon(":/img/img/back2.png" ), "&Back", this);

        forwardAct = new QAction(QIcon(":/img/img/forward.png" ), "&Forward", this);

        startAct = new QAction(QIcon(":/img/img/play.png" ), "&Debug", this);
        connect(startAct,SIGNAL(triggered()),this,SLOT(debugSlot()));

        pauseAct = new QAction(QIcon(":/img/img/pause.png" ), "&Pause", this);

        stopAct = new QAction(QIcon(":/img/img/stop.png" ), "&Stop", this);

        infoAct = new QAction(QIcon(":/img/img/info.png" ), "&Info", this);
        connect(infoAct,SIGNAL(triggered()),this,SLOT(explication()));

        helpAct = new QAction(QIcon(":/img/img/help.png" ), "&Help", this);

        initialAct = new QAction(QIcon(":/img/img/green.png"),"&Sommet initial" , this);
        connect(initialAct,SIGNAL(triggered()),this,SLOT(initialSlot()));

        finalAct = new QAction(QIcon(":/img/img/red.png"),"&Sommet final" , this);
        connect(finalAct,SIGNAL(triggered()),this,SLOT(finalSlot()));

        sceneScale = new QComboBox;//pour pouvoir agrandir la scene
        QStringList scales;
        scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
        sceneScale->addItems(scales);
        sceneScale->setCurrentIndex(2);
        connect(sceneScale, SIGNAL(currentIndexChanged(QString)),
                this, SLOT(sceneScaleslot(QString)));

        //ajout de toolbar et de ces elements...
        fileToolBar = this->addToolBar("Fichier");
        fileToolBar->addAction(newAct);
        fileToolBar->addSeparator();//separateur
        fileToolBar->addAction(openAct);
        fileToolBar->addSeparator();
        fileToolBar->addAction(saveAct);

        debugToolBar = this->addToolBar("Debug");
        debugToolBar->addAction(startAct);
        debugToolBar->addSeparator();
        debugToolBar->addAction(pauseAct);
        debugToolBar->addSeparator();
        debugToolBar->addAction(stopAct);

        editToolBar = this->addToolBar("Edition" );
        editToolBar->addAction(backAct);
        editToolBar->addSeparator();
        editToolBar->addAction(forwardAct);
        editToolBar->addSeparator();
        editToolBar->addAction(initialAct);
        editToolBar->addSeparator();
        editToolBar->addAction(finalAct);
        editToolBar->addSeparator();
        editToolBar->addAction(deleteAct);
        editToolBar->addSeparator();
        editToolBar->addAction(copyAct);
        editToolBar->addSeparator();
        editToolBar->addWidget(sceneScale);
        sceneScale->setFixedHeight(25);

        searchToolBar = this->addToolBar("recherche");
        formulaireSearch->addRow("recherche :" , searchBar);
        widgetSearch->setLayout(formulaireSearch);
        searchToolBar->addWidget(widgetSearch);
        searchBar->setFixedWidth(250);

        infos = this->addToolBar("information");
        infos->addAction(infoAct);
        infos->addSeparator();
        infos->addAction(helpAct);

}

void fenetrePrincipale::sceneScaleslot(const QString &scale){
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldscale = vue->matrix();
    vue->resetMatrix();
    vue->translate(oldscale.dx(), oldscale.dy());
    vue->scale(newScale, newScale);
}

void fenetrePrincipale::initialSlot(){
    sene->setModechoisi(graphscene::insererDebut);
}

void fenetrePrincipale::finalSlot(){
    sene->setModechoisi(graphscene::insererFin);
}

void fenetrePrincipale::debugSlot(){
    sene->generationInitial();
}

void fenetrePrincipale::afficheWidgetPrincipale(){
    centre->setLayout(Hlayout);
    setCentralWidget(centre);
}

void fenetrePrincipale::affichetoolbox(){
    ajoutboutonBox();//ajout des bouttons dans la toolbox
    ajoutModeAleatoire();
    toolbox1->setLayout(vlayout);
    box1->addItem(toolbox1,"ToolBox1");
    box1->addItem(aleatoirebox,"toolbox2");
    box1->setFixedWidth(80);
    Hlayout->addWidget(box1);
}

void fenetrePrincipale::ajoutboutonBox(){
    b_sommet->setIconSize(QSize(20,20));
    b_sommet->setGeometry(70,10,100,160);
    b_sommet->setFocusPolicy(Qt::TabFocus);
    QString ImagePath1;
    ImagePath1 = ":/img/img/point.png";
    QPixmap imagedisplay1(ImagePath1);
    QIcon icon1(imagedisplay1);
    b_sommet->setIcon(icon1);
    QMenuBar *barre_sommet = new QMenuBar; // On crée notre QMenuBar
        QMenu *menusommet = barre_sommet->addMenu("&Sommet");
        QAction *actionsommet = menusommet->addAction("sommet");
        QAction *actionjob = menusommet->addAction("job");
        b_sommet->setMenu(menusommet);
    connect(actionsommet, SIGNAL(triggered()), this, SLOT(sommetSlot()));
    connect(actionjob, SIGNAL(triggered()), this, SLOT(jobSlot()));
vlayout->addWidget(b_sommet);


    b_arete->setIconSize(QSize(20,20));
    b_arete->setGeometry(70,10,100,160);
    b_arete->setFocusPolicy(Qt::TabFocus);
    QString ImagePath2;
    ImagePath2 = ":/img/img/ligne.png";
    QPixmap imagedisplay2(ImagePath2);
    QIcon icon2(imagedisplay2);
    b_arete->setIcon(icon2);
    connect(b_arete, SIGNAL(clicked()), this, SLOT(areteSlot()));
vlayout->addWidget(b_arete);


    b_arc->setIconSize(QSize(20,20));
    b_arc->setGeometry(70,10,100,160);
    b_arc->setFocusPolicy(Qt::TabFocus);
    QString ImagePath3;
    ImagePath3 = ":/img/img/arc.png";
    QPixmap imagedisplay3(ImagePath3);
    QIcon icon3(imagedisplay3);
    b_arc->setIcon(icon3);
    connect(b_arc, SIGNAL(clicked()), this, SLOT(arcSlot()));
vlayout->addWidget(b_arc);


    b_supprimer->setIconSize(QSize(20,20));
    b_supprimer->setGeometry(70,10,100,160);
    b_supprimer->setFocusPolicy(Qt::TabFocus);
    QString ImagePath;
    ImagePath = ":/img/img/supp.ico";
    QPixmap imagedisplay(ImagePath);
    QIcon icon(imagedisplay);
    connect(b_supprimer, SIGNAL(clicked()), this, SLOT(suppSlot()));
    b_supprimer->setIcon(icon);
vlayout->addWidget(b_supprimer);


    b_select->setIconSize(QSize(20,20));
    b_select->setGeometry(70,10,100,160);
    b_select->setFocusPolicy(Qt::TabFocus);
    QString ImagePath4;
    ImagePath4 = ":/img/img/click.png";
    QPixmap imagedisplay4(ImagePath4);
    QIcon icon4(imagedisplay4);
    connect(b_select, SIGNAL(clicked()), this, SLOT(selectSlot()));
    b_select->setIcon(icon4);
vlayout->addWidget(b_select);
vlayout->addStretch(0);//pour organiser le vlayout
}

void fenetrePrincipale::sommetSlot(){
    sene->job = false;
    foreach (sommet *som, sene->sommetListe) {
        som->pLineEdit2->hide();
    }
    sene->setModechoisi(graphscene::insererSommet);
    //sene->cycle();
}

void fenetrePrincipale::jobSlot(){
    sene->job = true;
    foreach (sommet *som, sene->sommetListe) {
        som->pLineEdit->hide();
    }
    sene->setModechoisi(graphscene::insererSommet);
}

void fenetrePrincipale::areteSlot(){
    vue->setDragMode(QGraphicsView::NoDrag);
    sene->setModechoisi(graphscene::insererArete);
}

void fenetrePrincipale::arcSlot(){
    vue->setDragMode(QGraphicsView::NoDrag);
    sene->setModechoisi(graphscene::insererArc);
}

void fenetrePrincipale::selectSlot(){
    sene->setModechoisi(graphscene::ins);
    vue->setDragMode(QGraphicsView::RubberBandDrag);
}

void fenetrePrincipale::suppSlot(){
    sene->setModechoisi(graphscene::supp);
    vue->setDragMode(QGraphicsView::RubberBandDrag);
    sene->setModechoisi(graphscene::supp);
}

void fenetrePrincipale::ajoutModeAleatoire(){
    spinaleatoireSommet->setRange(0, 100);
    spinaleatoireSommet->setSingleStep(1);
    spinaleatoireSommet->setValue(0);
    spinaleatoireSommet->setFixedWidth(60);
    spinaleatoireArete->setRange(0, 100);
    spinaleatoireArete->setSingleStep(1);
    spinaleatoireArete->setValue(0);
    spinaleatoireArete->setFixedWidth(60);
    spinaleatoireArc->setRange(0, 100);
    spinaleatoireArc->setSingleStep(1);
    spinaleatoireArc->setValue(0);
    spinaleatoireArc->setFixedWidth(60);
    vgroup->addWidget(text_sommet);
    vgroup->addWidget(spinaleatoireSommet);
    vgroup->addWidget(text_arete);
    vgroup->addWidget(spinaleatoireArete);
    vgroup->addWidget(text_arc);
    vgroup->addWidget(spinaleatoireArc);
    b_aleatoire->setFixedWidth(60);
    connect(b_aleatoire, SIGNAL(clicked()), this, SLOT(aleatoireSlot()));
    vgroup->addWidget(b_aleatoire);
    vgroup->addStretch(0);
    aleatoirebox->setLayout(vgroup);
}

void fenetrePrincipale::aleatoireSlot(){
    sene->a = spinaleatoireSommet->value();
    sene->b = spinaleatoireArete->value();
    sene->c = spinaleatoireArc->value();
    sene->fonctionAleatoire();
}

void fenetrePrincipale::ajoutVue(){
    sene->setSceneRect(QRect(100,40,800,450));
    vue->setScene(sene);
    connect(sene, SIGNAL(itemSelected(QGraphicsItem*)),
            this, SLOT(itemSelected(QGraphicsItem*)));
    vue->setMouseTracking(true);
    vue->setMinimumWidth(730);
    Hlayout->addWidget(vue);
}

void fenetrePrincipale::ajoutValeur(){
    valeur->setReadOnly(true);
    valeurlayout->addRow("Valeur:", valeur);
    b_algorithme->setFocusPolicy(Qt::TabFocus);
    QMenuBar *barre_algorithme = new QMenuBar; // On crée notre QMenuBar
        QMenu *menualgo = barre_algorithme->addMenu("&Sommet");
        QAction *actionalgo1 = menualgo->addAction("algo1");
        QAction *actionalgo2 = menualgo->addAction("algo2");
        QAction *actionalgo3 = menualgo->addAction("algo3");
        b_algorithme->setMenu(menualgo);
    valeurlayout->addRow(b_algorithme);
    valeurlayout->addRow("job :" , editJob);
    valeurlayout->addRow("machines : " , machine);
    valeurlayout->addRow(b_job);
    connect(b_job,SIGNAL(clicked()),this,SLOT(CreerJob()));
    valeurbox->setMaximumWidth(200);
    valeurbox->setLayout(valeurlayout);
    Hlayout->addWidget(valeurbox);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
              this, SLOT(MyTimerSlot()));
    timer->start(10);
}

void fenetrePrincipale::MyTimerSlot(){
    if(sene->job == false){
        foreach (sommet *som, sene->sommetListe) {
            if(som->isSelected()){
                valeur->setText(som->valSommet);
            }
        }
        machine->setText("------------");
        editJob->setText("------------");
    }
    else if(sene->job == true){
        foreach(sommet *som,sene->sommetListe){
            if(som->isSelected()){
                machine->setText(som->valMachine);
                QString s = QString::number(som->sommetJob);
                editJob->setText(s);
            }
        }
        valeur->setText("------------");
    }
}

void fenetrePrincipale::CreerJob(){
    sene->creerjob = true;
    sene->valJob = ii;
    ii++;
    sene->setModechoisi(graphscene::insererJob);
}

void  fenetrePrincipale::enregistrerSlot(){

    QString filename = QFileDialog::getSaveFileName(this, "Save as", QDir::home().absolutePath(), "Graph file (*.grp)");

        qDebug() << filename;

        sene->scene_struct(filename);
}

void  fenetrePrincipale :: ouvrirSlot () {
    QString filename = QFileDialog::getOpenFileName(this, "open", QDir::home().absolutePath(), "Graph file (*.grp)");

        qDebug() << filename;

        sene->scene_open(filename);

}
