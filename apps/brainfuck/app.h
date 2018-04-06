#ifndef BRAINFUCK_APP_H
#define BRAINFUCK_APP_H

#include <escher.h>
#include <escher/tab_view_data_source.h>
#include <escher/tab_view_controller.h>
#include "execution_controller.h"
#include "editor_controller.h"
#include "machine.h"

namespace Brainfuck {

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
    ~Snapshot();
    App * unpack(Container * container) override;
    void reset() override;
    Descriptor * descriptor() override;
    Machine & machine();
    char * codeBuffer();
    size_t codeBufferSize();
    char * outputBuffer();
    size_t outputBufferSize();
  private:
    Machine m_machine;
    char * m_code;
    char * m_output;
  };
private:
  App(Container * container, Snapshot * snapshot);
  ExecutionController m_executionController;
  EditorController m_editorController;
  TabViewDataSource m_tabViewDataSource;
  TabViewController m_tabViewController;
};

}

#endif
