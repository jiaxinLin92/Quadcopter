#include "box.h"

Box::Box(){
    this->setSurroundingSphere(GMlib::Sphere<float,3>(100.0f));

//后
    auto Plane0 = std::make_shared<GMlib::PPlane<float>>(GMlib::Point<float,3>(30.0f,30.0f,-1.0f),
                                                             GMlib::Vector<float,3>(0.0f,0.0f,60.0f),
                                                             GMlib::Vector<float,3>(-60.0f,0.0f,0.0f));
    Plane0->toggleDefaultVisualizer();
    Plane0->setMaterial(GMlib::GMmaterial::Silver);
    Plane0->replot(1,1,1,1);
    Planes_.push_back(Plane0);
    this->insert(Plane0.get());
//左
    auto plane1 = std::make_shared<GMlib::PPlane<float>>(GMlib::Point<float,3>(-30.0f,30.0f,-1.0f),
                                                            GMlib::Vector<float,3>(0.0f,0.0f,60.0f),
                                                            GMlib::Vector<float,3>(0.0f,-60.0f,0.0f));
    plane1->toggleDefaultVisualizer();
    plane1->setMaterial(GMlib::GMmaterial::Silver);
    plane1->replot(1,1,1,1);
    Planes_.push_back(plane1);
    this->insert(plane1.get());
//右

    auto plane2 = std::make_shared<GMlib::PPlane<float>>(GMlib::Point<float,3>(30.0f,30.0f,-1.0f),
                                                           GMlib::Vector<float,3>(0.0f,0.0f,60.0f),
                                                           GMlib::Vector<float,3>(0.0f,-60.0f,0.0f));
    plane2->toggleDefaultVisualizer();
    plane2->setMaterial(GMlib::GMmaterial::Silver);
    plane2->replot(1,1,1,1);
    Planes_.push_back(plane2);
    this->insert(plane2.get());
//上

    auto plane3 = std::make_shared<GMlib::PPlane<float>>(GMlib::Point<float,3>(30.0f,30.0f,59.0f),
                                                            GMlib::Vector<float,3>(0.0f,-60.0f,0.0f),
                                                            GMlib::Vector<float,3>(-60.0f,0.0f,0.0f));
    plane3->toggleDefaultVisualizer();
    plane3->setMaterial(GMlib::GMmaterial::Gold);
    plane3->replot(1,1,1,1);
    Planes_.push_back(plane3);
    this->insert(plane3.get());



}


