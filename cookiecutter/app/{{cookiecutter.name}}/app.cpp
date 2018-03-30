#include "app.h"
#include "../apps_container.h"
#include "{{cookiecutter.name}}_icon.h"

using namespace Poincare;

namespace {{cookiecutter.camel_name}} {

I18n::Message App::Descriptor::name() {
  return I18n::Message::{{cookiecutter.camel_name}}App;
}

I18n::Message App::Descriptor::upperName() {
  return I18n::Message::{{cookiecutter.camel_name}}AppCapital;
}

const Image * App::Descriptor::icon() {
  return ImageStore::{{cookiecutter.camel_name}}Icon;
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
  ::App(container, snapshot, &m_{{cookiecutter.lcamel_name}}Controller)
{
}

}
