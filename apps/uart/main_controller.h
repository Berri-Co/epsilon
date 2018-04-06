#ifndef APPS_UART_CONTROLLER_H
#define APPS_UART_CONTROLLER_H

#include <escher.h>

namespace Uart {

class MainController : public ViewController, public ListViewDataSource, public SelectableTableViewDataSource {
public:
  MainController (Responder * parentResponder, bool & usart6);
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
  constexpr static int k_numberOfCellsWithBuffer = 4;
  MessageTableCellWithSwitch m_cellWithSwitch;
  MessageTableCellWithBuffer m_cellsWithBuffer[k_numberOfCellsWithBuffer];
  SelectableTableView m_selectableTableView;
  bool & m_usart6;
};

}

#endif
