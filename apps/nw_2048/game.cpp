#include "game.h"
#include <ion.h>
extern "C" {
#include <assert.h>
}

namespace Nw2048 {

Game::Game(dimenType dimen) :
  m_dimen(dimen),
  m_occupied(0),
  m_initialized(false)
{
  setUpBoard();
}

Game::~Game() {
  tearDownBoard();
}

void Game::resetGame() {
  for (int i = 0; i < m_dimen; ++i) {
    for (int j = 0; j < m_dimen; ++j) {
      m_board[i][j] = 0;
    }
  }
  for (char i = 0; i < 2; ++i) {
    placeNewBlock();
  }
  m_occupied = 2;
  m_initialized = true;
}

bool Game::move(bool x, dimenType d) {
  bool changed = false;

  changed |= fall(x, d);
  dimenType bs = d == -1 ? 0 : m_dimen - 1;
  for (dimenType a = 0; a < m_dimen; ++a) {
    for (dimenType b = bs; b >= 0 && b < m_dimen; b -= d) {
      if (x) {
        if (moveBlock(b, a, b + d, a)) {
          changed = true;
          b -= d;
        }
      } else {
        if (moveBlock(a, b, a, b + d)) {
          changed = true;
          b -= d;
        }
      }
    }
  }
  changed |= fall(x, d);
  if (changed) {
    placeNewBlock();
  }

  return changed;
}

bool Game::fall(bool x, dimenType d) {
  bool changed = false;

  dimenType bs = d == -1 ? 0 : m_dimen - 1;
  for (dimenType a = 0; a < m_dimen; ++a) {
    dimenType emptyb = -1;
    for (dimenType b = bs; b >= 0 && b < m_dimen; b -= d) {
      dimenType sx = x ? b : a;
      dimenType sy = x ? a : b;
      if (m_board[sx][sy] == 0 && emptyb == -1) {
        emptyb = b;
      } else if (m_board[sx][sy] != 0 && emptyb != -1) {
        dimenType tx = x ? emptyb : sx;
        dimenType ty = x ? sy : emptyb;
        moveBlock(sx, sy, tx, ty); // must be true
        emptyb -= d;
        changed = true;
      }
    }
  }

  return changed;
}

void Game::setDimen(dimenType n) {
  tearDownBoard();
  m_dimen = n;
  m_initialized = false;
  setUpBoard();
}

valueType Game::get(dimenType x, dimenType y) {
  return m_board[x][y];
}

bool Game::isFull() {
  assert(m_occupied <= m_dimen * m_dimen);
  return m_occupied == m_dimen * m_dimen;
}

bool Game::isInitialized() {
  return m_initialized;
}

dimenType Game::dimen() {
  return m_dimen;
}

dimenType Game::occupied() {
  return m_occupied;
}

bool Game::moveBlock(dimenType x, dimenType y, dimenType tx, dimenType ty) {
  if (tx < 0 || tx >= m_dimen || ty < 0 || ty >= m_dimen || m_board[x][y] == 0) {
    return false;
  }
  if (m_board[tx][ty] != 0 && m_board[tx][ty] != m_board[x][y]) {
    return false;
  }

  if (m_board[tx][ty] == m_board[x][y]) {
    m_occupied--;
    m_board[tx][ty]++;
  } else {
    m_board[tx][ty] = m_board[x][y];
  }

  m_board[x][y] = 0;
  return true;
}

void Game::placeNewBlock() {
  assert(!this->isFull());
  while (true) {
    dimenType x = Ion::random() % m_dimen;
    dimenType y = Ion::random() % m_dimen;
    if (m_board[x][y] == 0) {
      m_board[x][y] = 1;
      m_occupied++;
      return;
    }
  }
}

void Game::setUpBoard() {
  m_board = new valueType*[m_dimen];
  for (dimenType i = 0; i < m_dimen; ++i) {
    m_board[i] = new valueType[m_dimen];
  }
}

void Game::tearDownBoard() {
  for (dimenType i = 0; i < m_dimen; ++i) {
    delete[] m_board[i];
  }
  delete[] m_board;
}

}
