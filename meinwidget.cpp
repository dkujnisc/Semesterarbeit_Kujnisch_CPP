// Qt5 add:
#include <QPushButton>
#include <QGridLayout>

#include <QtGui>
#include "meinWidget.h"

meinWidget::meinWidget(QWidget *parent)
    : QWidget(parent)
{
    startPauseButton = new QPushButton(tr("Start"));
    startPauseButton->setFont(QFont("Arial", 18, QFont::Bold));
    connect(startPauseButton, SIGNAL(clicked()), this, SLOT(start()));

    QPushButton *speichernButton = new QPushButton(tr("Speichern"));
    speichernButton->setFont(QFont("Arial", 18, QFont::Bold));
    connect(speichernButton, SIGNAL(clicked()), qApp, SLOT(quit()));



    QPushButton *objektButton = new QPushButton(tr("Objekt"));
    objektButton->setFont(QFont("Arial", 18, QFont::Bold));
    connect(objektButton, SIGNAL(clicked()), this, SLOT(neu()));

    QPushButton *stopButton = new QPushButton(tr("Stop"));
    stopButton->setFont(QFont("Arial", 18, QFont::Bold));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stop()));

    meinZeichenFeld = new zeichenFeld;

    QGridLayout *gridLayout = new QGridLayout;
    /*
    gridLayout->addWidget(objektButton, 2, 0);
    gridLayout->addWidget(stopButton, 3, 0);
    */
    gridLayout->addWidget(startPauseButton, 0, 0);
    gridLayout->addWidget(speichernButton, 0, 1);
    gridLayout->addWidget(meinZeichenFeld, 1, 0, 10, 10);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);
}

void meinWidget::start(void)
{
    // zustandscheck: start oder pause?
    if (startPause) {
        startPauseButton->setText("Pause");
    } else {
        startPauseButton->setText("Start");
    }
    // zustandswechsel
    startPause=!startPause;
    meinZeichenFeld->start();
}

void meinWidget::neu(void)
{
    meinZeichenFeld->kreise++;
}

void meinWidget::stop(void)
{
    meinZeichenFeld->stop();
}
