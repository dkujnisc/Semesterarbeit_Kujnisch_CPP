#ifndef LEBENSANZEIGE_H
#define LEBENSANZEIGE_H

#include <QWidget>

using namespace std;

class lebensAnzeige : public QWidget
{
public:
    lebensAnzeige(QWidget *parent = 0);
    ~lebensAnzeige();

    int anzahlLeben;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // LEBENSANZEIGE_H
