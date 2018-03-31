#ifndef NW_2048_GAME_H
#define NW_2048_GAME_H

#include <stdint.h>

namespace Nw2048 {

typedef int8_t dimenType;
typedef int8_t valueType;

class Game {
public:
  Game(dimenType n);
  ~Game();
  void resetGame();
  bool move(bool x, dimenType d);
  void setDimen(dimenType n);
  valueType get(dimenType x, dimenType y);
  bool isFull();
  bool isInitialized();
  dimenType dimen();
  dimenType occupied();

private:
  bool fall(bool x, dimenType d);
  bool moveBlock(dimenType x, dimenType y, dimenType tx, dimenType ty);
  void placeNewBlock();
  void setUpBoard();
  void tearDownBoard();
  valueType ** m_board;
  dimenType m_dimen;
  dimenType m_occupied;
  bool m_initialized;
};

}

#endif
