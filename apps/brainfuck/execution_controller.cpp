#include "execution_controller.h"

namespace Brainfuck {

ExecutionController::ExecutionController(Responder * parentResponder, Machine & machine, char * codeBuffer, char * outputBuffer, size_t outputBufferSize) :
  ViewController(parentResponder),
  m_outputView(KDText::FontSize::Large, 0, 0),
  m_machine(machine),
  m_buffer(codeBuffer),
  m_output(outputBuffer),
  m_outputSize(outputBufferSize)
{
}

ExecutionController::~ExecutionController() {
}

void ExecutionController::viewWillAppear() {
}

View * ExecutionController::view() {
  m_outputView.setText(m_output);
  return &m_outputView;
}

const char * ExecutionController::title() {
  return "Execution";
}

bool ExecutionController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::Up) {
    app()->setFirstResponder(parentResponder());
    return true;
  }
  if (event == Ion::Events::EXE) {
    execute();
    return true;
  }
  return false;
}

void ExecutionController::execute() {
  m_machine.resetVm();
  Machine::Error error = m_machine.run(m_buffer);
  while (error != Machine::Error::Success) {
    if (error == Machine::Error::Input) {
      // No input
      InputController vc;
      app()->displayModalViewController(&vc, 0.f, 0.f, Metric::ExamPopUpTopMargin, Metric::PopUpRightMargin, Metric::ExamPopUpBottomMargin, Metric::PopUpLeftMargin);

      const char *input = vc.inputText();
      int inputLen = strlen(input);
      for (int i = 0; i < inputLen; ++i) {
        m_machine.input(input[i]);
      }
      m_machine.input(10); // Return
    } else {
      // Other errors
      break;
    }
    error = m_machine.resume();
  }
  m_machine.getOutput(m_output, m_outputSize);
  m_outputView.setText(m_output);
}

}
