#include <QtGui>
#include "zeichenFeld.h"

zeichenFeld::zeichenFeld(QWidget *parent)
    : QWidget(parent)
{
    setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);
    setMouseTracking(false);

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    lastX=100;
    lastY=100;
    increment=0;
    phase=0;
}

zeichenFeld::~zeichenFeld()
{
}

void zeichenFeld::paintEvent(QPaintEvent * )
{
    QPainter painter;
    int x,y,width,height;

    painter.begin( this );
    //linke obere Ecke: Breite == Hoehe == 50

    for (int i=0; i<kreise; i++)
    {
        x=lastX-25;
        y=lastY-25;

        painter.drawEllipse(x+(i*10),y+(i*10),50,50);
    }

    if (increment)
        switch(phase)
        {
        case 0:
            if (lastX<300) lastX++;
            else phase=1;
            break;
        case 1:
            if (lastY<300) lastY++;
            else phase=2;
            break;
        case 2:
            if (lastX>100) lastX--;
            else phase=3;
            break;
        case 3:
            if (lastY>100) lastY--;
            else phase=0;
            break;
        }

    painter.end();
}
