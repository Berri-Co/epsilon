#ifndef APPS_NW_2048_TILE_H
#define APPS_NW_2048_TILE_H

#include <escher.h>
#include <escher/buffer_text_view.h>

#include "game.h"

namespace Nw2048 {

class Tile : public BufferTextView {
public:
  Tile();
  void setValue(valueType value);
  void drawRect(KDContext * ctx, KDRect rect) const override;
private:
  valueType m_value;
};

}

#endif

