#include <QtGui>
#include "zeichenFeld.h"
#include <fallendesobjekt.h>

zeichenFeld::zeichenFeld(QWidget *parent)
    : QWidget(parent)
{
    setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);
    setMouseTracking(false);

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    increment=0;
}

zeichenFeld::~zeichenFeld()
{
}

void zeichenFeld::paintEvent(QPaintEvent * )
{
    QPainter painter;
    // lebensanzeige
    painter.begin( this );
    //linke obere Ecke: Breite == Hoehe == 50
    // quelle: https://forum.qt.io/topic/23701/solved-how-to-generate-random-number-between-two-numbers-qt/6

    int High=10;
    int Low=5;
    painter.drawText(rect(), Qt::AlignCenter, QString::number(qrand() % ((High + 1) - Low) + Low));
    this->width();
    painter.setBrush(Qt::red);
    if (0==anzahlLeben) {
        painter.setBrush(Qt::black);
    }
    painter.drawEllipse(this->width()-15,15,10,10);
    if (1==anzahlLeben) {
        painter.setBrush(Qt::black);
    }
    painter.drawEllipse(this->width()-30,15,10,10);
    if (2==anzahlLeben) {
        painter.setBrush(Qt::black);
    }
    painter.drawEllipse(this->width()-45,15,10,10);
    painter.setBrush(Qt::black);
    for(unsigned i = 0; i <= (sizeof(fallendesObjekt)/sizeof(listeFallenderObjekte)); i++)
    {
        painter.drawEllipse(listeFallenderObjekte[i].lastX,listeFallenderObjekte[i].lastY,50,50);
    }
    if (increment) {

    }
    painter.end();
}
