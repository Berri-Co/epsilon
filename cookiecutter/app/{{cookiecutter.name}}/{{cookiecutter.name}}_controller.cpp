#include "{{cookiecutter.name}}_controller.h"

namespace {{cookiecutter.camel_name}} {

{{cookiecutter.camel_name}}Controller::{{cookiecutter.camel_name}}Controller() :
  ViewController(nullptr),
  m_{{cookiecutter.lcamel_name}}View()
{
}

View * {{cookiecutter.camel_name}}Controller::view() {
  return &m_{{cookiecutter.lcamel_name}}View;
}

}
