#ifndef APPS_BRAINFUCK_EXECUTION_CONTROLLER_H
#define APPS_BRAINFUCK_EXECUTION_CONTROLLER_H

#include <escher.h>
#include "input_controller.h"
#include "machine.h"

namespace Brainfuck {

class ExecutionController : public ViewController {
public:
  ExecutionController(Responder * parentResponder, Machine & machine, char * codeBuffer, char * outputBuffer, size_t outputBufferSize);
  ~ExecutionController();
  void viewWillAppear() override;
  View * view() override;
  const char * title() override;
  bool handleEvent(Ion::Events::Event event) override;
  void execute();

private:
  BufferTextView m_outputView;
  Machine & m_machine;
  char * m_buffer;
  size_t m_bufferSize;
  char * m_output;
  size_t m_outputSize;
};

}

#endif
