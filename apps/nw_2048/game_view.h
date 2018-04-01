#ifndef APPS_NW_2048_GAME_VIEW_H
#define APPS_NW_2048_GAME_VIEW_H

#include <escher.h>
#include <ion.h>
#include "game.h"
#include "tile.h"

namespace Nw2048 {

class GameView : public View {
public:
  GameView(dimenType dimen);
  ~GameView();
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

