#include "scenario.h"
#include "controller.h"
#include "quadcopter.h"
#include "plane.h"
#include "box.h"


#include "scenario.h"
//// hidmanager
//#include "hidmanager/defaulthidmanager.h"

// gmlib
#include <gmOpenglModule>
#include <gmSceneModule>
#include <gmParametricsModule>

// qt
#include <QQuickItem>



void Scenario::initializeScenario() {

  // Insert a light
  GMlib::Point<GLfloat,3> init_light_pos( 0.0, 0.0, 15.0 );
  GMlib::PointLight *light = new GMlib::PointLight(  GMlib::GMcolor::White, GMlib::GMcolor::White,
                                                     GMlib::GMcolor::White, init_light_pos );
  light->setAttenuation(0.8, 0.002, 0.0008);
  scene()->insertLight( light, false );


  // Default camera parameters
  int init_viewport_size = 600;
  GMlib::Point<float,3>  init_cam_pos(  0.0f, 0.0f, 0.0f );
  GMlib::Vector<float,3> init_cam_dir( 0.0f, 1.0f, 0.0f );
  GMlib::Vector<float,3> init_cam_up(  0.0f, 0.0f, 1.0f );

  // Quadcopter cam
  auto quad_rcpair = createRCPair("Quadcopter");
  quad_rcpair.camera->set(init_cam_pos,init_cam_dir,init_cam_up);
  quad_rcpair.camera->setCuttingPlanes( 1.0f, 600.0f );
  quad_rcpair.camera->rotateGlobal( GMlib::Angle(-45), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
  quad_rcpair.camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -1.0f, 1.0f ) );
  scene()->insertCamera( quad_rcpair.camera.get(), false);
  quad_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Projection cam
  auto proj_rcpair = createRCPair("Projection");
  proj_rcpair.camera->set(init_cam_pos,init_cam_dir,init_cam_up);
  proj_rcpair.camera->setCuttingPlanes( 1.0f, 600.0f );
  proj_rcpair.camera->rotateGlobal( GMlib::Angle(-45), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
  proj_rcpair.camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -20.0f, 20.0f ) );
  scene()->insertCamera( proj_rcpair.camera.get() );
  proj_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Front cam
  auto front_rcpair = createRCPair("Front");
  front_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( 0.0f, -300.0f, 5.0f ), init_cam_dir, init_cam_up );
  front_rcpair.camera->setCuttingPlanes( 0.5f, 600.0f );
  scene()->insertCamera( front_rcpair.camera.get() );
  front_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Side cam
  auto side_rcpair = createRCPair("Side");
  side_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( -30.0f, 0.0f, 0.0f ), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ), init_cam_up );
  side_rcpair.camera->setCuttingPlanes( 0.5f, 600.0f );
  scene()->insertCamera( side_rcpair.camera.get() );
  side_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Top cam
  auto top_rcpair = createRCPair("Top");
  top_rcpair.camera->set( init_cam_pos + GMlib::Vector<float,3>( 0.0f, 0.0f, 50.0f ), -init_cam_up, init_cam_dir );
  top_rcpair.camera->setCuttingPlanes( 0.5f, 600.0f );
  scene()->insertCamera( top_rcpair.camera.get() );
  top_rcpair.renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );



  quadcopter_ = new Quadcopter(quad_rcpair.camera);
  scene()->insert(quadcopter_);


  //drawplane;
  auto plane1= new Plane(GMlib::Point<float,3>(30,-30,-1),
                                GMlib::Vector<float,3>(-60,0,0),
                                GMlib::Vector<float,3>(0,60,0));

  scene()->insert(plane1);



  //Surface
  box_ = new Box;
  box_->translate(GMlib::Vector<float,3>(0.0f, 0.0f, 0.0f));
  scene()->insert(box_);

  controller_ = new Controller(quadcopter_);

  connect(this,&Hover,this,&Scenario::HoverPressed);
  connect(this,&Stop,this,&Scenario::StopPressed);
  connect(this,&Up,this,&Scenario::UpPressed);
  connect(this,&Down,this,&Scenario::DownPressed);
  connect(this,&RollLeft,this,&Scenario::RollLeftPressed);
  connect(this,&RollRight,this,&Scenario::RollRightPressed);
  connect(this,&PitchForward,this,&Scenario::PitchForwardPressed);
  connect(this,&PitchBackward,this,&Scenario::PitchBackwardPressed);
  connect(this,&YawLeft,this,&Scenario::YawLeftPressed);
  connect(this,&YawRight,this,&Scenario::YawRightPressed);

}

void Scenario::cleanupScenario() {

}

void Scenario::HoverPressed()
{
    controller_->quadHover();
}

void Scenario::StopPressed()
{
    controller_->quadStop();
}


void Scenario::UpPressed()
{
    controller_->quadUp();
}

void Scenario::DownPressed()
{
    controller_->quadDown();
}

void Scenario::PitchForwardPressed()
{
    controller_->quadPitchForward();
}

void Scenario::PitchBackwardPressed()
{
    controller_->quadPitchBackward();
}

void Scenario::YawLeftPressed()
{
    controller_->quadYawLeft();
}

void Scenario::YawRightPressed()
{
    controller_->quadYawRight();
}

void Scenario::RollLeftPressed()
{
    controller_->quadRollLeft();
}

void Scenario::RollRightPressed()
{
    controller_->quadRollRight();
}




