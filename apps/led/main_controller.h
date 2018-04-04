#ifndef APPS_LED_CONTROLLER_H
#define APPS_LED_CONTROLLER_H

#include <escher.h>

namespace Led {

class MainController : public ViewController, public ListViewDataSource, public SelectableTableViewDataSource {
public:
  MainController (Responder * parentResponder, bool & ledOn, float * rgb);
  View * view() override;

  bool handleEvent(Ion::Events::Event event) override;
  void didBecomeFirstResponder() override;

  int numberOfRows() override;
  KDCoordinate rowHeight(int j) override;

  KDCoordinate cumulatedHeightFromIndex(int j) override;
  int indexFromCumulatedHeight(KDCoordinate offsetY) override;

  HighlightCell * reusableCell(int index, int type) override;
  int reusableCellCount(int type) override;
  int typeAtLocation(int i, int j) override;
  void willDisplayCellForIndex(HighlightCell * cell, int index) override;
private:
  static constexpr int k_numberOfGauges = 3;
  MessageTableCellWithSwitch m_cellWithSwitch;
  MessageTableCellWithGauge m_cellsWithGauge[k_numberOfGauges];
  SelectableTableView m_selectableTableView;
  bool & m_ledOn;
  float * m_rgb;
};

}

#endif
