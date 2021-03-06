// Qt5 add:
#include <QWidget>
#include <QPushButton>
#include <QObject>
#include <QEvent>
#include "zeichenFeld.h"
#include "lebensAnzeige.h"

class meinWidget : public QWidget
{
    Q_OBJECT  // notwendig, da Slots enthalten sind

public:
    meinWidget(QWidget *parent = 0);
    QPushButton *startPauseButton;
    bool startPause=true;

private:
    zeichenFeld *meinZeichenFeld;

private slots:
    void saveFile (void);
    void loadFile (void);
    void start (void);

protected:
    bool eventFilter(QObject *object, QEvent *event);
};
