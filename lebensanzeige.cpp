#include <QtGui>
#include "lebensAnzeige.h"

lebensAnzeige::lebensAnzeige(QWidget *parent)
    : QWidget(parent)
{
    setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);
    setMouseTracking(false);
}

lebensAnzeige::~lebensAnzeige()
{
}

void lebensAnzeige::paintEvent(QPaintEvent * )
{
    QPainter painter;
    // lebensanzeige

    painter.begin( this );
    painter.drawEllipse(0,15,10,10);
    painter.drawEllipse(15,15,10,10);
    painter.drawEllipse(30,15,10,10);
    painter.end();
}
