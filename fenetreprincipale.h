#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QToolBox>
#include <QComboBox>
#include <QGroupBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QList>
#include <QLabel>
#include <QSpinBox>
#include <QPoint>
#include <stdlib.h>
#include <QRadioButton>
#include <QTimer>
#include <QFileDialog>
#include "fenetrepropos.h"
#include "graphscene.h"
#include "sommet.h"
#include "arete.h"
class fenetrePrincipale : public QMainWindow{
    Q_OBJECT
public :
    //constructeur de la fenetre Principale
    fenetrePrincipale();
    void afficheMenu();//affiche le menubar
    void affichetoolTop();//affiche le toolbar
    void afficheWidgetPrincipale();//widget Principale centrale
    void affichetoolbox();//ajout de toolbox
    void ajoutboutonBox();//ajout des bouttons dans la toolbox
    void ajoutVue();//ajout de view et definition de scene
    void ajoutModeAleatoire();
    void ajoutValeur();
    int ii=1;
//initialisation_variable_mode_aleatoire
protected:
//*********debut_menubar
    //*****************menu
    QMenu *fichier;
    QMenu *edition;
    QMenu *affichage;
    QMenu *aide;
    QMenu *propos;
    //******************sous_menu_fichier
    QAction *nouveau;
    QAction *ouvrir;
    QAction *enregistrer;
    QAction *quitter;
    //******************sous_menu_edition
    QAction *revenir;
    //******************sous_menu_aide
    QAction *visiter;
    //******************fenetre_A_propos
    QAction *Apropos;
//**********fin_menubar

//debut_toolbar
    QAction* newAct;
    QAction* openAct;
    QAction* saveAct;
    QAction* startAct;
    QAction* pauseAct;
    QAction* stopAct;
    QAction* backAct;
    QAction* forwardAct;
    QAction* deleteAct;
    QAction* copyAct;
    QComboBox* sceneScale;
    QAction* initialAct;
    QAction* finalAct;
    QLineEdit* searchBar = new QLineEdit;
    QFormLayout *formulaireSearch = new QFormLayout;
    QWidget *widgetSearch = new QWidget;
    QAction* infoAct;
    QAction* helpAct;
    QToolBar* fileToolBar;
    QToolBar* editToolBar;
    QToolBar* debugToolBar;
    QToolBar* searchToolBar;
    QToolBar* infos;
//fin_toolbar
//*********************************************************
//*********************************************************
//**********************************************************
//************************************************************
//initialisation_du_widget_principale
      QWidget *centre = new QWidget;
//Debut_toolbox
    QToolBox *box1 = new QToolBox();
    QWidget *toolbox1 = new QWidget;
    //************Creation_de_bouttons
    QPushButton *b_sommet = new QPushButton();
    QPushButton *b_arete = new QPushButton();
    QPushButton *b_arc = new QPushButton();
    QPushButton *b_supprimer = new QPushButton();
    QPushButton *b_select = new QPushButton();
//Fin_toolbox
//****************************************
//****************************************
    //************Creation_de_layout
    QVBoxLayout *vlayout = new QVBoxLayout;
    QHBoxLayout *Hlayout = new QHBoxLayout;
    QVBoxLayout *vboxlayout = new QVBoxLayout;
//ajout_de_vue
    graphscene *sene = new graphscene();
    QGraphicsView *vue = new QGraphicsView(sene);
//mode_aleatoire*******************
    QGroupBox *aleatoirebox = new QGroupBox(tr("Aleatoire"));
    QLabel *text_sommet = new QLabel(tr("sommet:"));
    QSpinBox *spinaleatoireSommet = new QSpinBox;
    QLabel *text_arete = new QLabel(tr("arete:"));
    QSpinBox *spinaleatoireArete = new QSpinBox;
    QLabel *text_arc = new QLabel(tr("arc:"));
    QSpinBox *spinaleatoireArc = new QSpinBox;
    QPushButton *b_aleatoire = new QPushButton("GO!");
//initialisation_de_layout_mode_aleatoire
    QVBoxLayout *vgroup = new QVBoxLayout;
//initialisation_de_layout_valeur_sommet_arete
    QFormLayout *valeurlayout = new QFormLayout;
//QGroupBox_valeur*****************************
    QGroupBox *valeurbox = new QGroupBox(tr("Valeur :"));
    QLineEdit *valeur = new QLineEdit;
    QLineEdit *machine = new QLineEdit;
    QLineEdit *editJob = new QLineEdit;
    QPushButton *b_algorithme = new QPushButton("algorithmes");
    QString mavaleur;
    QPushButton *b_job = new QPushButton("Creer job");
//initialisation_de_Qtimer
    QTimer *timer;
public slots:
    void nouvelPage();//pour ouvrir une nouvelle page
    void explication();//slot à propos
    void sommetSlot();//slot b_sommet
    void jobSlot();
    void areteSlot();
    void arcSlot();
    void selectSlot();
    void debugSlot();
    void sceneScaleslot(const QString &scale);
    void suppSlot();
    void aleatoireSlot();
    void MyTimerSlot();
    void CreerJob();
    void enregistrerSlot();
    void ouvrirSlot();
    void initialSlot();
    void finalSlot();
};

#endif // FENETREPRINCIPALE_H
