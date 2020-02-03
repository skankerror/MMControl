/*
 * (c) 2020 Michaël Creusy -- creusy(.)michael(@)gmail(.)com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
