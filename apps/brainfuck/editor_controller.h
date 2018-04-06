#ifndef APPS_BRAINFUCK_EDITOR_CONTROLLER_H
#define APPS_BRAINFUCK_EDITOR_CONTROLLER_H

#include <escher.h>
#include "brainfuck_text_area.h"

namespace Brainfuck {

class EditorController : public ViewController {
public:
  EditorController(Responder * parentResponder, char * textBuffer, size_t textBufferSize);
  void didBecomeFirstResponder() override;
  View * view() override;
  const char * title() override;
private:
  char * m_buffer;
  size_t m_bufferSize;
  BrainfuckTextArea m_textArea;
};

}

#endif
