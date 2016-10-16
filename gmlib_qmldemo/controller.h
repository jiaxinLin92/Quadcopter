#ifndef CONTROLLER
#define CONTROLLER

class Quadcopter;

// qt
#include <QObject>

class Controller : public QObject{
    Q_OBJECT

public:
    Controller(Quadcopter* quadcopter);
//press
    void quadHover();
    void quadStop();

    void quadUp();
    void quadDown();

    void quadPitchForward();
    void quadPitchBackward();

    void quadYawLeft();
    void quadYawRight();

    void quadRollLeft();
    void quadRollRight();


protected:

private:
    Quadcopter* quadcopter_;




};
#endif
