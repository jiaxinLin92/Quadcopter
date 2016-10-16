#ifndef PLANE_H
#define PLANE_H

#include "../gmlib/modules/parametrics/src/gmpsurf.h"
#include<parametrics/gmpplane>
#include "application/gmlibwrapper.h"

// qt
#include <QObject>

class Plane : public GMlib::PPlane<float> {
  GM_SCENEOBJECT(Plane)
public:
    Plane(GMlib::Point<float,3> p1, GMlib::Vector<float,3> v1, GMlib::Vector<float,3> v2);
    ~Plane();
};

#endif
