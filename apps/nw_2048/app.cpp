#include "app.h"
#include "../apps_container.h"
#include "nw_2048_icon.h"

using namespace Poincare;

namespace Nw2048 {

I18n::Message App::Descriptor::name() {
  return I18n::Message::Nw2048App;
}

I18n::Message App::Descriptor::upperName() {
  return I18n::Message::Nw2048AppCapital;
}

const Image * App::Descriptor::icon() {
  return ImageStore::Nw2048Icon;
}

App::Snapshot::Snapshot() :
  m_game(4)
{
}

App * App::Snapshot::unpack(Container * container) {
  return new App(container, this);
}

void App::Snapshot::reset() {
  m_game.resetGame();
}

App::Descriptor * App::Snapshot::descriptor() {
  static Descriptor descriptor;
  return &descriptor;
}

Game & App::Snapshot::game() {
  return m_game;
}

App::App(Container * container, Snapshot * snapshot) :
  ::App(container, snapshot, &m_controller),
  m_controller(this, snapshot->game())
{
}

}
