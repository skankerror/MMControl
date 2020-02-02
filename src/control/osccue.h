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

  int oscSendCount() const;
  OscSend* getOscSend(int vectAt);

signals:

public slots:
  void addOscSend(OscSend *oscsend);
  void insertOscSend(int vectAt, OscSend *oscsend);
  void removeOscSend(int vectAt);
  void removeAllOscSend();
  void moveOscSendPrev(int vectAt);
//  void executeCue();

private:
  QVector<OscSend *> v_listOscSend;

};

#endif // OSCCUE_H
