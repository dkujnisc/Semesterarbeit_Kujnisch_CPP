#include "meinWidget.h"
// Qt5 add:
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    meinWidget w;
    w.setGeometry(100, 100, 500, 355);
    w.show();

    return a.exec();
}
