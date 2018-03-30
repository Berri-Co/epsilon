#include "app.h"
#include "../apps_container.h"
#include "hello_icon.h"

using namespace Poincare;

namespace Hello {

I18n::Message App::Descriptor::name() {
  return I18n::Message::HelloApp;
}

I18n::Message App::Descriptor::upperName() {
  return I18n::Message::HelloAppCapital;
}

const Image * App::Descriptor::icon() {
  return ImageStore::HelloIcon;
}

App::Snapshot::Snapshot()
{
}

App * App::Snapshot::unpack(Container * container) {
  return new App(container, this);
}

void App::Snapshot::reset() {
}

App::Descriptor * App::Snapshot::descriptor() {
  static Descriptor descriptor;
  return &descriptor;
}

App::App(Container * container, Snapshot * snapshot) :
  ::App(container, snapshot, &m_helloController)
{
}

}
