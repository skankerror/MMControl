#ifndef OSCCUE_H
#define OSCCUE_H

#include <QObject>
#include <QThread>
#include <QVariant>
#include "oscsend.h"
#include "MMC.h"

class OscCue : public QObject
{
  Q_OBJECT

public:
  explicit OscCue(QObject *parent = nullptr);
  ~OscCue();

  int oscSendCount(){ return v_listOscSend.size(); };
  OscSend* getOscSend(int row) const{ return v_listOscSend.at(row); };

signals:

public slots:
  void addOscSend(OscSend *oscsend);
  void insertOscSend(int row, OscSend *oscsend){ v_listOscSend.insert(row, oscsend); };
  void removeOscSend(int row){ v_listOscSend.remove(row); };
  void removeAllOscSend(){ qDeleteAll(v_listOscSend); };
  void moveOscSendPrev(int row){ v_listOscSend.swapItemsAt(row -1, row); };
  void executeCue();


private:
  QVector<OscSend *> v_listOscSend;

};

#endif // OSCCUE_H
