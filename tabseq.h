#ifndef TABSEQ_H
#define TABSEQ_H

#include <QWidget>
#include <QtWidgets>
#include <QTableView>
#include "osccuelist.h"
#include <QBoxLayout>
#include <unistd.h>
//#include <QFile>

class TabSeq : public QWidget
{
  Q_OBJECT
public:
  TabSeq(OscCueList *);

signals:

public slots:
  void executeGo();
  void movePrevious();
  void moveNext();
  void removeCue();
  void saveAs();
  void loadFile();

private:
  OscCueList *m_oscCueList;
  QHBoxLayout *layoutMain;
    QHBoxLayout *layout1;
      QVBoxLayout *boutonLayout;
        QPushButton *boutonPrev;
        QPushButton *boutonNext;
        QPushButton *boutonRemove;
        QPushButton *boutonGo;
        QPushButton *boutonSaveAs;
        QPushButton *boutonLoad;
    QTableView *tableView;


};

#endif // TABSEQ_H
