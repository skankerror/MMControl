#include "tabmmstate.h"

TabMMState::TabMMState(MMState * mmstate) :
  QWidget(),
  m_mmstate(mmstate)
{
  QPalette pal = palette();
  pal.setColor(QPalette::Background, Qt::gray);
  setAutoFillBackground(true);
  setPalette(pal);
}
