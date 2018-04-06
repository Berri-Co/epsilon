#include <escher/text_area.h>

namespace Brainfuck {

class BrainfuckTextArea : public TextArea {
public:
  BrainfuckTextArea(Responder * parentResponder, char * textBuffer = nullptr, size_t textBufferSize = 0, TextAreaDelegate * delegate = nullptr, KDText::FontSize fontSize = KDText::FontSize::Large,
    KDColor textColor = KDColorBlack, KDColor backgroundColor = KDColorWhite);
  bool handleEvent(Ion::Events::Event event) override;
};

}