#ifndef NW_2048_APP_H
#define NW_2048_APP_H

#include <escher.h>
#include "game.h"
#include "nw_2048_controller.h"

namespace Nw2048 {

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
    Game & game();
  private:
    Game m_game;
  };
private:
  App(Container * container, Snapshot * snapshot);
  Nw2048Controller m_nw2048Controller;
};

}

#endif
