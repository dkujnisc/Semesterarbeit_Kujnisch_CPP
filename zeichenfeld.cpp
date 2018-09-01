#include <QtGui>
#include <QMessageBox>
#include "zeichenFeld.h"
#include <fallendesobjekt.h>
#include <iostream>

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

    // avatar
    positionAvatarY=height()-10;
    painter.drawRect(positionAvatarX, positionAvatarY, 50, 50);

    // fallende objekte
    for(unsigned i = 0; i <= (sizeof(fallendesObjekt)/sizeof(listeFallenderObjekte)); i++)
    {
        painter.drawEllipse(listeFallenderObjekte[i].lastX,listeFallenderObjekte[i].lastY,50,50);
    }
    if (increment) {

    }
    painter.end();
}

// anlegen der methode serialize
void zeichenFeld::serialize(QFile &file)
{
    // format der datei
    // leben
    // punkte
    // position avatar
    // position fallendesObjekt
    // fallende objekte...

    // beispiel dateiinhalt
    // 2
    // 5311
    // 10;100
    // 300;200
    // 253;192
    // 112;270
    // aus dem programm in eine datei
    QTextStream out(&file);

    out << anzahlLeben << endl;
    out << punkte << endl;
    out << positionAvatarX << endl;
    out << positionAvatarY << endl;
    for(unsigned i = 0; i <= (sizeof(fallendesObjekt)/sizeof(listeFallenderObjekte)); i++)
    {
        out << listeFallenderObjekte[i].lastX << endl;
        out << listeFallenderObjekte[i].lastY << endl;
    }
}

// anlegen der methode deserialize
void zeichenFeld::deserialize(QFile &file)
{

    // von der datei in das programm
    QTextStream in(&file);

    in >> anzahlLeben;
    in >> punkte;
    in >> positionAvatarX;
    in >> positionAvatarY;

    int i=0;

    while (in.status() == QTextStream::Ok)
    {
        if (in.status() == QTextStream::ReadPastEnd) break;
        listeFallenderObjekte[i]=fallendesObjekt(0, 0);
        in >> listeFallenderObjekte[i].lastX >> listeFallenderObjekte[i].lastY;
        i++;
    }
    //cout << listeFallenderObjekte[0].lastX << endl;
    //cout << listeFallenderObjekte[0].lastY << endl;
    update();
}
