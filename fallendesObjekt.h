#ifndef FALLENDESOBJEKT_H
#define FALLENDESOBJEKT_H

//using namespace std;

class fallendesObjekt
{
public:
    fallendesObjekt();
    ~fallendesObjekt();
    fallendesObjekt(int x, int y, int isUsed);

    int lastX=0;
    int lastY=0;
    // zur überprüfung, ob objekt angezeigt werden soll
    int isUsed=0;
};

#endif // FALLENDESOBJEKT_H
