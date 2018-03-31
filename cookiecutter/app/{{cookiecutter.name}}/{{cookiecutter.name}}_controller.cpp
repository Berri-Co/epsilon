#include "{{cookiecutter.name}}_controller.h"

namespace {{cookiecutter.camel_name}} {

{{cookiecutter.camel_name}}Controller::{{cookiecutter.camel_name}}Controller(Responder * parentResponder) :
  ViewController(parentResponder),
  m_{{cookiecutter.lcamel_name}}View()
{
}

View * {{cookiecutter.camel_name}}Controller::view() {
  return &m_{{cookiecutter.lcamel_name}}View;
}

}
