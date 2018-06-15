#ifndef TABSEQ_H
#define TABSEQ_H

#include <QWidget>
#include <QtWidgets>
#include <QTableView>
#include "osccuelist.h"
#include <QBoxLayout>

class TabSeq : public QWidget
{
    Q_OBJECT
public:
    TabSeq(OscCueList *);

signals:

public slots:

private:
    //OscCueList *oscCueList;
    QVBoxLayout *layout1;
    QTableView *tableView;


};

#endif // TABSEQ_H
