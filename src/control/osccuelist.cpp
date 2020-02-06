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
  int count = getOscCueCount();
  if (!v_listCue.empty())
  {
    for (int i = 0; i < getOscCueCount(); i++)
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
  if (!index.isValid() || index.row() < 0 || index.row() > rowCount() - 1) return QVariant();
  int row = index.row();
  int col = index.column();
  QBrush salmonColor(QColor("#59271E"));
  QBrush yellowColor(QColor("#B8BF7E"));

  if (isRowCue(row))
  {
    OscCue *tempCue = getOscCue(getCueId(row) - 1);
    switch (role)
    {
    case Qt::DisplayRole: case Qt::EditRole:
      if (col == Wait) return tempCue->getTotalTime();
      if (col == Note) return tempCue->getNoteCue();
      break;
    case Qt::BackgroundRole:
      /*if (col == Wait || col == Note) */return yellowColor; break;
    case Qt::TextAlignmentRole: return Qt::AlignCenter;
    default: break;
    }
  }
  else if (index.flags().testFlag(Qt::ItemIsEditable))
  {
    OscSend *tempSend = getOscCue(getSendCueId(row) - 1)->getOscSend(getSendId(row) - 1);

    switch (role)
    {
    case Qt::DisplayRole: case Qt::EditRole:
      switch (col)
      {
      case Champ: return OscSend::getChampToString(tempSend->getChamp()); break;
      case P_name: return tempSend->getP_name(); break;
      case P_name2: return tempSend->getP_name2(); break;
      case Uri: return tempSend->getP_uri(); break;
      case Color: return tempSend->getP_color(); break;
      case P_Id: return tempSend->getP_ID1(); break;
      case P_Id2: return tempSend->getP_ID2(); break;
      case Rate: return tempSend->getP_rate(); break;
      case P_opac: return tempSend->getP_opacity(); break;
      case Vol: return tempSend->getP_volume(); break;
      case M_name: return tempSend->getM_name(); break;
      case M_name2: return tempSend->getM_name2(); break;
      case M_Id: return tempSend->getM_ID1(); break;
      case M_opac: return tempSend->getM_opacity(); break;
      case Visible: return tempSend->getM_isvisible(); break;
      case Solo: return tempSend->getM_issolo(); break;
      case Lock: return tempSend->getM_islocked(); break;
      case Depth: return tempSend->getM_depth(); break;
      case Fade_In: return tempSend->getIsfadein(); break;
      case Time: return tempSend->getTime(); break;
      case Wait: return tempSend->getTimewait(); break;
      case Note: return tempSend->getNoteSend(); break;
      default: break;
      } break;
    case Qt::BackgroundRole:
      if(col == Champ) return salmonColor;
      switch(tempSend->getChamp())
      {
      case P_NAME: if(col == P_name || col == P_Id) return salmonColor; break;
      case P_REWIND: if(col == P_Id) return salmonColor; break;
      case P_COLOR:
        if(col == P_Id) return salmonColor;
        if(col == Color) return QColor(tempSend->getP_color());
        break;
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
      } break;
    case Qt::TextAlignmentRole: return Qt::AlignCenter;
    default: break;
    }
  }
  return QVariant();
}

bool OscCueList::setData(const QModelIndex &index, const QVariant &value, int role)
{
  Q_UNUSED(role);
  if (!index.isValid() || index.row() < 0 || !(index.flags().testFlag(Qt::ItemIsEditable))
      || index.row() > rowCount() - 1) return false;
  int row = index.row();
  int col = index.column();

  if (isRowCue(row) && col == Note)
  {
    getOscCue(getCueId(row) - 1)->setNoteCue(value.toString());
    emit dataChanged(index, index);
    return true;
  }

  OscCue *tempCue = getOscCue(getSendCueId(row) - 1);
  OscSend *tempSend = tempCue->getOscSend(getSendId(row) - 1);
  double oldTimeWait = tempSend->getTimewait();
  double oldTime = tempSend->getTime();
  double oldTotalTime = tempCue->getTotalTime();

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
  case Time:
    tempSend->setTime(value.toDouble());
    tempCue->setTotalTime(oldTotalTime - oldTime + value.toDouble()); // update temps
    break;
  case Wait:
   tempSend->setTimewait(value.toDouble());
   tempCue->setTotalTime(oldTotalTime - oldTimeWait + value.toDouble()); //update temps
   break;
  case Note: tempSend->setNoteSend(value.toString()); break;
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
      case Note: return QString("Note");
      default: return QVariant(); break;
      }
    }
    if (orientation == Qt::Vertical)
    {
      if (isRowCue(section))
      {
        OscCue *osccue = getOscCue(getCueId(section) - 1);
        QString value = QString("CUE %1 - ").arg(getCueId(section));
        value += osccue->getNoteCue();
//        return QString("CUE %1").arg(getCueId(section));
        return value;
      }
      return QString("send %1 -> ").arg(getSendId(section));
    }
//    return QVariant();
  }
  if (role == Qt::BackgroundRole)
  {
    if (orientation == Qt::Vertical && isRowCue(section))
    {
      QBrush yellowColor(QColor("#B8BF7E"));
      return yellowColor;
    }
  }
  if (role == Qt::TextAlignmentRole && orientation == Qt::Vertical && !isRowCue(section)) return Qt::AlignRight;
  return QVariant();
}

Qt::ItemFlags OscCueList::flags(const QModelIndex &index) const
{
  int cueCount = getOscCueCount();
  int lineCount = rowCount();
  int row = index.row();
  int col = index.column();
  bool isCue = isRowCue(row);

  if (cueCount && index.isValid() && row > -1 && row < lineCount && !isCue)
  {
    OscSend *tempSend = getOscCue(getSendCueId(row) - 1)->getOscSend(getSendId(row) - 1);
    champMM champ = tempSend->getChamp();
    if (col == Champ || col == Wait || col == Note) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    if (champ == P_NAME) {if (col == P_name || col == P_Id) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ == P_REWIND) {if (col == P_Id) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ == P_COLOR) {if (col == Color || col == P_Id) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ == P_OPACITY) {if (col == P_Id || col == P_opac) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ == P_VOLUME) {if (col == P_Id || col == Vol) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ == P_RATE) {if (col == P_Id || col == Rate) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ == P_URI) {if (col == Uri || col == P_Id) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ == M_NAME) {if (col == M_name || col == M_Id) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ == M_OPACITY) {if (col == M_Id || col == M_opac) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ == M_VISIBLE) {if (col == M_Id || col == Visible) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ == M_SOLO) {if (col == M_Id || col == Solo) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ == M_LOCK) {if (col == M_Id || col == Lock) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ == M_DEPTH) {if (col == M_Id || col == Depth) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ == P_XFADE) {if (col == P_Id || col == P_Id2 || col == Time) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ == P_FADE) {if (col == P_Id || col == Fade_In || col == Time) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ == R_P_NAME) {if (col == P_name || col == P_name2)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ == R_P_REWIND) {if (col == P_name) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ ==  R_P_OPACITY) {if (col == P_name || col == P_opac) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ ==  R_P_VOLUME) {if (col == P_name || col == Vol) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ ==  R_P_RATE) {if (col == P_name || col == Rate) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ ==  R_P_URI) {if (col == P_name || col == Uri) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ ==  R_P_COLOR) {if (col == P_name || col == Color) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ ==  R_M_NAME) {if (col == M_name || col == M_name2) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ ==  R_M_OPACITY) {if (col == M_name || col == M_opac) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ ==  R_M_VISIBLE) {if (col == M_name || col == Visible) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ ==  R_M_SOLO) {if (col == M_name || col == Solo) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ ==  R_M_LOCK) {if (col == M_name || col == Lock) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ ==  R_M_DEPTH) {if (col ==M_name || col == Depth) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ ==  R_P_FADE) {if (col == P_name || col == Fade_In || col == Time) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
    if (champ ==  R_P_XFADE) {if (col == P_name || col == P_name2 || col == Time) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  }
  if (cueCount && index.isValid() && row > -1 && row < lineCount && isCue)
  {
    if (col == Note) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    if (col == Wait) return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
  }
  return QAbstractItemModel::flags(index);
}

OscCue *OscCueList::getOscCue(const int vectAt) const
{
  if (vectAt < 0 || vectAt > getOscCueCount() - 1)
  {
//    auto *voidCue = new OscCue();
    qDebug() << "OscCuelist::getOscCue badly returned... problem";
    return nullptr;
  }
  return v_listCue.at(vectAt);
}

int OscCueList::getOscCueCount() const
{
  return v_listCue.size();
}

bool OscCueList::isRowCue(const int row) const
{
  int cueCount = getOscCueCount();
  if (!cueCount) return false;
  int count = 0; // count pour repérer les cue dans la boucle for d'après
  for (int i = 0; i < cueCount; i++)
  {
    if (row == count) return true;
    count += getOscCue(i)->oscSendCount() + 1;
  }
  return false;
}

int OscCueList::getCueId(const int row) const // retourne -1 si problème
{
  int cueCount = getOscCueCount();
  if (!isRowCue(row) || !cueCount || row > rowCount() - 1 || row < 0)
  {
    qDebug() << "OscCueList::getCueId badly returned... problem";
    return -1;
  }
  int count = 0;
  for (int i = 0; i < cueCount; i++)
  {
    if (row == count)
    {
//      qDebug() << "OscCueList::getCueId returned" << i + 1;
      return i + 1;
    }
    count += getOscCue(i)->oscSendCount() + 1;
  }
  qDebug() << "OscCueList::getCueId badly returned... problem";
  return -1;
}

int OscCueList::getSendId(const int row) const // retourne -1 si problème
{
  if (isRowCue(row) || row > rowCount() - 1 || row < 0)
  {
    qDebug() << "OscCueList::getSendId returned -1... problem";
    return -1;
  }
  int count = 0;
  for (int i = 0; i < getSendCueId(row) - 1; i++)
  {
    count += getOscCue(i)->oscSendCount() +1;
  }
//  qDebug() << "OscCueList::getSendId returned" << row - count;
  return row - count;
}

int OscCueList::getSendCueId(const int row) const // retourne -1 si problème
{
  if (isRowCue(row) || row > rowCount() - 1 || row < 0)
  {
    qDebug() << "OscCueList::getSendCueId returned -1... problem";
    return -1;
  }
  for (int i = row; i > -1; i--)
  {
    if (isRowCue(i))
    {
//      qDebug() << "OscCueList::getSendCueId returned" << getCueId(i) << "for row" << row;
      return getCueId(i);
    }
  }
  qDebug() << "OscCueList::getSendCueId returned -1... problem";
  return -1;
}

int OscCueList::getRowCueFromCueId(int cueId) const
{
  if (cueId < 1 || cueId > v_listCue.size()) return -1; // retourne -1 si problème
  int count = 0;
  cueId--; // là ça marche...
  for (int i = 0; i < cueId; i++)
  {
    count += 1 + getOscCue(i)->oscSendCount();
  }
  return count;
}

int OscCueList::getLastCueRow() const // retourne -1 si problème
{
  int lastCueRow = -1;
  for (int i = 0; i < rowCount(); i++)
  {
    if (isRowCue(i)) lastCueRow = i;
  }
  if (lastCueRow == -1) qDebug() << "OscCueList::getLasCueRow returned -1";
  return lastCueRow;
}

OscCue *OscCueList::retOscCueFromFileLine(QStringList &lineToken)
{
  QString m_noteCue = "";
  // load parsed data to model accordingly
  for (int j = 0; j < lineToken.size(); j++)
  {
    QString val = lineToken.at(j);
    val = val.trimmed();
//    qDebug() << val << ", ";
    QVariant value(val);
    switch(j)
    {
    case Note - 1: m_noteCue = value.toString();
    }
  }
//  qDebug() << "Salut mec, le m_noteCue renvoie" << m_noteCue;
  OscCue *osccue = new OscCue(this, 0, m_noteCue);
  return osccue;
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
  QString m_noteSend = "";

  // load parsed data to model accordingly
  for (int j = 0; j < lineToken.size(); j++)
  {
    QString val = lineToken.at(j);
    val = val.trimmed();
//    qDebug() << val << ", ";
    QVariant value(val);
    switch(j)
    {
    case Champ: m_champInt = OscSend::getChampFromString(val); break;
    case P_name: m_p_name = value.toString(); break;
    case P_name2: m_p_name2 = value.toString(); break;
    case Uri: m_p_uri = value.toString(); break;
    case Color: m_p_color = value.toString(); break;
    case P_Id: m_p_ID1 = value.toInt(); break;
    case P_Id2: m_p_ID2 = value.toInt(); break;
    case Rate: m_p_rate = value.toInt(); break;
    case P_opac: m_p_opacity = value.toInt(); break;
    case Vol: m_p_volume = value.toInt(); break;
    case M_name: m_m_name = value.toString(); break;
    case M_name2: m_m_name2 = value.toString(); break;
    case M_Id: m_m_ID1 = value.toInt(); break;
    case M_opac: m_m_opacity = value.toInt(); break;
    case Visible: m_m_isvisible = value.toBool(); break;
    case Solo: m_m_issolo = value.toBool(); break;
    case Lock: m_m_islocked = value.toBool(); break;
    case Depth: m_m_depth = value.toInt(); break;
    case Fade_In: m_isfadein = value.toBool(); break;
    case Time: m_time = value.toDouble(); break;
    case Wait: m_timewait = value.toDouble(); break;
    case Note: m_noteSend = value.toString(); break;
    default: break;
    }
  m_champ = static_cast<champMM>(m_champInt);
  }
//  qDebug()<< "champ dans l'oscsend qui retourne" << m_champ;

  auto *oscsend = new OscSend(
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
        m_timewait,
        m_noteSend
        );

  return oscsend;
}

void OscCueList::addCue(OscCue *osccue)
{
  QModelIndex indexTemp = QModelIndex();
  beginInsertRows(indexTemp, rowCount(), rowCount());
  v_listCue.append(osccue);
  endInsertRows();
//  qDebug() << "cue added";
}

void OscCueList::insertCue(OscCue *osccue, int rowCue)
{
  if (rowCue < 0 || rowCue > rowCount() - 1 || !isRowCue(rowCue)) return; // C'est aux meth de vérifier
  QModelIndex indexTemp = QModelIndex();
  int cueId = getCueId(rowCue); // On choppe l'ID de la cue
  if (cueId == 1)
  {
    beginInsertRows(indexTemp, 1, 1);
    v_listCue.insert(0, osccue);
    endInsertRows();
//    qDebug() << "cue inserted";
  }
  else
  {
    beginInsertRows(indexTemp, rowCue, rowCue);
    v_listCue.insert(cueId - 1, osccue);
    endInsertRows();
//    qDebug() << "cue inserted";
  }
}

void OscCueList::moveCuePrev(int rowCue)
{
  if (rowCue < 1 || rowCue > rowCount() - 1 || !isRowCue(rowCue)) return; // C'est aux meth de vérifier
  QModelIndex indexTemp = QModelIndex();
  int row = getCueId(rowCue) - 1; // row = pointeur dans v_listCue
  beginMoveRows(indexTemp, rowCue, rowCue, indexTemp, rowCue - 1);
  v_listCue.move(row, row - 1);
  endMoveRows();
}

void OscCueList::removeCue(int rowCue)
{
  if (rowCue < 0 || rowCue > rowCount() - 1 || !isRowCue(rowCue)) return; // C'est aux meth de vérifier
  QModelIndex indexTemp = QModelIndex();
  OscCue *tempCue = getOscCue(getCueId(rowCue) - 1); // On extrait la cue pour connaitre sa taille
  beginRemoveRows(indexTemp, rowCue, rowCue + tempCue->oscSendCount());
  v_listCue.remove(getCueId(rowCue) - 1);
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
//  qDebug() << "All cue removed";
}

void OscCueList::addSend(OscSend *oscsend, int rowCue)
{
  if (!isRowCue(rowCue)) return; //c'est aux méthodes appelantes de vérifier
  QModelIndex indexTemp = QModelIndex();
  OscCue *tempCue = v_listCue.at(getCueId(rowCue) - 1);
  int row = rowCue + tempCue->oscSendCount();
  beginInsertRows(indexTemp, row + 1, row  + 1);
  tempCue->addOscSend(oscsend);
  endInsertRows();
}

void OscCueList::insertSend(OscSend *oscsend, int rowSend)
{
  if (rowSend < 0 || rowSend > rowCount() || isRowCue(rowSend)) return; // C'est aux meth de vérifier
  QModelIndex indexTemp = QModelIndex();
  int cue = getSendCueId(rowSend) - 1;
  OscCue *tempCue = v_listCue.at(cue);
  beginInsertRows(indexTemp, rowSend + 1, rowSend +1);
  tempCue->insertOscSend(getSendId(rowSend), oscsend);
  endInsertRows();
}

void OscCueList::moveSendPrev(int rowSend)
{
  if (rowSend < 2 || rowSend > rowCount() || isRowCue(rowSend)) return; // C'est aux meth de vérifier
  QModelIndex indexTemp = QModelIndex();
  int cue = getSendCueId(rowSend) - 1; // pointeur dans v_listCue
  if (getSendId(rowSend) == 1) // Si c'est le 1er send on le met à la fin de la cue d'avant
  {
    if (cue == 0) return; // Si y a pas de cue avant on fait rien
    OscCue *tempCue = getOscCue(cue); // On pointe la cue actuelle
    OscSend *tempSend = tempCue->getOscSend(0); // on prend le 1er
    OscCue *tempCuePrev = getOscCue(cue -1); // On pointe la cue d'avant
    beginMoveRows(indexTemp, rowSend, rowSend, indexTemp, rowSend - 2);
    tempCuePrev->addOscSend(tempSend); // On met le send à la fin
    tempCue->removeOscSend(0); // on l'efface dans l'ancienne cue
    endMoveRows();
  }
  else
  {
    OscCue *tempCue = getOscCue(cue);
    beginMoveRows(indexTemp, rowSend, rowSend, indexTemp, rowSend - 1);
    tempCue->moveOscSendPrev(getSendId(rowSend) - 1);
    endMoveRows();
  }
}

void OscCueList::moveSendNext(int rowSend)
{
  if (rowSend > rowCount() - 2 || isRowCue(rowSend) || rowSend < 1) return; // C'est aux meth de vérifier
  QModelIndex indexTemp = QModelIndex();
  int cue = getSendCueId(rowSend) - 1; // pointeur dans v_listCue
  int send = getSendId(rowSend) - 1; // pointeur dans v_listOscSend
  if (isRowCue(rowSend + 1)) // Si le row d'après est une cue
  {
    OscCue *tempCue = getOscCue(cue); // On pointe la cue actuelle
    OscSend *tempSend = tempCue->getOscSend(send);
    OscCue *tempCueNext = getOscCue(cue + 1);
    beginMoveRows(indexTemp, rowSend, rowSend, indexTemp, rowSend + 2);
    tempCueNext->insertOscSend(0, tempSend);
    tempCue->removeOscSend(tempCue->oscSendCount() - 1);
    endMoveRows();
  }
  else // le row d'après est un send
  {
    rowSend++;
    OscCue *tempCue = getOscCue(cue);
    beginMoveRows(indexTemp, rowSend, rowSend, indexTemp, rowSend - 1);
    tempCue->moveOscSendPrev(getSendId(rowSend) - 1);
    endMoveRows();
  }
}

void OscCueList::removeSend(int rowSend)
{
  if (rowSend < 0 || rowSend > rowCount() || isRowCue(rowSend)) return; // C'est aux meth de vérifier
  QModelIndex indexTemp = QModelIndex();
  int cue = getSendCueId(rowSend) - 1;
  OscCue *tempCue = v_listCue.at(cue);
  beginRemoveRows(indexTemp, rowSend, rowSend);
  tempCue->removeOscSend(getSendId(rowSend) - 1);
  endRemoveRows();
}

void OscCueList::removeAllSend(int cueRow)
{
  if (cueRow < 0 || cueRow > rowCount() || !isRowCue(cueRow)) return; // C'est aux meth de vérifier
  int cue = getCueId(cueRow) - 1;
  OscCue *tempCue = v_listCue.at(cue);
  int rows = tempCue->oscSendCount();
  for (int i = 0; i < rows; i++)
  {
    removeSend(cueRow + 1);
  }
}

//***************************************************************************

OscCueListProxy::OscCueListProxy(OscCueList *osccuelist, QObject *parent):
  QSortFilterProxyModel(parent),
  m_oscCueList(osccuelist)
{}

QVariant OscCueListProxy::data(const QModelIndex &index, int role) const
{
  int row = index.row();
  int col = index.column();
//  QBrush salmonColor(QColor("#59271E"));
  if (!m_oscCueList->isRowCue(row) && index.flags().testFlag(Qt::ItemIsEditable) && index.isValid() && row > -1
      && row < m_oscCueList->rowCount() && col == Uri)
  {
    OscCue *tempCue = m_oscCueList->getOscCue(m_oscCueList->getSendCueId(row) - 1);
    OscSend *tempSend = tempCue->getOscSend(m_oscCueList->getSendId(row) - 1);
    switch (role)
    {
    case Qt::DisplayRole:
      QString tempString = tempSend->getP_uri();
      for (int i = tempString.size() - 1; i > 0; --i)
      {
        if (tempString.at(i) == QChar('/'))
        {
          return tempString = tempString.right(tempString.size() - i - 1); break;
        }
      }
      return tempString; // pour voir si ça marche
      break;
    }
  }
  return QSortFilterProxyModel::data(index, role);
}
