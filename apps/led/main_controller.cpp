#include <ion.h>
#include "main_controller.h"
#include "../i18n.h"

namespace Led {

MainController::MainController(Responder * parentResponder, bool & ledOn, float * rgb) :
  ViewController(parentResponder),
  m_selectableTableView(this, this, 0, 1,
    Metric::CommonTopMargin, Metric::CommonRightMargin, Metric::CommonBottomMargin, Metric::CommonLeftMargin,
    this
   ),
  m_ledOn(ledOn),
  m_rgb(rgb)
{
}

bool MainController::handleEvent(Ion::Events::Event event) {
  if (selectedRow() == 0) {
    if (event == Ion::Events::EXE || event == Ion::Events::OK) {
      m_ledOn = !m_ledOn;
      m_selectableTableView.reloadCellAtLocation(0, 0);
    } else {
      return false;
    }
  } else {
    int rgbIndex = selectedRow() - 1;
    if (event == Ion::Events::Left || event == Ion::Events::Right) {
      float delta = 0.1f;
      if (event == Ion::Events::Left) {
        delta = -delta;
      }

      float newLevel = m_rgb[rgbIndex] + delta;
      if (newLevel < 0) {
        newLevel = 0;
      } else if (newLevel > 1) {
        newLevel = 1;
      }

      m_rgb[rgbIndex] = newLevel;
      m_selectableTableView.reloadCellAtLocation(0, selectedRow());
    } else {
      return false;
    }
  }
  if (m_ledOn) {
    Ion::LED::setColor(KDColor::RGB888(255 * m_rgb[0], 255 * m_rgb[1], 255 * m_rgb[2]));
  } else {
    Ion::LED::setColor(KDColorBlack);
  }
  return true;
}

void MainController::didBecomeFirstResponder() {
  if (selectedRow() < 0) {
    selectCellAtLocation(0, 0);
  }
  app()->setFirstResponder(&m_selectableTableView);
}

int MainController::numberOfRows() {
  return 4;
}

KDCoordinate MainController::rowHeight(int j) {
  return Metric::ParameterCellHeight;
}

KDCoordinate MainController::cumulatedHeightFromIndex(int j) {
  return j * rowHeight(0);
}

int MainController::indexFromCumulatedHeight(KDCoordinate offsetY) {
  return offsetY / rowHeight(0);
}

HighlightCell * MainController::reusableCell(int index, int type) {
  switch (type) {
    case 0:
      assert(index == 0);
      return &m_cellWithSwitch;
    case 1:
      assert(index < 3);
      return &m_cellsWithGauge[index];
    default:
      assert(false);
      return nullptr;
  }
}

int MainController::reusableCellCount(int type) {
  switch (type) {
    case 0:
      // LED Switch
      return 1;
    case 1:
      // RGB Gauges
      return k_numberOfGauges;
    default:
      // WTF?
      assert(false);
      return 0;
  }
}

int MainController::typeAtLocation(int i, int j) {
  assert(i == 0);
  assert(j < 4);
  if (j == 0) {
    // LED Switch
    return 0;
  }
  // RGB Gauges
  return 1;
}

void MainController::willDisplayCellForIndex(HighlightCell * cell, int index) {
  if (index == 0) {
    MessageTableCellWithSwitch * cellWithSwitch = (MessageTableCellWithSwitch *)cell;
    cellWithSwitch->setMessage(I18n::Message::LedApp);
    SwitchView * switchView = (SwitchView *)cellWithSwitch->accessoryView();
    switchView->setState(m_ledOn);
  } else {
    assert(index < 4);
    int rgbIndex = index - 1;
    MessageTableCellWithGauge * cellWithGauge = (MessageTableCellWithGauge *)cell;
    switch (rgbIndex) {
      case 0: // R
        cellWithGauge->setMessage(I18n::Message::Red);
        break;
      case 1:
        cellWithGauge->setMessage(I18n::Message::Green);
        break;
      case 2:
        cellWithGauge->setMessage(I18n::Message::Blue);
        break;
      default:
        assert(false);
        break;
    }
    GaugeView * gaugeView = (GaugeView *)cellWithGauge->accessoryView();
    gaugeView->setLevel(m_rgb[rgbIndex]);
  }
}

View * MainController::view() {
  return &m_selectableTableView;
}

}
