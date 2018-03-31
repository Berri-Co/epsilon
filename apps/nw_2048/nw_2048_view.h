#ifndef APPS_NW_2048_VIEW_H
#define APPS_NW_2048_VIEW_H

#include <escher.h>
#include <ion.h>
#include "game.h"
#include "tile.h"

namespace Nw2048 {

class Nw2048View : public View {
public:
  Nw2048View(dimenType dimen);
  ~Nw2048View();
  void drawRect(KDContext * ctx, KDRect rect) const override;
  int numberOfSubviews() const override;
  View * subviewAtIndex(int index) override;
  void redrawGame(Game & game);
private:
  int indexAtCoord(dimenType x, dimenType y) const;
  void layoutSubviews() override;
  void setUpBoard();
  void tearDownBoard();
  dimenType m_dimen;
  Tile ** m_tiles;
};

}

#endif

