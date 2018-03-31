#include "nw_2048_view.h"
#include "app.h"
#include "tile.h"

namespace Nw2048 {

Nw2048View::Nw2048View(dimenType dimen) :
  View(),
  m_dimen(dimen)
{
  setUpBoard();
}

Nw2048View::~Nw2048View() {
  tearDownBoard();
}

void Nw2048View::drawRect(KDContext * ctx, KDRect rect) const {
  ctx->fillRect(KDRect(0, 0, bounds().width(), bounds().height()), KDColor::RGB24(0xBBADA0));
}

int Nw2048View::numberOfSubviews() const {
  return m_dimen * m_dimen;
}

View * Nw2048View::subviewAtIndex(int index) {
  return m_tiles[index];
}

int Nw2048View::indexAtCoord(dimenType x, dimenType y) const {
  return y * m_dimen + x;
}

void Nw2048View::layoutSubviews() {
  float paddingWeight = 0.12;
  KDCoordinate boardSize = bounds().height();
  KDCoordinate size = boardSize / (m_dimen + (m_dimen + 1) * paddingWeight);
  KDCoordinate padding = paddingWeight * size;

  if (padding < 3) {
    padding = 0;
    size = boardSize / m_dimen;
  }

  KDCoordinate xoffset = (bounds().width() - boardSize) / 2;

  for (dimenType x = 0; x < m_dimen; ++x) {
    for (dimenType y = 0; y < m_dimen; ++y) {
      int index = indexAtCoord(x, y);
      KDRect frame(
        (x + 1) * padding + size * x + xoffset,
        (y + 1) * padding + size * y,
        size,
        size
      );
      m_tiles[index]->setFrame(frame);
    }
  }
}

void Nw2048View::setUpBoard() {
  m_tiles = new Tile*[m_dimen * m_dimen];
  for (dimenType i = 0; i < m_dimen * m_dimen; ++i) {
    m_tiles[i] = new Tile();
  }
}

void Nw2048View::tearDownBoard() {
  for (dimenType i = 0; i < m_dimen * m_dimen; ++i) {
    delete m_tiles[i];
  }
  delete[] m_tiles;
}

void Nw2048View::redrawGame(Game & game) {
  if (game.dimen() != m_dimen) {
    tearDownBoard();
    m_dimen = game.dimen();
    setUpBoard();
	layoutSubviews();
    markRectAsDirty(bounds());
  }

  for (dimenType x = 0; x < m_dimen; ++x) {
    for (dimenType y = 0; y < m_dimen; ++y) {
      int index = indexAtCoord(x, y);
      m_tiles[index]->setValue(game.get(x, y));
    }
  }
}

}
