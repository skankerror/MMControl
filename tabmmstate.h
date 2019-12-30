#ifndef TABMMSTATE_H
#define TABMMSTATE_H

#include <QWidget>
#include <QtWidgets>
#include <QTableView>
#include "mmstate.h"
#include <QBoxLayout>

class TabMMState : public QWidget
{
  Q_OBJECT
public:
  explicit TabMMState(MMState *);

signals:

public slots:

private:
  MMState *m_mmstate;
};

#endif // TABMMSTATE_H
