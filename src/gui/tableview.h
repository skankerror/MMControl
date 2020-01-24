#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>


class TableView: public QTableView
{
  Q_OBJECT
public:
  TableView(QWidget *parent = nullptr);
};

#endif // TABLEVIEW_H
