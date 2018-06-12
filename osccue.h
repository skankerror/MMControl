#ifndef OSCCUE_H
#define OSCCUE_H

//#include <QObject>
//#include <QVector>
#include "oscsend.h"
#include <QStandardItemModel>
#include <QStringList>


class OscCue :
        //public QObject,
        public QStandardItemModel
{
    //Q_OBJECT
public:
    OscCue();
    OscCue(OscSend *oscsend);

signals:

public slots:

private:
    QStandardItemModel m_cueModel;
};

#endif // OSCCUE_H
