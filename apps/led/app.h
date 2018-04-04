#ifndef LED_APP_H
#define LED_APP_H

#include <escher.h>
#include "main_controller.h"

namespace Led {

class App : public ::App {
public:
  class Descriptor : public ::App::Descriptor {
  public:
    I18n::Message name() override;
    I18n::Message upperName() override;
    const Image * icon() override;
  };
  class Snapshot : public ::App::Snapshot {
  public:
    Snapshot();
    App * unpack(Container * container) override;
    void reset() override;
    Descriptor * descriptor() override;
    bool & ledOn();
    float * rgb();
  private:
    bool m_ledOn;
    float m_rgb[3];
  };
private:
  App(Container * container, Snapshot * snapshot);
  MainController m_mainController;
};

}

#endif
