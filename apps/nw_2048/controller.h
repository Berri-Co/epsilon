#ifndef APPS_NW_2048_CONTROLLER_H
#define APPS_NW_2048_CONTROLLER_H

#include <escher.h>
#include "game.h"
#include "game_view.h"

namespace Nw2048 {

class Controller : public ViewController {
public:
  Controller(Responder * parentResponder, Game & game);
  View * view() override;
  bool handleEvent(Ion::Events::Event event) override;
private:
  void setDimen(dimenType n);
  Game & m_game;
  GameView m_gameView;
};

}

#endif
