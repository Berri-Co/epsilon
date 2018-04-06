#include "app.h"
#include "../apps_container.h"
#include "brainfuck_icon.h"
extern "C" {
#include <string.h>
}

using namespace Poincare;

namespace Brainfuck {

I18n::Message App::Descriptor::name() {
  return I18n::Message::BrainfuckApp;
}

I18n::Message App::Descriptor::upperName() {
  return I18n::Message::BrainfuckAppCapital;
}

const Image * App::Descriptor::icon() {
  return ImageStore::BrainfuckIcon;
}

App::Snapshot::Snapshot() :
  m_machine(),
  m_code(nullptr),
  m_output(nullptr)
{
}

App::Snapshot::~Snapshot() {
  if (m_code) {
    delete[] m_code;
  }
  if (m_output) {
    delete[] m_output;
  }
}

char * App::Snapshot::codeBuffer() {
  if (m_code == nullptr) {
    m_code = new char[255];
    strlcpy(m_code, R"EOF(++++++++[>++++[>++>+++>+++>+<<<<
-]>+>+>->>+[<]<-]>>.>---.+++++++
..+++.>>.<-.<.+++.------.-------
-.>>+.>++.)EOF", 255);
  }
  return m_code;
}

size_t App::Snapshot::codeBufferSize() {
  return 255;
}

char * App::Snapshot::outputBuffer() {
  if (m_output == nullptr) {
    m_output = new char[255];
    *m_output = 0;
  }
  return m_output;
}

size_t App::Snapshot::outputBufferSize() {
  return 255;
}

App * App::Snapshot::unpack(Container * container) {
  return new App(container, this);
}

void App::Snapshot::reset() {
  m_machine.resetVm();
}

App::Descriptor * App::Snapshot::descriptor() {
  static Descriptor descriptor;
  return &descriptor;
}

Machine & App::Snapshot::machine() {
  return m_machine;
}

App::App(Container * container, Snapshot * snapshot) :
  ::App(container, snapshot, &m_tabViewController),
  m_executionController(&m_tabViewController, snapshot->machine(), snapshot->codeBuffer(), snapshot->outputBuffer(), snapshot->outputBufferSize()),
  m_editorController(&m_tabViewController, snapshot->codeBuffer(), snapshot->codeBufferSize()),
  m_tabViewDataSource(),
  m_tabViewController(this, &m_tabViewDataSource, &m_executionController, &m_editorController, nullptr)
{
}

}
