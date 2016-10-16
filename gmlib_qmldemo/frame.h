#ifndef FRAME
#define FRAME

//GMlib
#include <scene/gmsceneobject>
#include <parametrics/gmpcylinder>
#include <parametrics/gmptorus>
//stl
#include <memory>

class Frame : public GMlib::SceneObject{
    GM_SCENEOBJECT(Frame)

public:
    Frame();
    ~Frame();
protected:

private:
    std::vector<std::shared_ptr<GMlib::PTorus<float>>> frameParts_;
    std::vector<std::shared_ptr<GMlib::PCylinder<float>>> armParts_;

};

#endif
