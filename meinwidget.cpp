// Qt5 add:
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

#include <QtGui>
#include "meinWidget.h"

meinWidget::meinWidget(QWidget *parent)
    : QWidget(parent)
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
    connect(speichernButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    QPushButton *objektButton = new QPushButton(tr("Objekt"));
    objektButton->setFont(QFont("Arial", 18, QFont::Bold));
    connect(objektButton, SIGNAL(clicked()), this, SLOT(neu()));

    QPushButton *ladenButton = new QPushButton(tr("Laden"));
    ladenButton->setFont(QFont("Arial", 18, QFont::Bold));
    connect(ladenButton, SIGNAL(clicked()), this, SLOT(laden()));

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
    meineLebensAnzeige->update();
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

void meinWidget::laden(void)
{
    meinZeichenFeld->stop();
}
