#include "meinWidget.h"
// Qt5 add:
#include <QApplication>

int main(int argc, char *argv[])
{
    // initial setzen für zufallsgenerator
    srand(time(NULL));
    QApplication a(argc, argv);
    meinWidget w;
    w.setGeometry(0, 0, 500, 355);
    w.show();

    return a.exec();
}
