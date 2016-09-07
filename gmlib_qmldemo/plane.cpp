#include "plane.h"

Plane::Plane(GMlib::Point<float,3> p1, GMlib::Vector<float,3> v1, GMlib::Vector<float,3> v2):GMlib::PPlane<float>(p1,v1,v2)
{
    this->toggleDefaultVisualizer();
    this->replot(200,200,1,1);
    this->setMaterial(GMlib::GMmaterial::Jade);
}

Plane::~Plane(){}
