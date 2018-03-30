#ifndef {{cookiecutter.upper_name}}_APP_H
#define {{cookiecutter.upper_name}}_APP_H

#include <escher.h>
#include "{{cookiecutter.name}}_controller.h"

namespace {{cookiecutter.camel_name}} {

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
  };
private:
  App(Container * container, Snapshot * snapshot);
  {{cookiecutter.camel_name}}Controller m_{{cookiecutter.lcamel_name}}Controller;
};

}

#endif
