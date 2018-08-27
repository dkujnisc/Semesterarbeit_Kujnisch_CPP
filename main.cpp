#include "meinWidget.h"
// Qt5 add:
#include <QApplication>


int main(int argc, char *argv[])
{
    srand(time(NULL));
    //fallendesObjekt *ukulele=new fallendesObjekt(1,2);
    QApplication a(argc, argv);
    meinWidget w;
    w.setGeometry(0, 0, 500, 355);
    w.show();

    return a.exec();
}
