#include "controller.h"

namespace Nw2048 {

Controller::Controller(Responder * parentResponder, Game & game) :
  ViewController(parentResponder),
  m_game(game),
  m_gameView(game.dimen())
{
  if (!m_game.isInitialized()) {
    m_game.resetGame();
  }
  m_gameView.redrawGame(m_game);
}

View * Controller::view() {
  return &m_gameView;
}

bool Controller::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::Up || event == Ion::Events::Eight) {
    m_game.move(false, -1);
  } else if (event == Ion::Events::Down || event == Ion::Events::Two) {
    m_game.move(false, 1);
  } else if (event == Ion::Events::Left || event == Ion::Events::Four) {
    m_game.move(true, -1);
  } else if (event == Ion::Events::Right || event == Ion::Events::Six) {
    m_game.move(true, 1);
  } else if (event == Ion::Events::Clear) {
    m_game.resetGame();
  } else if (event == Ion::Events::Plus) {
    setDimen(m_game.dimen() + 1);
  } else if (event == Ion::Events::Minus) {
    setDimen(m_game.dimen() - 1);
  } else {
    return false;
  }
  m_gameView.redrawGame(m_game);

  return true;
}

void Controller::setDimen(dimenType n) {
  if (m_game.occupied() > 2) {
    return;
  }

  if (n < 2 || n > 10) {
    return;
  }

  m_game.setDimen(n);
  m_game.resetGame();
  m_gameView.redrawGame(m_game);
}

}
