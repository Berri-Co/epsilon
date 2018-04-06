#include "input_controller.h"

namespace Brainfuck {

InputController::InputController() :
  ViewController(nullptr),
  TextFieldDelegate(),
  m_buffer(new char[k_bufferSize]),
  m_inputView(m_buffer, k_bufferSize, this),
  m_inputRunLoopActive(true)
{
  *m_buffer = 0;
}

InputController::~InputController() {
  delete[] m_buffer;
}

View * InputController::view() {
  return &m_inputView;
}

void InputController::didBecomeFirstResponder() {
  if (inputRunLoopActive()) {
    app()->setFirstResponder(m_inputView.textField());
  }
}

bool InputController::inputRunLoopActive() {
  return m_inputRunLoopActive;
}

bool InputController::textFieldShouldFinishEditing(TextField * textField, Ion::Events::Event event) {
  return event == Ion::Events::OK || event == Ion::Events::EXE;
}

bool InputController::textFieldDidFinishEditing(TextField * textField, const char * text, Ion::Events::Event event) {
  askInputRunLoopTermination();
  return true;
}

bool InputController::textFieldDidReceiveEvent(TextField * textField, Ion::Events::Event event) {
  return false;
}

Toolbox * InputController::toolboxForTextInput(TextInput * textInput) {
  AppsContainer * ac = (AppsContainer *)(app()->container());
  return ac->mathToolbox();
}

bool InputController::handleEvent(Ion::Events::Event event) {
  if (event == Ion::Events::Back) {
    askInputRunLoopTermination();
    return true;
  }
  return false;
}

const char * InputController::inputText() {
  AppsContainer * a = (AppsContainer *)(app()->container());
  m_inputRunLoopActive = true;

  a->redrawWindow();
  a->runWhile([](void * a){
    InputController * c = static_cast<InputController *>(a);
    return c->inputRunLoopActive();
  }, this);

  app()->dismissModalViewController();

  return (const char *)m_buffer;
}

void InputController::askInputRunLoopTermination() {
  m_inputRunLoopActive = false;
}

InputController::InputView::InputView(char * buffer, size_t bufferSize, TextFieldDelegate * delegate) :
  View(),
  m_buffer(buffer),
  m_draftBuffer(new char[bufferSize]),
  m_title(KDText::FontSize::Large, I18n::Message::BrainfuckInput, 0.f, 0.f, KDColorWhite, KDColorBlack),
  m_textField(nullptr, m_buffer, m_draftBuffer, bufferSize, delegate, true)
{
  *m_draftBuffer = 0;
}

InputController::InputView::~InputView() {
  delete[] m_draftBuffer;
}

void InputController::InputView::drawRect(KDContext *ctx, KDRect rect) const {
  ctx->fillRect(bounds(), KDColorBlack);
}

int InputController::InputView::numberOfSubviews() const {
  return 2;
}

View * InputController::InputView::subviewAtIndex(int index) {
  if (index == 0) return &m_title;
  else return &m_textField;
}

TextField * InputController::InputView::textField() {
  return &m_textField;
}

void InputController::InputView::layoutSubviews() {
  // m_textField.setFrame(KDRect(0, 0, 300, 300));
  KDCoordinate textHeight = KDText::charSize(KDText::FontSize::Large).height();
  m_title.setFrame(KDRect(k_padding, k_padding, bounds().width() - 2 * k_padding, textHeight));
  m_textField.setFrame(KDRect(k_padding, k_padding + textHeight, bounds().width() - 2 * k_padding, bounds().height() - 2 * k_padding - textHeight));
}

}