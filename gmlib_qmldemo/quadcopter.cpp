#include "quadcopter.h"

Quadcopter::Quadcopter(std::shared_ptr<GMlib::Camera> cam){

    this->setSurroundingSphere(GMlib::Sphere<float,3>(1.0f));

    cam_ = cam;
    this->insert(cam_.get());

    frame_ = std::make_shared<Frame>();
    this->insert(frame_.get());


    auto motor1_ = std::make_shared<Motors>(1);
    auto motor2_ = std::make_shared<Motors>(1);
    auto motor3_ = std::make_shared<Motors>(-1);
    auto motor4_ = std::make_shared<Motors>(-1);

    motor1_->translate(GMlib::Vector<float,3>(0.0f, 5.0f, 0.75f));
    motor2_->translate(GMlib::Vector<float,3>(0.0f, -5.0f, 0.75f));

    motor3_->translate(GMlib::Vector<float,3>(-5.0f, 0.0f, 0.75f));
    motor4_->translate(GMlib::Vector<float,3>(5.0f, 0.0f, 0.75f));

    motors_.push_back(motor1_);
    motors_.push_back(motor2_);
    motors_.push_back(motor3_);
    motors_.push_back(motor4_);


    this->insert(motor1_.get());
    this->insert(motor2_.get());
    this->insert(motor3_.get());
    this->insert(motor4_.get());



    bodyPoint_ = frame_->getPos();
//    std::cout<<bodyPoint_<<std::endl;
    motorPoint_ = motor1_->getPos();
//    std::cout<<motorPoint_<<std::endl;

    //initialization matrices and vector
    rotMatrix_ = GMlib::SqMatrix<double,3> ();
    rotMatrix_[0][0] = 1;
    rotMatrix_[0][1] = 0;
    rotMatrix_[0][2] = 0;

    rotMatrix_[1][0] = 0;
    rotMatrix_[1][1] = 1;
    rotMatrix_[1][2] = 0;

    rotMatrix_[2][0] = 0;
    rotMatrix_[2][1] = 0;
    rotMatrix_[2][2] = 1;


    rotDotMatrix_ = GMlib::SqMatrix<double,3> ();
    rotDotMatrix_[0][0] = 0;
    rotDotMatrix_[0][1] = 0;
    rotDotMatrix_[0][2] = 0;

    rotDotMatrix_[1][0] = 0;
    rotDotMatrix_[1][1] = 0;
    rotDotMatrix_[1][2] = 0;

    rotDotMatrix_[2][0] = 0;
    rotDotMatrix_[2][1] = 0;
    rotDotMatrix_[2][2] = 0;


    inertiaMatrix_ = GMlib::SqMatrix<double,3> ();
    inertiaMatrix_[0][0] = 0.47316;
    inertiaMatrix_[0][1] = 0;
    inertiaMatrix_[0][2] = 0;

    inertiaMatrix_[1][0] = 0;
    inertiaMatrix_[1][1] = 0.47316;
    inertiaMatrix_[1][2] = 0;

    inertiaMatrix_[2][0] = 0;
    inertiaMatrix_[2][1] = 0;
    inertiaMatrix_[2][2] = 0.0539632;

    inverseInertiaMatrix_ = inertiaMatrix_;
    inverseInertiaMatrix_.invert();


    omegaVector = GMlib::Vector<double,3> ();
    omegaVector[0] = p_;
    omegaVector[1] = q_;
    omegaVector[2] = r_;

    omegaX_ = GMlib::SqMatrix<double,3> ();
    omegaX_ [0][0] = 0;
    omegaX_ [0][1] = -omegaVector[2];
    omegaX_ [0][2] = omegaVector[1];

    omegaX_ [1][0] = omegaVector[2];
    omegaX_ [1][1] = 0;
    omegaX_ [1][2] = -omegaVector[0];

    omegaX_ [2][0] = -omegaVector[1];
    omegaX_ [2][1] = omegaVector[0];
    omegaX_ [2][2] = 0;



}

GMlib::Vector<double,3> Quadcopter::computet(double dt)
{

    float rotor1 = std::pow(motors_[0]->getW(),2);
    float rotor2 = std::pow(motors_[1]->getW(),2);
    float rotor3 = std::pow(motors_[2]->getW(),2);
    float rotor4 = std::pow(motors_[3]->getW(),2);
    const double d = getDLength()/10;
//    std::cout<<"length d "<<d<<std::endl;

    float torque1 = d * ct_ * (rotor2-rotor4);
    float torque2 = d * ct_ * (rotor1-rotor3);
    float torque3 = cq_ * (-rotor1+rotor2-rotor3+rotor4);

    t_ = GMlib::Vector<double,3>(torque1,torque2,torque3);
    return t_;
}

void Quadcopter::computeStep(double dt){

    sumF_ = 0;
    thrustI_= 0;

    for(int i = 0; i < 4; i++){
        w_=motors_[i]->getW();
        thrustI_ = ct_ * std::pow(w_,2);
        sumF_ += thrustI_;
    }
//    std::cout<<"sum:"<<sumF_<<std::endl;

    omegaDotVector_ = inverseInertiaMatrix_*(computet(dt) -(omegaVector ^(inertiaMatrix_ * omegaVector)));
//    std::cout<<"omegaDotVector_r "<< omegaDotVector_<<std::endl;
    omegaVector = omegaDotVector_*dt;
//    std::cout<<"omegaVector "<< omegaVector<<std::endl;

    omegaX_ [0][0] = 0;
    omegaX_ [0][1] = -omegaVector[2];
    omegaX_ [0][2] = omegaVector[1];

    omegaX_ [1][0] = omegaVector[2];
    omegaX_ [1][1] = 0;
    omegaX_ [1][2] = -omegaVector[0];

    omegaX_ [2][0] = -omegaVector[1];
    omegaX_ [2][1] = omegaVector[0];
    omegaX_ [2][2] = 0;

    rotDotMatrix_ = rotMatrix_*omegaX_;
    rotMatrix_ += rotDotMatrix_*dt;
//    std::cout<<"matrix rotmatrix"<< rotMatrix_<<std::endl;

    globalMatrix_ = getMatrixGlobal();
    globalMatrix_.invert();


    GMlib::SqMatrix<float,3> convertmatrix;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            convertmatrix[i][j] = rotMatrix_[i][j];
        }
    }
//    std::cout<<"matrix 0"<< fromDtoFmatrix[0]<<std::endl;
//    std::cout<<"matrix 2"<< fromDtoFmatrix[2]<<std::endl;
    set(getPos(), convertmatrix[0], convertmatrix[2]);


    vDotVector_ = (globalMatrix_*gravity_) + (1/mass_)*GMlib::Vector<float,3>(0.0, 0.0, sumF_);

    auto pos_ = this->getPos();
    if((getPos() + vDotVector_ * dt)[2] > 0 && (getPos() + vDotVector_ * dt)[2] < 59){
        translate(vDotVector_ * dt);
    }
    else
        set(GMlib::Point<float,3>(pos_[0] ,pos_[1], 0), convertmatrix[0],convertmatrix[2]);
    std::cout<<"pos0 pos 1 0:"<<GMlib::Point<float,3>(pos_[0] ,pos_[1], 0)<<"matrix0:"<<convertmatrix[0]<<"matrix2:"<<convertmatrix[2]<<std::endl;
}


float Quadcopter::getDLength(){

    return (motorPoint_ - bodyPoint_).getLength();
}


std::vector<std::shared_ptr<Motors>> Quadcopter::getMotors(){
    return motors_;
}

void Quadcopter::localSimulate(double dt){
    computeStep(dt);

}










