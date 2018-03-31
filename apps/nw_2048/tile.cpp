#include "tile.h"
#include "game.h"

#include <stdio.h>

namespace Nw2048 {

constexpr const char * tileText[17] = {
  "",
  "2",
  "4",
  "8",
  "16",
  "32",
  "64",
  "128",
  "256",
  "512",
  "1024",
  "2048",
  "4096",
  "8192",
  "16384",
  "32768",
  "65536"
};
constexpr valueType tileTextN = 17;

constexpr KDColor tileBackground[12] = {
  KDColor::RGB24(0xBBADA0), // blank
  KDColor::RGB24(0xEEE4DA), // 2
  KDColor::RGB24(0xEDE0C8), // 4
  KDColor::RGB24(0xF2B179), // 8
  KDColor::RGB24(0xF2B179), // 16
  KDColor::RGB24(0xF67C5F), // 32
  KDColor::RGB24(0xF65E3B), // 64
  KDColor::RGB24(0xEDCF72), // 128
  KDColor::RGB24(0xEDCC61), // 256
  KDColor::RGB24(0xEDC850), // 512
  KDColor::RGB24(0xEDC53F), // 1024
  KDColor::RGB24(0xEDC22E), // 2048
};
constexpr valueType tileBackgroundN = 12;

constexpr KDColor SuperTileBackground = KDColor::RGB24(0x3C3A32);
constexpr KDColor LightTextColor = KDColor::RGB24(0xF9F6F2);
constexpr KDColor DarkTextColor = KDColor::RGB24(0x776E65);

Tile::Tile() :
  ::BufferTextView(KDText::FontSize::Large, 0.5f, 0.5f, DarkTextColor, tileBackground[0])
{
  setValue(0);
}

void Tile::setValue(valueType value) {
  if (m_value == value) {
    return;
  }

  m_value = value;
  if (value < tileTextN) {
    setText(tileText[value]);
  } else {
    setText("???");
  }
  if (value < tileBackgroundN) {
    setBackgroundColor(tileBackground[value]);
  } else {
    setBackgroundColor(SuperTileBackground);
  }
  if (value < 3) {
    setTextColor(DarkTextColor);
  } else {
    setTextColor(LightTextColor);
  }
}

}
