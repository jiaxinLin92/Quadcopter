#include "frame.h"

Frame::Frame(){
    this->setSurroundingSphere(GMlib::Sphere<float,3>(100.0f));

    float dscaler = 1.0f;


    auto body = std::make_shared<GMlib::PTorus<float>>(0.3f,0.6f,1.0f);
    body->toggleDefaultVisualizer();
    //armOneTwo->rotate(GMlib::Angle(90), GMlib::Vector<float,3>(0.0f, 1.0f, 0.0f));
    body->translate(GMlib::Vector<float,3>(0.0f/dscaler, 0.0f/dscaler, 0.0/dscaler));
    body->setMaterial(GMlib::GMmaterial::Gold);
    body->replot(1,1,1,1);
    frameParts_.push_back(body);
    this->insert(body.get());



    auto arm1 = std::make_shared<GMlib::PCylinder<float>>(0.3f/dscaler,0.3f/dscaler, 10.0f/dscaler);
    arm1->toggleDefaultVisualizer();
    arm1->rotate(GMlib::Angle(90), GMlib::Vector<float,3>(0.0f, 1.0f, 0.0f));
    arm1->translate(GMlib::Vector<float,3>(0.0f/dscaler, 0.0f/dscaler, 0.0f/dscaler));
    arm1->setMaterial(GMlib::GMmaterial::Gold);
    arm1->replot(1,1,1,1);
    armParts_.push_back(arm1);
    this->insert(arm1.get());


    auto arm2 = std::make_shared<GMlib::PCylinder<float>>(0.3f/dscaler,0.3f/dscaler, 10.0f/dscaler);
    arm2->toggleDefaultVisualizer();
    arm2->rotate(GMlib::Angle(90), GMlib::Vector<float,3>(1.0f, 0.0f, 0.0f));
    arm2->translate(GMlib::Vector<float,3>(0.0f/dscaler, 0.0f/dscaler, 0.0f/dscaler));
    arm2->setMaterial(GMlib::GMmaterial::Gold);
    arm2->replot(1,1,1,1);
    armParts_.push_back(arm2);
    this->insert(arm2.get());
}



Frame::~Frame()
{

}
