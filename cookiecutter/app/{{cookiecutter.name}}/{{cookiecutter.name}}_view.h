#ifndef APPS_{{cookiecutter.upper_name}}_VIEW_H
#define APPS_{{cookiecutter.upper_name}}_VIEW_H

#include <escher.h>

namespace {{cookiecutter.camel_name}} {

class {{cookiecutter.camel_name}}View : public View {
public:
  {{cookiecutter.camel_name}}View();
  void drawRect(KDContext * ctx, KDRect rect) const override;
  int numberOfSubviews() const override;
  View * subviewAtIndex(int index) override;
private:
  void layoutSubviews() override;
  BufferTextView m_bufferTextView;
};

}

#endif

