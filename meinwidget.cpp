// Qt5 add:
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QEvent>
#include <QObject>
#include <QKeyEvent>
#include <QtGui>
#include "meinWidget.h"
#include <fallendesobjekt.h>
#include <iostream>

meinWidget::meinWidget(QWidget *parent) : QWidget(parent)
{
    QLabel *highScoreLabel = new QLabel(this);
    highScoreLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    highScoreLabel->setText("0 Punkte");
    highScoreLabel->setFont(QFont("Arial", 18, QFont::Bold));
    highScoreLabel->setAlignment(Qt::AlignBottom | Qt::AlignRight);

    startPauseButton = new QPushButton(tr("Start"));
    startPauseButton->setFont(QFont("Arial", 18, QFont::Bold));
    connect(startPauseButton, SIGNAL(clicked()), this, SLOT(start()));

    QPushButton *speichernButton = new QPushButton(tr("Speichern"));
    speichernButton->setFont(QFont("Arial", 18, QFont::Bold));
    connect(speichernButton, SIGNAL(clicked()), this, SLOT(saveFile()));

    QPushButton *ladenButton = new QPushButton(tr("Laden"));
    ladenButton->setFont(QFont("Arial", 18, QFont::Bold));
    connect(ladenButton, SIGNAL(clicked()), this, SLOT(loadFile()));

    meinZeichenFeld = new zeichenFeld;

    meineLebensAnzeige = new lebensAnzeige;

    QGridLayout *gridLayout = new QGridLayout;

    /*
    gridLayout->addWidget(objektButton, 2, 0);
    gridLayout->addWidget(stopButton, 3, 0);
    */
    gridLayout->addWidget(highScoreLabel, 0, 0);
    gridLayout->addWidget(startPauseButton, 0, 1);
    gridLayout->addWidget(speichernButton, 0, 2);
    gridLayout->addWidget(ladenButton, 0, 3);
    gridLayout->addWidget(meineLebensAnzeige, 0, 4, 1, 3);
    gridLayout->addWidget(meinZeichenFeld, 1, 0, 10, 10);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);
    //meineLebensAnzeige->update();
    //meinZeichenFeld->listeFallenderObjekte[0]=fallendesObjekt(222, 333);
    meinZeichenFeld->positionAvatarX=meinZeichenFeld->width()/2;
}

void meinWidget::saveFile(void)
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getSaveFileName(this,
                                      tr("Speichern als"), ".", tr("Zeichnungen (*.myz)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht verwendet werden: ") + fileName,QMessageBox::Ok);
        }

        meinZeichenFeld->serialize(file);
        file.close();
        return;
    }
}

void meinWidget::loadFile(void)
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getOpenFileName(this,
                                      tr("Speichern als"), ".", tr("Zeichnungen (*.myz)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht geöffnet werden: ") + fileName,QMessageBox::Ok);
        }

        meinZeichenFeld->deserialize(file);
        file.close();
        return;
    }
}

void meinWidget::start(void)
{
    // zustandscheck: start oder pause?
    if (startPause) {
        startPauseButton->setText("Pause");
        meinZeichenFeld->start();
    } else {
        startPauseButton->setText("Start");
        meinZeichenFeld->stop();
    }
    // zustandswechsel
    startPause=!startPause;
}

// steuerung mit pfeiltaste
// quelle: https://stackoverflow.com/questions/10942384/handling-left-and-right-key-events-in-qt

bool meinWidget::eventFilter(QObject *object, QEvent *event)
{
    cout << "test" << endl;
 if (event->type() == QEvent::KeyPress)
  {
  QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
  cout << keyEvent->key() << "\n";

  }
 return QObject::eventFilter(object, event);
}


/*
bool meinWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (keyEvent->key() == Qt::Key_Left){
            if (hauptSpielfeld->x >= 30)
                    hauptSpielfeld->x -= 50;
            else if (hauptSpielfeld->x < 30)
                hauptSpielfeld->x = 0;
        }
        else if (keyEvent->key() == Qt::Key_Right){
            if (hauptSpielfeld->x <= 1040)
            hauptSpielfeld->x += 50;
            else if (hauptSpielfeld->x > 1040)
                hauptSpielfeld->x = 1075;
        }


        hauptSpielfeld->update();
    }
    return QObject::eventFilter(obj, event);
}
*/
