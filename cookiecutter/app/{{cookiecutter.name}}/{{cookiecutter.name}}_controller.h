#ifndef APPS_{{cookiecutter.upper_name}}_CONTROLLER_H
#define APPS_{{cookiecutter.upper_name}}_CONTROLLER_H

#include <escher.h>
#include "{{cookiecutter.name}}_view.h"

namespace {{cookiecutter.camel_name}} {

class {{cookiecutter.camel_name}}Controller : public ViewController {
public:
  {{cookiecutter.camel_name}}Controller();
  View * view() override;
private:
  {{cookiecutter.camel_name}}View m_{{cookiecutter.lcamel_name}}View;
};

}

#endif
