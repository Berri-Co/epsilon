#include "brainfuck_text_area.h"

namespace Brainfuck {

BrainfuckTextArea::BrainfuckTextArea(Responder * parentResponder, char * textBuffer,
  size_t textBufferSize, TextAreaDelegate * delegate,
  KDText::FontSize fontSize, KDColor textColor, KDColor backgroundColor) :
  ::TextArea(parentResponder, textBuffer, textBufferSize, delegate, fontSize, textColor, backgroundColor)
{
}

bool BrainfuckTextArea::handleEvent(Ion::Events::Event event) {
  Ion::Events::Event newEvent(event);
  if (newEvent == Ion::Events::LeftParenthesis) {
    newEvent = Ion::Events::LeftBracket;
  } else if (newEvent == Ion::Events::RightParenthesis) {
    newEvent = Ion::Events::RightBracket;
  } else if (newEvent == Ion::Events::Sqrt) {
    newEvent = Ion::Events::Lower;
  } else if (newEvent == Ion::Events::Square) {
    newEvent = Ion::Events::Greater;
  }
  return ::TextArea::handleEvent(newEvent);
}

}