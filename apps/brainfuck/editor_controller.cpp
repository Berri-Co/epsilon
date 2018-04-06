#include "editor_controller.h"

namespace Brainfuck {

EditorController::EditorController(Responder * parentResponder, char * textBuffer, size_t textBufferSize) :
  ViewController(parentResponder),
  m_buffer(textBuffer),
  m_bufferSize(textBufferSize),
  m_textArea(parentResponder, m_buffer, m_bufferSize)
{
}

void EditorController::didBecomeFirstResponder() {
  app()->setFirstResponder(&m_textArea);
}

View * EditorController::view() {
  return &m_textArea;
}

const char * EditorController::title() {
  return "Code";
}

}
