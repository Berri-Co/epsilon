#include "{{cookiecutter.name}}_view.h"

namespace {{cookiecutter.camel_name}} {

{{cookiecutter.camel_name}}View::{{cookiecutter.camel_name}}View() :
  View()
{
  m_bufferTextView.setText("Hello, world!");
}

void {{cookiecutter.camel_name}}View::drawRect(KDContext * ctx, KDRect rect) const {
  ctx->fillRect(bounds(), KDColorGreen);
}

int {{cookiecutter.camel_name}}View::numberOfSubviews() const {
  return 1;
}

View * {{cookiecutter.camel_name}}View::subviewAtIndex(int index) {
  return &m_bufferTextView;
}

void {{cookiecutter.camel_name}}View::layoutSubviews() {
  m_bufferTextView.setFrame(KDRect(0, 0, bounds().width(), bounds().height()));
}

}
