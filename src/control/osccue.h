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
  explicit OscCue(QObject *parent = nullptr, double totalTime = 0, QString noteCue = "");
  ~OscCue();

  int oscSendCount() const;
  OscSend* getOscSend(int vectAt);

  QString getNoteCue()const {return m_noteCue; };
  double getTotalTime()const {return m_totalTime; };

  void setNoteCue(const QString noteCue) {m_noteCue = noteCue; };
  void setTotalTime(const double totalTime) {m_totalTime = totalTime; };

signals:

public slots:
  void addOscSend(OscSend *oscsend);
  void insertOscSend(int vectAt, OscSend *oscsend);
  void removeOscSend(int vectAt);
  void removeAllOscSend();
  void moveOscSendPrev(int vectAt);

private:
  QVector<OscSend *> v_listOscSend;
  double m_totalTime = 0;
  QString m_noteCue = "";

};

#endif // OSCCUE_H
