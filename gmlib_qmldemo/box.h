#ifndef SKYBOX_H
#define SKYBOX_H


//GMlib
#include <scene/gmsceneobject>
#include <parametrics/gmpplane>
#include <gmParametricsModule>
//stl
#include <memory>
//QT
#include <QImage>
#include <QImageReader>
#include <QOpenGLTexture>
#include <QDirIterator>

class PSurfTexVisualizer;


class Box : public GMlib::SceneObject{
    GM_SCENEOBJECT(Box)

public:
    Box();


private:

    std::vector<std::shared_ptr<GMlib::PPlane<float>>> Planes_;
    std::vector<GMlib::PSurfTexVisualizer<float,3>*> Textures_;


};

#endif //
