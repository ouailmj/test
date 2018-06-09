#include "fenetrepropos.h"
fenetrePropos::fenetrePropos(){
     txt->setText("textxstttsxtstt");
     txt->append("Appending some text…");
     txt->setReadOnly(true);
     layout->addWidget(txt);
     wid->setLayout(layout);
     this->setCentralWidget(wid);
     this->show();
     this->setFixedSize(500,500);
}
