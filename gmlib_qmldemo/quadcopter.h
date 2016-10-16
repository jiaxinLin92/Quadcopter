#ifndef QUADCOPTER_H
#define QUADCOPTER_H

//class
#include "frame.h"
#include "motors.h"

#include <memory>

class Quadcopter : public GMlib::SceneObject {
    GM_SCENEOBJECT(Quadcopter)
public:
   Quadcopter(std::shared_ptr<GMlib::Camera> cam);

   void computeStep(double dt);

   std::vector<std::shared_ptr<Motors>> getMotors();
   float getDLength();
protected:

    void localSimulate(double dt);

private:

    std::shared_ptr<GMlib::Camera> cam_;

    const double mass_ = 1.25, ct_ = 8.6e-6, cq_ = 1.8e-7;
    double p_ = 0.0, q_ = 0.0, r_ = 0.0, thrustI_ = 0.0, sumF_ = 0.0;

    float w_=0;

    GMlib::Point<float,3> bodyPoint_;
    GMlib::Point<float,3> motorPoint_;

    std::shared_ptr<Frame> frame_;
    std::vector<std::shared_ptr<Motors>> motors_;

    //---------
    GMlib::Vector<float,3>   gravity_  = GMlib::Vector<float,3>(0.0,0.0,-9.81);

    GMlib::Vector<double,3> computet(double dt);
    GMlib::Vector<double,3>  t_;

    GMlib::SqMatrix<double,3> omegaX_;
    GMlib::Vector<double,3>  omegaVector;
    GMlib::Vector<double,3>  omegaDotVector_;


    GMlib::Vector<float,3>   vDotVector_;

    GMlib::SqMatrix<double,3> rotMatrix_;
    GMlib::SqMatrix<double,3> rotDotMatrix_;

    GMlib::SqMatrix<double,3> inertiaMatrix_;
    GMlib::SqMatrix<double,3> inverseInertiaMatrix_;

    GMlib::HqMatrix<float,3>  globalMatrix_;


};

#endif

