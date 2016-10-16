#include "controller.h"
#include "quadcopter.h"

Controller::Controller(Quadcopter* quadcopter){

    quadcopter_ = quadcopter;
}

void Controller::quadHover() {
    auto hover = quadcopter_->getMotors();
    for(int i = 0; i < 4;i++){
        hover[i]->setHover();
    }
}
void Controller::quadStop() {
    auto quad = quadcopter_->getMotors();
    for(int i = 0; i < 4;i++){
        quad[i]->resetSpeed();

//        quad[i]->resetYaw();
//        quad[i]->resetPitch();
//        quad[i]->resetRoll();
    }
}

void Controller::quadUp() {
    auto quad = quadcopter_->getMotors();
    for(int i = 0; i < 4 ;i++){
        quad[i]->setVelocity(0.2);
    }
}
void Controller::quadDown() {
    auto quad = quadcopter_->getMotors();
    for(int i = 0; i < 4;i++){
        quad[i]->setVelocity(-0.2);
    }
}

void Controller::quadPitchForward(){
    auto pitch = quadcopter_->getMotors();
    pitch[0]->speedUp(0.1);
    pitch[1]->speedDown(0.1);
    pitch[2]->speedUp(0.1);
    pitch[3]->speedUp(0.1);
}
void Controller::quadPitchBackward(){
    auto pitchback = quadcopter_->getMotors();
    pitchback[0]->speedDown(0.1);
    pitchback[1]->speedUp(0.1);
    pitchback[2]->speedDown(0.1);
    pitchback[3]->speedDown(0.1);
}

void Controller::quadYawLeft(){
    auto yawl = quadcopter_->getMotors();
    yawl[0]->speedDown(0.1);
    yawl[1]->speedUp(0.1);
    yawl[2]->speedDown(0.1);
    yawl[3]->speedUp(0.1);

}
void Controller::quadYawRight(){
    auto yawr = quadcopter_->getMotors();
    yawr[0]->speedUp(0.1);
    yawr[1]->speedDown(0.1);
    yawr[2]->speedUp(0.1);
    yawr[3]->speedDown(0.1);
}

void Controller::quadRollLeft(){
    auto roll = quadcopter_->getMotors();
    roll[0]->speedUp(0.1);
    roll[1]->speedUp(0.1);
    roll[2]->speedDown(0.1);
    roll[3]->speedUp(0.1);
}
void Controller::quadRollRight(){
    auto roll = quadcopter_->getMotors();
    roll[0]->speedDown(0.1);
    roll[1]->speedDown(0.1);
    roll[2]->speedUp(0.1);
    roll[3]->speedDown(0.1);
}

