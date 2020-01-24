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

  int oscSendCount();
  OscSend* getOscSend(int row) const;

signals:

public slots:
  void addOscSend(OscSend *oscsend);
  void insertOscSend(int row, OscSend *oscsend);
  void removeOscSend(int row);
  void removeAllOscSend();
  void moveOscSendPrev(int row);
  void executeCue();


private:
  QVector<OscSend *> v_listOscSend;

};

#endif // OSCCUE_H
