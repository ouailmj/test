#include <QApplication>
#include <QWidget>
#include "fenetreprincipale.h"
#include "graphscene.h"
int main(int argc, char *argv[]){
    QApplication app(argc,argv);
    fenetrePrincipale fenetre;
    fenetre.show();
    return app.exec();
}
