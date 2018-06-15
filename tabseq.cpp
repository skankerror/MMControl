#include "tabseq.h"

TabSeq::TabSeq(OscCueList *oscCueList) :
    QWidget()
{
    //oscCueList = new OscCueList(this);
    layout1 = new QVBoxLayout;
    tableView = new QTableView();
    tableView->setModel(oscCueList);
    tableView->show();
    layout1->addWidget(tableView);
    this->setLayout(layout1);
}
