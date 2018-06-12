#ifndef OSCCUELIST_H
#define OSCCUELIST_H

#include <QObject>
#include <QVector>
#include <osccue.h>
//#include <QStandardItemModel>

class OscCueList :
        //public QStandardItemModel
        public QObject
{
    //Q_OBJECT
public:
    OscCueList();
    void addCue(OscCue *osccue);

signals:

public slots:

private:
    QVector<OscCue *> v_listCue;
};

#endif // OSCCUELIST_H
