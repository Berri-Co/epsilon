#include "hello_view.h"

namespace Hello {

HelloView::HelloView() :
  View()
{
}

void HelloView::drawRect(KDContext * ctx, KDRect rect) const {
  ctx->fillRect(bounds(), KDColor::RGB24(0x808080));
}

}
