#ifndef APPS_NW_2048_CONTROLLER_H
#define APPS_NW_2048_CONTROLLER_H

#include <escher.h>
#include "game.h"
#include "nw_2048_view.h"

namespace Nw2048 {

class Nw2048Controller : public ViewController {
public:
  Nw2048Controller(Responder * parentResponder, Game & game);
  View * view() override;
  bool handleEvent(Ion::Events::Event event) override;
private:
  void setDimen(dimenType n);
  Game & m_game;
  Nw2048View m_nw2048View;
};

}

#endif
