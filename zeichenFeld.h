#include <vector>
#include <QWidget>
#include <QTimer>
#include <QFile>
#include <fallendesobjekt.h>

using namespace std;

class zeichenFeld : public QWidget
{
public:
    zeichenFeld(QWidget *parent = 0);
    ~zeichenFeld();

    void serialize (QFile &file);
    void deserialize (QFile &file);

    void start(void) { timer->start(10); increment=1; };
    void stop(void) { timer->stop(); increment=0; };

    // startlebensanzeige = 3 leben
    int anzahlLeben=3;
    int punkte=0;
    int positionAvatarX=0;
    int positionAvatarY=0;

    fallendesObjekt listeFallenderObjekte[100];

private:
    QTimer *timer;
    int increment;
protected:
    void paintEvent(QPaintEvent *event);
};
