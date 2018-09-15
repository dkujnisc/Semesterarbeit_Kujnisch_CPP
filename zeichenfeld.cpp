#include <QtGui>
#include <QMessageBox>
#include <QGraphicsItem>
#include "zeichenFeld.h"
#include <fallendesobjekt.h>
#include <iostream>
#include <cmath>

zeichenFeld::zeichenFeld(QWidget *parent)
    : QWidget(parent)
{
    setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);
    setMouseTracking(false);

    for (int j = 0; j<100; j++) {
        listeFallenderObjekte[j]=fallendesObjekt();
    }
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
    painter.begin( this );

    // punktecounter
    painter.drawText(10, 20, QString::number(punkte));
    // quelle: https://forum.qt.io/topic/23701/solved-how-to-generate-random-number-between-two-numbers-qt/6

    // lebensanzeige
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
    painter.setBrush(Qt::green);
    painter.drawRect(positionAvatarX, positionAvatarY, 50, 50);
    painter.setBrush(Qt::black);

    // fallende objekte
        for (int j = 0; j<100; j++) {
            if (1==listeFallenderObjekte[j].isUsed) {
                painter.drawEllipse(listeFallenderObjekte[j].lastX,listeFallenderObjekte[j].lastY,50,50);
            }

        }

    if (increment) {
        for (int j = 0; j<100; j++) {
            listeFallenderObjekte[j].lastY=listeFallenderObjekte[j].lastY+3;
            if (height()==listeFallenderObjekte[j].lastY+50) {
                listeFallenderObjekte[j].isUsed=0;
            }
        }
        countdownFallenderObjekte++;
        if (0==countdownFallenderObjekte%50) {
            punkte++;
        }
        if (50<countdownFallenderObjekte) {
            for (int j = 0; j<100; j++) {
                if (0==listeFallenderObjekte[j].isUsed) {
                    listeFallenderObjekte[j].lastX=qrand() % (width() - 99) + 60;
                    listeFallenderObjekte[j].lastY=0;
                    listeFallenderObjekte[j].isUsed=1;
                    countdownFallenderObjekte=0;
                    break;
                }
            }
            countdownFallenderObjekte=0;
        }
    }
    painter.end();
    //CollisionDetection
    // http://www.cplusplus.com/forum/beginner/198640/
    // http://www.cplusplus.com/reference/cmath/abs/
    // https://www.c-plusplus.net/forum/topic/39475/quadratwurzel/2
    for (int j = 0; j<100; j++) {
        if (1==listeFallenderObjekte[j].isUsed) {

            double px =abs(static_cast<double>(positionAvatarX - listeFallenderObjekte[j].lastX));
            double py =abs(static_cast<double>(positionAvatarY - listeFallenderObjekte[j].lastY));
            double squareRoot = sqrt(px*px+py*py);
            cout<< "squareRoot" << squareRoot << endl;
            if(50.0 > squareRoot){
                listeFallenderObjekte[j].isUsed=0;
                anzahlLeben--;
                if(0>anzahlLeben){
                    stop();
                }
            }
        }
    }

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
        out << listeFallenderObjekte[i].isUsed << endl;
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
        in >> listeFallenderObjekte[i].lastX >> listeFallenderObjekte[i].lastY>>listeFallenderObjekte[i].isUsed;
        i++;
    }
    //cout << listeFallenderObjekte[0].lastX << endl;
    //cout << listeFallenderObjekte[0].lastY << endl;
    update();
}
