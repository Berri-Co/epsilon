#include "app.h"
#include "../apps_container.h"
#include "led_icon.h"
extern "C" {
#include <stdlib.h>
}

using namespace Poincare;

namespace Led {

I18n::Message App::Descriptor::name() {
  return I18n::Message::LedApp;
}

I18n::Message App::Descriptor::upperName() {
  return I18n::Message::LedAppCapital;
}

const Image * App::Descriptor::icon() {
  return ImageStore::LedIcon;
}

App::Snapshot::Snapshot() :
  m_ledOn(false),
  m_rgb{1.0f, 1.0f, 1.0f}
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

bool & App::Snapshot::ledOn() {
  return m_ledOn;
}

float * App::Snapshot::rgb() {
  return m_rgb;
}

App::App(Container * container, Snapshot * snapshot) :
  ::App(container, snapshot, &m_mainController),
  m_mainController(this, snapshot->ledOn(), snapshot->rgb())
{
}

}
