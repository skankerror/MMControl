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

#ifndef MMSTATE_H
#define MMSTATE_H

#include <QObject>
#include <QDebug>
#include "MMC.h"

class MMMapping : public QObject
{
  Q_OBJECT

public:
  explicit MMMapping(QObject *parent = nullptr);
  MMMapping(const MMMapping &mmmapping, QObject *parent = nullptr);

  // getters
  int getM_id() const { return m_id; };
  QString getM_name() const { return m_name; };
  int getM_paintLinkedId() const { return m_paintLinkedId; };
  int getM_opacity() const { return m_opacity; };
  bool visible() const { return isVisible; };
  bool locked() const { return isLocked; };
  bool solo() const { return isSolo; };
  int getM_depth() const {return m_depth; };

  // setters
  void setM_id(const int id) { m_id = id; };
  void setM_name(const QString name) { m_name = name; };
  void setm_paintLinkedId(const int id) { m_paintLinkedId = id; };
  void setM_opacity(const int opacity) { m_opacity = opacity; };
  void setVisible(const bool visible) { isVisible = visible; };
  void setLocked(const bool locked) { isLocked = locked; };
  void setSolo(const bool solo) { isSolo = solo; };
  void setM_depth(const int depth) { m_depth = depth; };

private:
  int m_id;
  QString m_name = "Mesh";
  int m_paintLinkedId;
  int m_opacity = 100;
  bool isVisible = false;
  bool isLocked = false;
  bool isSolo = false;
  int m_depth;
};

//**********************************************************************

class MMPaint : public QObject
{
  Q_OBJECT

public:
  explicit MMPaint(QObject *parent = nullptr);
  MMPaint(const MMPaint &mmpaint, QObject *parent = nullptr);
  ~MMPaint();

  // getters
  int getM_id() const { return m_id; };
  QString getM_name() const { return m_name; };
  int getM_paintType() const { return m_paintType; };
  QString getM_uri() const { return m_uri; };
  int getM_opacity() const { return m_opacity; };
  int getM_rate() const { return m_rate; };
  int getM_volume() const { return m_volume; };

  MMMapping *getMapping(const int vectorAt) const;
  int getMappingCount() const { return v_listMapping.size(); };

  // setters
  void setM_id(const int id) { m_id = id; };
  void setM_name(const QString name) { m_name = name; };
  void setM_paintType(const int type);
  void setM_uri(const QString uri) { m_uri = uri; };
  void setM_opacity(const int opacity) { m_opacity = opacity; };
  void setM_rate(const int rate) { m_rate = rate; };
  void setM_volume(const int volume) { m_volume = volume; };

  void addMapping(MMMapping *mapping);
  void insertMapping(MMMapping *mapping,const int vectorAt);
  void removeMapping(const int vectorAt);

signals:

private:
  int m_id;
  QString m_name = "paint";
  int m_paintType = videoPaint;
  QString m_uri = "";
  int m_opacity = 0;
  int m_rate = 100;
  int m_volume = 100;
  QVector<MMMapping *> v_listMapping;
};

//*******************************************************************************

class MMState : public QObject
{
  Q_OBJECT

public:
  explicit MMState(QObject *parent = nullptr);
  MMState(const MMState &mmState, QObject *parent = nullptr);
  ~MMState();

  //getters
  MMPaint *getPaint(const int vectorAt) const;
  int getPaintCount() const { return v_listPaint.size(); }
  int getPaintVectorAt(MMPaint *paint) const;

  //setters
  void addPaint(MMPaint *paint);
  void removePaint(const int vectorAt);
  void removeAllPaint();

private:
  QVector<MMPaint *> v_listPaint;
};

#endif // MMSTATE_H
