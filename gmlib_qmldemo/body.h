#ifndef BODY_H
#define BODY_H

#include "../gmlib/modules/parametrics/src/gmpsurf.h"
#include<parametrics/gmpsphere>
#include "application/gmlibwrapper.h"


// qt
#include <QObject>

class Body : public GMlib::PSphere<float> {
  GM_SCENEOBJECT(Body)
public:
    using PSphere::PSphere;
    Body(float radius);
    ~Body();

private:
    int radius_;
};

#endif // BODY_H
