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

    // quelle: https://stackoverflow.com/questions/26368659/qwidget-how-to-receive-keypressevent-inside-child-widgets/26368894
    // diese zeile stand leider in nur sehr wenigen quellen drin
    // deshalb hat die steuerung auch am meisten nerven gekostet
    qApp->installEventFilter(this);

    QGridLayout *gridLayout = new QGridLayout;

    gridLayout->addWidget(startPauseButton, 0, 1);
    gridLayout->addWidget(speichernButton, 0, 2);
    gridLayout->addWidget(ladenButton, 0, 3);
    gridLayout->addWidget(meinZeichenFeld, 1, 0, 10, 10);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);
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
  if (event->type() == QEvent::KeyPress)
  {
  QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
  if (keyEvent->key() == Qt::Key_Left){
      meinZeichenFeld->positionAvatarX=meinZeichenFeld->positionAvatarX-5;
  }

  if (keyEvent->key() == Qt::Key_Right){
     meinZeichenFeld->positionAvatarX=meinZeichenFeld->positionAvatarX+5;
  }

  cout << keyEvent->key() << "\n";

  }
 return QObject::eventFilter(object, event);
}
