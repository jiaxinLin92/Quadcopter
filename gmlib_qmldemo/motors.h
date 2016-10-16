#ifndef MOTORS_H
#define MOTORS_H

//GMlib
#include <scene/gmsceneobject>
#include <parametrics/gmpplane>
#include <parametrics/gmpcone>
#include <parametrics/gmpcylinder>
#include <parametrics/gmpsphere>

//stl
#include <memory>
#include <vector>

class Motors : public GMlib::SceneObject{
    GM_SCENEOBJECT(Motors)

public:
    Motors(int dir);
    Motors();
    ~Motors();

    float getW();

    void setHover();
    void setVelocity(float velocity);


    void speedUp(float speed);
    void speedDown(float speed);

    void resetSpeed();


protected:

    void localSimulate(double dt);

private:
    std::vector<std::shared_ptr<GMlib::PSurf<float,3>>> rotorParts_;
    std::vector<std::shared_ptr<GMlib::PSurf<float,3>>> motorParts_;

    int dir_ = 0.0;
    float pitch_ = 0.0;
    float roll_ = 0.0;
    float yaw_ = 0.0;
    float velocity_ = 0.0f;
    float speed_;

};

#endif
