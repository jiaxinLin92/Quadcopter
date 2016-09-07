#include "body.h"
#include "../gmlib/modules/parametrics/src/surfaces/gmpcylinder.h"

Body::Body(float radius){
    radius_=radius;
    this->toggleDefaultVisualizer();
    this->replot(200,200,1,1);
    this->setMaterial(GMlib::GMmaterial::Gold);

    auto cylinder1= new GMlib::PCylinder<float>(0.1,0.1,5);
    cylinder1->toggleDefaultVisualizer();
    cylinder1->replot(200,200,1,1);
    cylinder1->setMaterial(GMlib::GMmaterial::Gold);
    cylinder1->rotate(GMlib::Angle(90),GMlib::Vector<float,3>(1,0,0));
    this->insert(cylinder1);

    auto cylinder2= new GMlib::PCylinder<float>(0.1,0.1,5);
    cylinder2->toggleDefaultVisualizer();
    cylinder2->replot(200,200,1,1);
    cylinder2->setMaterial(GMlib::GMmaterial::Gold);
    cylinder2->rotate(GMlib::Angle(90),GMlib::Vector<float,3>(0,1,0));
   // cylinder2->translateGlobal(GMlib::Vector<float,3>(2,0,0),true);
    this->insert(cylinder2);
}
Body::~Body(){}
