#include "guiapplication.h"

// local
#include "window.h"
#include "gmlibwrapper.h"
#include "../controller.h"


// hidmanager
#include "../hidmanager/defaulthidmanager.h"
#include "../hidmanager/hidmanagertreemodel.h"

// qt
#include <QQmlContext>
#include <QQuickItem>
#include <QStringListModel>
#include <QOpenGLContext>

// stl
#include <cassert>


std::unique_ptr<GuiApplication> GuiApplication::_instance {nullptr};


GuiApplication::GuiApplication(int& argc, char **argv) : QGuiApplication(argc, argv) {

  assert(!_instance);
  _instance = std::unique_ptr<GuiApplication>(this);


  qRegisterMetaType<HidInputEvent::HidInputParams> ("HidInputEvent::HidInputParams");

  connect( &_window, &Window::sceneGraphInitialized,
           this,     &GuiApplication::onSceneGraphInitialized,
           Qt::DirectConnection );

  connect( &_window, &Window::sceneGraphInvalidated,
           this,     &GuiApplication::onSceneGraphInvalidated,
           Qt::DirectConnection );

  connect( this, &GuiApplication::signOnSceneGraphInitializedDone,
           this, &GuiApplication::afterOnSceneGraphInitialized );

  connect( this, &QGuiApplication::lastWindowClosed,
           this, &QGuiApplication::quit );

  _window.rootContext()->setContextProperty( "rc_name_model", &_scenario.rcNameModel() );
  _window.rootContext()->setContextProperty( "hidmanager_model", _hidmanager.getModel() );
  _window.setSource(QUrl("qrc:///qml/main.qml"));

  _window.show();
}

GuiApplication::~GuiApplication() {

  _scenario.stop();
  _window.setPersistentOpenGLContext(false);
  _window.setPersistentSceneGraph(false);
  _window.releaseResources();
  _instance.release();

  qDebug() << "Bye bye ^^, ~~ \"emerge --oneshot life\"";
}

void
GuiApplication::onSceneGraphInitialized() {

  // Print format
  qDebug() << "Surface format: " << QOpenGLContext::currentContext()->format();

  // Init GMlibWrapper
  _scenario.initialize();
  _hidmanager.init(_scenario);
  connect( &_scenario,  &GMlibWrapper::signFrameReady,
           &_window,    &Window::update );

  // Init test scene of the GMlib wrapper
  _scenario.initializeScenario();
  _scenario.prepare();

  emit signOnSceneGraphInitializedDone();
}

void GuiApplication::onSceneGraphInvalidated() {

  _scenario.cleanUp();
}

void
GuiApplication::afterOnSceneGraphInitialized() {

  // Hidmanager setup
  _hidmanager.setupDefaultHidBindings();
  connect( &_window, &Window::signKeyPressed,         &_hidmanager, &StandardHidManager::registerKeyPressEvent );
  connect( &_window, &Window::signKeyReleased,        &_hidmanager, &StandardHidManager::registerKeyReleaseEvent );
  connect( &_window, &Window::signMouseDoubleClicked, &_hidmanager, &StandardHidManager::registerMouseDoubleClickEvent);
  connect( &_window, &Window::signMouseMoved,         &_hidmanager, &StandardHidManager::registerMouseMoveEvent );
  connect( &_window, &Window::signMousePressed,       &_hidmanager, &StandardHidManager::registerMousePressEvent );
  connect( &_window, &Window::signMouseReleased,      &_hidmanager, &StandardHidManager::registerMouseReleaseEvent );
  connect( &_window, &Window::signWheelEventOccurred, &_hidmanager, &StandardHidManager::registerWheelEvent );

  // Handle HID OpenGL actions; needs to have the OGL context bound;
  // QQuickWindow's beforeRendering singnal provides that on a DirectConnection
  connect( &_window, &Window::beforeRendering,        &_hidmanager, &DefaultHidManager::triggerOGLActions,
           Qt::DirectConnection );

  // Register an application close event in the hidmanager;
  // the QWindow must be closed instead of the application being quitted,
  // this is to make sure that GL exits gracefully
  QString ha_id_var_close_app =
  _hidmanager.registerHidAction( "Application", "Quit", "Close application!", &_window, SLOT(close()));
  _hidmanager.registerHidMapping( ha_id_var_close_app, new KeyPressInput( Qt::Key_Q, Qt::ControlModifier) );

  // Connect some application spesific inputs.
  connect( &_hidmanager, &DefaultHidManager::signToggleSimulation,
           &_scenario,   &GMlibWrapper::toggleSimulation );

  connect( &_hidmanager,          SIGNAL(signOpenCloseHidHelp()),
           _window.rootObject(),  SIGNAL(toggleHidBindView()) );


 //--------------------------------------------------------------------------------------------------------
  // hover
  QString ha_id_quadHover =
      _hidmanager.registerHidAction( "Keys for movement",
                                     "Hover",
                                     "Hover",
                         &_scenario, SIGNAL(Hover())
                         );
  // stop
  QString ha_id_quadStop =
      _hidmanager.registerHidAction( "Keys for movement",
                                     "Stop",
                                     "Stop",
                         &_scenario, SIGNAL(Stop())
                         );
//up
  QString ha_id_quadUp =
      _hidmanager.registerHidAction( "Keys for movement",
                                     "Up",
                                     "Up",
                         &_scenario, SIGNAL(Up())
                         );
//down
  QString ha_id_quadDown =
      _hidmanager.registerHidAction( "Keys for movement",
                                     "Down",
                                     "Down",
                         &_scenario, SIGNAL(Down())
                         );
//pitching forward
  QString ha_id_quadPitchUp =
      _hidmanager.registerHidAction( "Keys for movement",
                                     "Pitch forward",
                                     "Pitch forward",
                         &_scenario, SIGNAL(PitchForward())
                         );
//pitching backward
  QString ha_id_quadPitchDown =
      _hidmanager.registerHidAction( "Keys for movement",
                                     "Pitch backward",
                                     "Pitch backward",
                         &_scenario, SIGNAL(PitchBackward())
                         );

  QString ha_id_quadYawLeft =
      _hidmanager.registerHidAction( "Keys for movement",
                                     "Yaw left ",
                                     "Yaw left",
                         &_scenario, SIGNAL(YawLeft())
                         );

  QString ha_id_quadYawRight =
      _hidmanager.registerHidAction( "Keys for movement",
                                     "Yaw right",
                                     "Yaw right",
                         &_scenario, SIGNAL(YawRight())
                         );

  QString ha_id_quadRollLeft =
      _hidmanager.registerHidAction( "Keys for movement",
                                     "Rolls left",
                                     "Rolls left",
                         &_scenario, SIGNAL(RollLeft())
                         );

  QString ha_id_quadRollRight =
      _hidmanager.registerHidAction( "Keys for movement",
                                     "Rolls right ",
                                     "Rolls right ",
                         &_scenario, SIGNAL(RollRight())
                         );
 //--------------------------------------------------------------------------------------------------------
  _hidmanager.registerHidMapping( ha_id_quadHover,                    new KeyPressInput( Qt::Key_H ) );
  _hidmanager.registerHidMapping( ha_id_quadStop,                     new KeyPressInput( Qt::Key_Space ) );

  _hidmanager.registerHidMapping( ha_id_quadUp,                       new KeyPressInput( Qt::Key_Up ) );
  _hidmanager.registerHidMapping( ha_id_quadDown,                     new KeyPressInput( Qt::Key_Down ) );

  _hidmanager.registerHidMapping( ha_id_quadPitchUp,                  new KeyPressInput( Qt::Key_Q ) );
  _hidmanager.registerHidMapping( ha_id_quadPitchDown,                new KeyPressInput( Qt::Key_E) );

  _hidmanager.registerHidMapping( ha_id_quadYawLeft,                  new KeyPressInput( Qt::Key_W ) );
  _hidmanager.registerHidMapping( ha_id_quadYawRight,                 new KeyPressInput( Qt::Key_S ) );

  _hidmanager.registerHidMapping( ha_id_quadRollLeft,                 new KeyPressInput( Qt::Key_Left ) );
  _hidmanager.registerHidMapping( ha_id_quadRollRight,                new KeyPressInput( Qt::Key_Right) );

  // Update RCPair name model
  _scenario.updateRCPairNameModel();

  // Start simulator
  _scenario.start();
}

const GuiApplication& GuiApplication::instance() {  return *_instance; }
