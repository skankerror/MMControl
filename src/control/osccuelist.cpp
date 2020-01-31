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

#include "osccuelist.h"

OscCueList::OscCueList(QObject *parent):
  QAbstractTableModel(parent)
{}

OscCueList::~OscCueList()
{
  qDeleteAll( v_listCue);
}

int OscCueList::rowCount(const QModelIndex &index) const
{
  int count = v_listCue.size();
  if (v_listCue.size())
  {
    for (int i = 0; i < v_listCue.size(); i++)
    {
      count += getOscCue(i)->oscSendCount();
    }
  }
  return index.isValid() ? 0 : count;
}

int OscCueList::columnCount(const QModelIndex &index) const
{
  return index.isValid() ? 0 : Count;
}

QVariant OscCueList::data(const QModelIndex &index, int role) const
{
  if (!index.isValid() || index.row() < 0 || !(index.flags().testFlag(Qt::ItemIsEditable))
      || index.row() > rowCount() || isRowCue(index.row())) return QVariant();
  int row = index.row();
  int col = index.column();
  QBrush salmonColor(QColor("#59271E"));

  OscSend *tempSend = getOscCue(getSendCueId(row) - 1)->getOscSend(getSendId(row) - 1);

  switch (role)
  {
  case Qt::DisplayRole: case Qt::EditRole:
    switch (col)
    {
    case Champ: return tempSend->getChampToString();
    case P_name: return tempSend->getP_name();
    case P_name2: return tempSend->getP_name2();
    case Uri: return tempSend->getP_uri();
    case Color: return tempSend->getP_color();
    case P_Id: return tempSend->getP_ID1();
    case P_Id2: return tempSend->getP_ID2();
    case Rate: return tempSend->getP_rate();
    case P_opac: return tempSend->getP_opacity();
    case Vol: return tempSend->getP_volume();
    case M_name: return tempSend->getM_name();
    case M_name2: return tempSend->getM_name2();
    case M_Id: return tempSend->getM_ID1();
    case M_opac: return tempSend->getM_opacity();
    case Visible: return tempSend->getM_isvisible();
    case Solo: return tempSend->getM_issolo();
    case Lock: return tempSend->getM_islocked();
    case Depth: return tempSend->getM_depth();
    case Fade_In: return tempSend->getIsfadein();
    case Time: return tempSend->getTime();
    case Wait: return tempSend->getTimewait();
    default: break;
    }
  case Qt::BackgroundRole:
    if(col == Champ) return salmonColor;
    switch(tempSend->getChamp())
    {
    case P_NAME: if(col == P_name || col == P_Id) return salmonColor; break;
    case P_REWIND: if(col == P_Id) return salmonColor; break;
    case P_COLOR: if(col == Color || col == P_Id) return salmonColor; break;
    case P_OPACITY: if(col == P_Id || col == P_opac) return salmonColor; break;
    case P_VOLUME: if(col == P_Id || col == Vol) return salmonColor; break;
    case P_RATE: if(col == P_Id || col == Rate) return salmonColor; break;
    case P_URI: if(col == Uri || col == P_Id) return salmonColor; break;
    case M_NAME: if(col == M_name || col == M_Id) return salmonColor; break;
    case M_OPACITY: if(col == M_opac || col == M_Id) return salmonColor; break;
    case M_VISIBLE: if(col == Visible || col == M_Id) return salmonColor; break;
    case M_SOLO: if(col == M_Id || col == Solo) return salmonColor; break;
    case M_LOCK: if(col == M_Id || col == Lock) return salmonColor; break;
    case M_DEPTH: if(col == M_Id || col == Depth) return salmonColor; break;
    case P_XFADE: if(col == P_Id || col == P_Id2 || col == Time) return salmonColor; break;
    case P_FADE: if(col == P_Id || col == Fade_In || col == Time) return salmonColor; break;
    case R_P_NAME: if(col == P_name || col == P_name2) return salmonColor; break;
    case R_P_REWIND: if(col == P_name) return salmonColor; break;
    case R_P_OPACITY: if(col == P_name || col == P_opac) return salmonColor; break;
    case R_P_VOLUME: if(col == P_name || col == Vol) return salmonColor; break;
    case R_P_RATE: if(col == P_name || col == Rate) return salmonColor; break;
    case R_P_URI: if(col == P_name || col == Uri) return salmonColor; break;
    case R_P_COLOR: if(col == P_name || col == Color) return salmonColor; break;
    case R_M_NAME: if(col == M_name || col == M_name2) return salmonColor; break;
    case R_M_OPACITY: if(col == M_name || col == M_opac) return salmonColor; break;
    case R_M_VISIBLE: if(col == M_name || col == Visible) return salmonColor; break;
    case R_M_SOLO: if(col == M_name || col == Solo) return salmonColor; break;
    case R_M_LOCK: if(col == M_name || col == Lock) return salmonColor; break;
    case R_M_DEPTH: if(col == M_name || col == Depth) return salmonColor; break;
    case R_P_FADE: if(col == P_name || col == Fade_In || col == Time) return salmonColor; break;
    case R_P_XFADE: if(col == P_name || col == P_name2 || col == Time) return salmonColor; break;
    default: break;
    }
  case Qt::TextAlignmentRole: return Qt::AlignCenter;
  default: break;
  }
  return QVariant();
}

bool OscCueList::setData(const QModelIndex &index, const QVariant &value, int role)
{
  Q_UNUSED(role);
  if (!index.isValid() || index.row() < 0 || !(index.flags().testFlag(Qt::ItemIsEditable))
      || index.row() > rowCount() || isRowCue(index.row())) return false;
  int row = index.row();
  int col = index.column();

  OscSend *tempSend = getOscCue(getSendCueId(row) - 1)->getOscSend(getSendId(row) - 1);

  switch(col)
  {
  case Champ: tempSend->setChamp(static_cast<champMM>(value.toInt())); break;
  case P_name: tempSend->setP_name(value.toString()); break;
  case P_name2: tempSend->setP_name2(value.toString()); break;
  case Uri: tempSend->setP_uri(value.toString()); break;
  case Color: tempSend->setP_color(value.toString()); break;
  case P_Id: tempSend->setP_ID1(value.toInt()); break;
  case P_Id2: tempSend->setP_ID2(value.toInt()); break;
  case Rate: tempSend->setP_rate(value.toInt()); break;
  case P_opac: tempSend->setP_opacity(value.toInt()); break;
  case Vol: tempSend->setP_volume(value.toInt()); break;
  case M_name: tempSend->setM_name(value.toString()); break;
  case M_name2: tempSend->setM_name2(value.toString()); break;
  case M_Id: tempSend->setM_ID1(value.toInt()); break;
  case M_opac: tempSend->setM_opacity(value.toInt()); break;
  case Visible: tempSend->setM_isvisible(value.toBool()); break;
  case Solo: tempSend->setM_issolo(value.toBool()); break;
  case Lock: tempSend->setM_islocked(value.toBool()); break;
  case Depth: tempSend->setM_depth(value.toInt()); break;
  case Fade_In: tempSend->setIsfadein(value.toBool()); break;
  case Time: tempSend->setTime(value.toDouble()); break;
  case Wait: tempSend->setTimewait(value.toDouble()); break;
  default: break;
  }
  emit dataChanged(index, index);
  return true;
}

QVariant OscCueList::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole)
  {
    if (orientation == Qt::Horizontal)
    {
      switch(section)
      {
      case Champ: return QString("Champ");
      case P_name: return QString("P_name");
      case P_name2: return QString("p_name2");
      case Uri: return QString("Uri");
      case Color: return QString("Color");
      case P_Id: return QString("P_Id");
      case P_Id2: return QString("P_Id2");
      case Rate: return QString("Rate");
      case P_opac: return QString("P_opac");
      case Vol: return QString("Vol");
      case M_name: return QString("M_name");
      case M_name2: return QString("M_name2");
      case M_Id: return QString("M_Id");
      case M_opac: return QString("M_opac");
      case Visible: return QString("Visible");
      case Solo: return QString("Solo");
      case Lock: return QString("Lock");
      case Depth: return QString("Depth");
      case Fade_In: return QString("Fade_In");
      case Time: return QString("Time");
      case Wait: return QString("Wait");
      default: return QVariant(); break;
      }
    }
    if (orientation == Qt::Vertical)
    {
      if (isRowCue(section)) return QString("CUE %1").arg(getCueId(section));
      else return QString("send %1").arg(getSendId(section));
      return QVariant();
    }
  }
  return QVariant();
}

Qt::ItemFlags OscCueList::flags(const QModelIndex &index) const
{
  if (getOscCueCount() && index.isValid() && index.row() > -1 && index.row() < rowCount() && !isRowCue(index.row()))
  {
    int row = index.row();
    int col = index.column();
    OscSend *tempSend = getOscCue(getSendCueId(row) - 1)->getOscSend(getSendId(row) - 1);
    champMM champ = tempSend->getChamp();
    if (col == Champ || col == Wait) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    else if (champ == P_NAME) {if (col == P_name || col == P_Id) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ == P_REWIND) {if (col == P_Id) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ == P_REWIND) {if (col == P_Id) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ == P_COLOR) {if (col == Color || col == P_Id) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ == P_OPACITY) {if (col == P_Id || col == P_opac) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ == P_VOLUME) {if (col == P_Id || col == Vol) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ == P_RATE) {if (col == P_Id || col == Rate) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ == P_URI) {if (col == Uri || col == P_Id) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ == M_NAME) {if (col == M_name || col == M_Id) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ == M_OPACITY) {if (col == M_Id || col == M_opac) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ == M_VISIBLE) {if (col == M_Id || col == Visible) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ == M_SOLO) {if (col == M_Id || col == Solo) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ == M_LOCK) {if (col == M_Id || col == Lock) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ == M_DEPTH) {if (col == M_Id || col == Depth) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ == P_XFADE) {if (col == P_Id || col == P_Id2 || col == Time) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ == P_FADE) {if (col == P_Id || col == Fade_In || col == Time) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ == R_P_NAME) {if (col == P_name || col == P_name2)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ == R_P_REWIND) {if (col == P_name) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ ==  R_P_OPACITY) {if (col == P_name || col == P_opac) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ ==  R_P_VOLUME) {if (col == P_name || col == Vol) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ ==  R_P_RATE) {if (col == P_name || col == Rate) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ ==  R_P_URI) {if (col == P_name || col == Uri) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ ==  R_P_COLOR) {if (col == P_name || col == Color) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ ==  R_M_NAME) {if (col == M_name || col == M_name2) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ ==  R_M_OPACITY) {if (col == M_name || col == M_opac) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ ==  R_M_VISIBLE) {if (col == M_name || col == Visible) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ ==  R_M_SOLO) {if (col == M_name || col == Solo) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ ==  R_M_LOCK) {if (col == M_name || col == Lock) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ ==  R_M_DEPTH) {if (col ==M_name || col == Depth) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ ==  R_P_FADE) {if (col == P_name || col == Fade_In || col == Time) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    else if (champ ==  R_P_XFADE) {if (col == P_name || col == P_name2 || col == Time) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  }
  return QAbstractTableModel::flags(index);
}

OscCue *OscCueList::getOscCue(const int row) const
{
  return v_listCue.at(row);
}

bool OscCueList::isRowCue(const int row) const
{
  if (!getOscCueCount()) return false;
  int count = 0; // count pour repérer les cue dans la boucle for d'après
  for (int i = 0; i < getOscCueCount(); i++)
  {
    if (row == count) return true;
    count += getOscCue(i)->oscSendCount() + 1;
  }
  return false;
}

int OscCueList::getCueId(const int row) const
{
  if (!isRowCue(row) || !getOscCueCount() || row > rowCount() - 1 || row < 0) return -1;
  int count = 0;
  for (int i = 0; i < getOscCueCount(); i++)
  {
    if (row == count) return i + 1;
    count += getOscCue(i)->oscSendCount() + 1;
  }
  return -1;
}

int OscCueList::getSendId(const int row) const
{
  if (isRowCue(row) || row > rowCount() - 1 || row < 0) return -1;
  int count = 0;
  for (int i = 0; i < getSendCueId(row) - 1; i++)
  {
    count += getOscCue(i)->oscSendCount() +1;
  }
  return row - count;
}

int OscCueList::getSendCueId(const int row) const
{
  if (isRowCue(row) || row > rowCount() - 1 || row < 0) return -1;
  int count = 0;
  int max = 0;
  for (int i = 0; i < getOscCueCount(); i++)
  {
    max += getOscCue(i)->oscSendCount() + i;
    if (row == count || row < max + 1) {return i + 1;}
    count += getOscCue(i)->oscSendCount() + 1;
  }
  return -1;
}

OscSend* OscCueList::retOscsendFromFileLine(QStringList &lineToken)
{
  champMM m_champ = NOOP;
  int m_champInt = 0;
  QString m_p_name = "";
  QString m_p_name2 = "";
  QString m_p_uri = "";
  QString m_p_color = "";
  int m_p_ID1 = 0;
  int m_p_ID2 = 0;
  int m_p_rate = 0;
  int m_p_opacity = 0;
  int m_p_volume = 0;
  QString m_m_name = "";
  QString m_m_name2 = "";
  int m_m_ID1 = 0;
  int m_m_opacity = 0;
  bool m_m_isvisible = false;
  bool m_m_issolo = false;
  bool m_m_islocked = false;
  int m_m_depth = 0;
  double m_time = 0;
  bool m_isfadein = false;
  double m_timewait = false;

  // load parsed data to model accordingly
  for (int j = 0; j < lineToken.size(); j++)
  {
    QString val = lineToken.at(j);
    val = val.trimmed();
    qDebug() << val << ", ";
    QVariant value(val);
    switch(j)
    {
    case 0:
      if (val.toStdString() == "NOOP") m_champInt = NOOP;
      if (val.toStdString() == "PLAY") m_champInt = PLAY;
      if (val.toStdString() == "PAUSE") m_champInt = PAUSE;
      if (val.toStdString() == "REWIND") m_champInt = REWIND;
      if (val.toStdString() == "QUIT") m_champInt = QUIT;
      if (val.toStdString() == "P_NAME") m_champInt = P_NAME;
      if (val.toStdString() == "P_REWIND") m_champInt = P_REWIND;
      if (val.toStdString() == "P_OPACITY") m_champInt = P_OPACITY;
      if (val.toStdString() == "P_VOLUME") m_champInt = P_VOLUME;
      if (val.toStdString() == "P_RATE") m_champInt = P_RATE;
      if (val.toStdString() == "P_URI") m_champInt = P_URI;
      if (val.toStdString() == "P_COLOR") m_champInt = P_COLOR;
      if (val.toStdString() == "M_NAME") m_champInt = M_NAME;
      if (val.toStdString() == "M_OPACITY") m_champInt = M_OPACITY;
      if (val.toStdString() == "M_VISIBLE") m_champInt = M_VISIBLE;
      if (val.toStdString() == "M_SOLO") m_champInt = M_SOLO;
      if (val.toStdString() == "M_LOCK") m_champInt = M_LOCK;
      if (val.toStdString() == "M_DEPTH") m_champInt = M_DEPTH;
      if (val.toStdString() == "P_XFADE") m_champInt = P_XFADE;
      if (val.toStdString() == "P_FADE") m_champInt = P_FADE;
      if (val.toStdString() == "R_P_NAME") m_champInt = R_P_NAME;
      if (val.toStdString() == "R_P_REWIND") m_champInt = R_P_REWIND;
      if (val.toStdString() == "R_P_OPACITY") m_champInt = R_P_OPACITY;
      if (val.toStdString() == "R_P_VOLUME") m_champInt = R_P_VOLUME;
      if (val.toStdString() == "R_P_RATE") m_champInt = R_P_RATE;
      if (val.toStdString() == "R_P_URI") m_champInt = R_P_URI;
      if (val.toStdString() == "R_P_COLOR") m_champInt = R_P_COLOR;
      if (val.toStdString() == "R_M_NAME") m_champInt = R_M_NAME;
      if (val.toStdString() == "R_M_OPACITY") m_champInt = R_M_OPACITY;
      if (val.toStdString() == "R_M_VISIBLE") m_champInt = R_M_VISIBLE;
      if (val.toStdString() == "R_M_SOLO") m_champInt = R_M_SOLO;
      if (val.toStdString() == "R_M_LOCK") m_champInt = R_M_LOCK;
      if (val.toStdString() == "R_M_DEPTH") m_champInt = R_M_DEPTH;
      if (val.toStdString() == "R_P_FADE") m_champInt = R_P_FADE;
      if (val.toStdString() == "R_P_XFADE") m_champInt = R_P_XFADE;
      qDebug() << "bluk " << val << " " << m_champInt << " bluk";
      break;
    case 1: m_p_name = value.toString(); break;
    case 2: m_p_name2 = value.toString(); break;
    case 3: m_p_uri = value.toString(); break;
    case 4: m_p_color = value.toString(); break;
    case 5: m_p_ID1 = value.toInt(); break;
    case 6: m_p_ID2 = value.toInt(); break;
    case 7: m_p_rate = value.toInt(); break;
    case 8: m_p_opacity = value.toInt(); break;
    case 9: m_p_volume = value.toInt(); break;
    case 10: m_m_name = value.toString(); break;
    case 11: m_m_name2 = value.toString(); break;
    case 12: m_m_ID1 = value.toInt(); break;
    case 13: m_m_opacity = value.toInt(); break;
    case 14: m_m_isvisible = value.toInt(); break;
    case 15: m_m_issolo = value.toInt(); break;
    case 16: m_m_islocked = value.toInt(); break;
    case 17: m_m_depth = value.toInt(); break;
    case 18: m_isfadein = value.toInt(); break;
    case 19: m_time = value.toDouble(); break;
    case 20: m_timewait = value.toDouble(); break;
    default: break;
    }
  m_champ = static_cast<champMM>(m_champInt);
  }
  qDebug() << m_champ << " bluk2";

  OscSend *oscsend = new OscSend(
        this,
        m_champ,
        m_p_uri,
        m_p_name,
        m_p_name2,
        m_p_color,
        m_p_ID1,
        m_p_ID2,
        m_p_rate,
        m_p_opacity,
        m_p_volume,
        m_m_name,
        m_m_name2,
        m_m_ID1,
        m_m_opacity,
        m_m_isvisible,
        m_m_issolo,
        m_m_islocked,
        m_m_depth,
        m_time,
        m_isfadein,
        m_timewait
        );

  return oscsend;
}

void OscCueList::addCue(OscCue *osccue)
{
  QModelIndex indexTemp = QModelIndex();
  beginInsertRows(indexTemp, v_listCue.size(), v_listCue.size());
  v_listCue.append(osccue);
  endInsertRows();

  qDebug() << "cue added";
}

void OscCueList::insertCue(OscCue *osccue, int row)
{
  QModelIndex indexTemp = QModelIndex();
  beginInsertRows(indexTemp, row + 1, row + 1);
  v_listCue.insert(row + 1, osccue);
  endInsertRows();

  qDebug() << "cue inserted";
}

void OscCueList::moveCuePrev(int rowCue)
{
  QModelIndex indexTemp = QModelIndex();
  beginMoveRows(indexTemp, rowCue, rowCue, indexTemp, rowCue - 1);
  v_listCue.move(rowCue, rowCue - 1);
  endMoveRows();
}

void OscCueList::removeCue(int rowCue)
{
  QModelIndex indexTemp = QModelIndex();
  beginRemoveRows(indexTemp, rowCue, rowCue);
  v_listCue.remove(rowCue);
  endRemoveRows();
}

void OscCueList::removeAllCue()
{
  if (!(v_listCue.size())) return;
  int rows = getOscCueCount();
  for (int i = 0; i < rows; i++)
  {
    removeCue(0);
  }
  qDebug() << "All cue removed";
}

void OscCueList::addSend(OscSend *oscsend, int rowCue)
{ // vérifier avant ? ou dans l'appel dans la toolbar ?
  QModelIndex indexTemp = QModelIndex();
  OscCue *tempCue = v_listCue.at(getCueId(rowCue) - 1);
  int row = rowCue + tempCue->oscSendCount();
  beginInsertRows(indexTemp, row + 1, row + 1);
  tempCue->addOscSend(oscsend);
  endInsertRows();
}

void OscCueList::insertSend(OscSend *oscsend, int rowSend)
{ // vérifier ?
  QModelIndex indexTemp = QModelIndex();
  int cue = getSendCueId(rowSend) - 1;
  OscCue *tempCue = v_listCue.at(cue);
  beginInsertRows(indexTemp, rowSend + 1, rowSend +1);
  tempCue->insertOscSend(getSendId(rowSend), oscsend);
  endInsertRows();
}

void OscCueList::moveSendPrev(int rowSend)
{ // vérifier
  QModelIndex indexTemp = QModelIndex();
  int cue = getSendCueId(rowSend) - 1;
  OscCue *tempCue = v_listCue.at(cue);
  beginMoveRows(indexTemp, rowSend, rowSend, indexTemp, rowSend - 1);
  tempCue->moveOscSendPrev(getSendId(rowSend) - 1);
  endMoveRows();
}

void OscCueList::removeSend(int rowSend) // Vérifier
{ // vérifier
  QModelIndex indexTemp = QModelIndex();
  int cue = getSendCueId(rowSend) - 1;
  OscCue *tempCue = v_listCue.at(cue);
  beginRemoveRows(indexTemp, rowSend, rowSend);
  tempCue->removeOscSend(getSendId(rowSend) - 1);
  endRemoveRows();
}

void OscCueList::removeAllSend(int cueRow) //Vérifier ou sinon faire comme les cues ?
{ // vérifier
  QModelIndex indexTemp = QModelIndex();
  int cue = getCueId(cueRow) - 1;
  OscCue *tempCue = v_listCue.at(cue);
  beginRemoveRows(indexTemp, cueRow + 1, cueRow + 1 + tempCue->oscSendCount());
  tempCue->removeAllOscSend();
  endRemoveRows();
}

