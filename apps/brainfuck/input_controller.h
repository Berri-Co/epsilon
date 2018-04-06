#ifndef APPS_BRAINFUCK_INPUT_CONTROLLER_H
#define APPS_BRAINFUCK_INPUT_CONTROLLER_H

#include <escher.h>
#include "../apps_container.h"

namespace Brainfuck {

class InputController : public ViewController, public TextFieldDelegate {
public:
  InputController();
  ~InputController();
  View * view() override;
  void didBecomeFirstResponder() override;
  bool inputRunLoopActive();
  bool textFieldShouldFinishEditing(TextField * textField, Ion::Events::Event event) override;
  bool textFieldDidFinishEditing(TextField * textField, const char * text, Ion::Events::Event event) override;
  bool textFieldDidReceiveEvent(TextField * textField, Ion::Events::Event event) override;
  Toolbox * toolboxForTextInput(TextInput * textInput);
  bool handleEvent(Ion::Events::Event event) override;
  const char * inputText();
  constexpr static int k_bufferSize = 100;
private:
  class InputView : public View {
  public:
    InputView(char * buffer, size_t bufferSize, TextFieldDelegate * delegate);
    ~InputView();
    void drawRect(KDContext *ctx, KDRect rect) const override;
    int numberOfSubviews() const override;
    View *subviewAtIndex(int index) override;
    TextField * textField();
    const static int k_padding = 12;
  private:
    void layoutSubviews() override;
    char * m_buffer;
    char * m_draftBuffer;
    MessageTextView m_title;
    TextField m_textField;
  };
  char * m_buffer;
  InputView m_inputView;
  bool m_inputRunLoopActive;
  void askInputRunLoopTermination();
};

}

#endif