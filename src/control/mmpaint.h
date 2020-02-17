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

#ifndef MMPAINT_H
#define MMPAINT_H

#include <QObject>
#include "MMC.h"

class MMPaint : public QObject
{
  Q_OBJECT

public:
  explicit MMPaint(QObject *parent = nullptr);
  MMPaint(const MMPaint &mmpaint, QObject *parent = nullptr);

  // getters
  int getM_id() const { return m_id; };
  QString getM_name() const { return m_name; };
  paintType getM_paintType() const { return m_paintType; };
  QString getM_uri() const { return m_uri; };
  QString getM_color() const { return m_color; };
  int getM_opacity() const { return m_opacity; };
  int getM_rate() const { return m_rate; };
  int getM_volume() const { return m_volume; };

  int getMappingId(const int vectorAt) const; // return -1 si pas d'Id
  int getMappingCount() {return v_listMappingId.size(); };

  // setters
  void setM_id(const int id) { m_id = id; };
  void setM_name(const QString name) { m_name = name; };
  void setM_paintType(const paintType type);
  void setM_uri(const QString uri) { m_uri = uri; };
  void setM_color(const QString color) { m_color = color; };
  void setM_opacity(const int opacity) { m_opacity = opacity; };
  void setM_rate(const int rate) { m_rate = rate; };
  void setM_volume(const int volume) { m_volume = volume; };

  void addMappingId(const int id);
  void changeMappingId(const int id, const int vectorAt);
  void removeMappingId(const int vectorAt);

signals:

private:
  int m_id;
  QString m_name;
  paintType m_paintType;
  QString m_uri = "";
  QString m_color = "";
  int m_opacity;
  int m_rate;
  int m_volume;
  QVector<int> v_listMappingId;
};

#endif // MMPAINT_H
