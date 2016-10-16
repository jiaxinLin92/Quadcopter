#include "motors.h"

Motors::Motors(int dir){
    this->setSurroundingSphere(GMlib::Sphere<float,3>(100.0f));
    dir_ = dir;

    auto motor = std::make_shared<GMlib::PSphere<float>>(0.35f);
    motor->toggleDefaultVisualizer();
    motor->translate(GMlib::Vector<float,3>(0.0f, 0.0f, -0.75f));
    motor->setMaterial(GMlib::GMmaterial::Copper);
    motor->replot(1,1,1,1);
    motorParts_.push_back(motor);
    this->insert(motor.get());

    for(int i = 0; i < 2; i++){

        auto blade = std::make_shared<GMlib::PPlane<float>>(GMlib::Point<float,3>(0.0f,-0.1f,-0.4f),
                                                            GMlib::Vector<float,3>(0.0f,0.2f,0.0f),
                                                            GMlib::Vector<float,3>(1.8f,0.0f,0.0f));
        blade->toggleDefaultVisualizer();
        blade->rotate(GMlib::Angle(180*i), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
        blade->setMaterial(GMlib::GMmaterial::Bronze);
        blade->replot(1,1,1,1);
        motorParts_.push_back(blade);
        this->insert(blade.get());
    }
}


Motors::Motors(){

}

Motors::~Motors(){}

void Motors::setHover(){
    velocity_=9.8f;
    std::cout<<"HOVER"<<velocity_<<std::endl;
}

void  Motors::resetSpeed(){
    velocity_ = 0.0f;
    speed_=0.0f;
}


void Motors::setVelocity(float velocity){
    velocity_ += velocity;
    std::cout<<velocity_<<std::endl;
}

void Motors::speedUp(float speed)
{
    speed_ += speed;
}

void Motors::speedDown(float speed)
{
    speed_ -= speed;
}



float Motors::getW(){

    return(velocity_+speed_)/0.016;
}

void Motors::localSimulate(double dt) {
    this->rotate(GMlib::Angle(velocity_*dt), GMlib::Vector<float,3>(0.0f, 0.0f, 1.0f));
}
