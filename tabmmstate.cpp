#include "tabmmstate.h"

TabMMState::TabMMState(MMState * mmstate) :
  QWidget(),
  m_mmstate(mmstate)
{
  QPalette pal = palette();
  pal.setColor(QPalette::Background, Qt::lightGray);
  setAutoFillBackground(true);
  setPalette(pal);
}
