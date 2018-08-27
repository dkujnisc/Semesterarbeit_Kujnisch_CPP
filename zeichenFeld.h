#include <vector>
#include <QWidget>
#include <QTimer>
#include <fallendesobjekt.h>

using namespace std;

class zeichenFeld : public QWidget
{
public:
    zeichenFeld(QWidget *parent = 0);
    ~zeichenFeld();

    void start(void) { timer->start(10); increment=1; };
    void stop(void) { timer->stop(); increment=0; };

    int kreise=0;
    // startlebensanzeige = 3 leben
    int anzahlLeben=3;
    fallendesObjekt listeFallenderObjekte[100];

private:
    QTimer *timer;
    int increment;
protected:
    void paintEvent(QPaintEvent *event);
};
