#ifndef SCENARIO_H
#define SCENARIO_H

//class
#include "application/gmlibwrapper.h"

class Plane;
class Quadcopter;
class Controller;
class Box;



// qt
#include <QObject>

class Scenario : public GMlibWrapper {
    Q_OBJECT
public:
    using GMlibWrapper::GMlibWrapper;

    void    initializeScenario() override;
    void    cleanupScenario() override;

signals:
    //press
    void Hover();
    void Stop();

    void Up();
    void Down();

    void PitchForward();
    void PitchBackward();

    void YawLeft();
    void YawRight();

    void RollLeft();
    void RollRight();

protected:

    void localSimulate(double dt);
private slots:
    void    HoverPressed();
    void    StopPressed();
    void    UpPressed();
    void    DownPressed();
    void    PitchForwardPressed();
    void    PitchBackwardPressed();
    void    YawLeftPressed();
    void    YawRightPressed();
    void    RollLeftPressed();
    void    RollRightPressed();



private:
    Plane*      plane_;
    Quadcopter* quadcopter_;
    Controller* controller_;
    Box* box_;



};

#endif // SCENARIO_H
