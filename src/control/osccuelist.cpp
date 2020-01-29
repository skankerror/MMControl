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
  if (!index.isValid()) return 0;
  int count = v_listCue.size();
  for (int i = 0; i < v_listCue.size(); i++)
  {
    count += getOscCue(i)->oscSendCount();
  }
  return count;
}

int OscCueList::columnCount(const QModelIndex &index) const
{
  return index.isValid() ? 0 : Count;
}

QVariant OscCueList::data(const QModelIndex &index, int role) const
{
  // Si y'a un blème on renvoie un QVariant vide
  if (!index.isValid() || index.row() < 0 || !(index.flags().testFlag(Qt::ItemIsEditable)) || index.row() > rowCount()) return QVariant();

  int count = 0; // count pour repérer les cue dans la boucle for d'après
  int row = index.row();
  int col = index.column();
  QBrush salmonColor(QColor("#59271E"));

  for (int i = 0; i < v_listCue.size(); i++) // un for ou un do while ?
  {
    if (row == count) // Si c'est une cue...
    {
      if (col == Cue) return QString("Cue %1").arg(i + 1); // On met le nom par défaut de la cue dans la col 0
      // Rajouter les roles pour améliorer la vue de la cue (mettre temps total, couleurs...)
      else return QVariant();
    }
    else
    {
      if (row < count) // c'est bien un send. Au-dessus de count on laisse pour la boucle d'après
      {
//        count += getOscCue(i)->oscSendCount() + 1;
        if (col == Cue) return QString("Send %1").arg(row - count); // On met le nom par défaut dans la col 0
        OscSend *tempSend = getOscCue(count)->getOscSend(row - count -1); // On prend l'OscSend correspondant
        switch (role)
          {
          case Qt::DisplayRole: case Qt::EditRole:
            switch (col)
            {
            case Champ:
              switch(tempSend->getChamp())
              {
              case NOOP: return QString("NOOP"); break;
              case PLAY: return QString("PLAY"); break;
              case PAUSE: return QString("PAUSE"); break;
              case REWIND: return QString("REWIND"); break;
              case QUIT: return QString("QUIT"); break;
              case P_NAME: return QString("P_NAME"); break;
              case P_REWIND: return QString("P_REWIND"); break;
              case P_OPACITY: return QString("P_OPACITY"); break;
              case P_VOLUME: return QString("P_VOLUME"); break;
              case P_RATE: return QString("P_RATE"); break;
              case P_URI: return QString("P_URI"); break;
              case P_COLOR: return QString("P_COLOR"); break;
              case M_NAME: return QString("M_NAME"); break;
              case M_OPACITY: return QString("M_OPACITY"); break;
              case M_VISIBLE: return QString("M_VISIBLE"); break;
              case M_SOLO: return QString("M_SOLO"); break;
              case M_LOCK: return QString("M_LOCK"); break;
              case M_DEPTH: return QString("M_DEPTH"); break;
              case P_XFADE: return QString("P_XFADE"); break;
              case P_FADE: return QString("P_FADE"); break;
              case R_P_NAME: return QString("R_P_NAME"); break;
              case R_P_REWIND: return QString("R_P_REWIND"); break;
              case R_P_OPACITY: return QString("R_P_OPACITY"); break;
              case R_P_VOLUME: return QString("R_P_VOLUME"); break;
              case R_P_RATE: return QString("R_P_RATE"); break;
              case R_P_URI: return QString("R_P_URI"); break;
              case R_P_COLOR: return QString("R_P_COLOR"); break;
              case R_M_NAME: return QString("R_M_NAME"); break;
              case R_M_OPACITY: return QString("R_M_OPACITY"); break;
              case R_M_VISIBLE: return QString("R_M_VISIBLE"); break;
              case R_M_SOLO: return QString("R_M_SOLO"); break;
              case R_M_LOCK: return QString("R_M_LOCK"); break;
              case R_M_DEPTH: return QString("R_M_DEPTH"); break;
              case R_P_FADE: return QString("R_P_FADE"); break;
              case R_P_XFADE: return QString("R_P_XFADE"); break;
              default: break;
              }
              break;
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
            if (tempSend->getTimewait() > 0) return QBrush(Qt::Dense4Pattern);
          }
      }
//      count += getOscCue(i)->oscSendCount() + 1;
    }
    count += getOscCue(i)->oscSendCount() + 1; // On incrémente pour la boucle d'après.
  }


  if (role == Qt::TextAlignmentRole) return Qt::AlignCenter;
  if (role == Qt::ForegroundRole){/* à voir*/}
  if (role == Qt::SizeHintRole){/* à voir*/}

  return QVariant();
}

bool OscCueList::setData(const QModelIndex &index, const QVariant &value, int role)
{
  Q_UNUSED(role);
  if (!index.isValid() || index.row() < 0 || !(index.flags().testFlag(Qt::ItemIsEditable)) || index.row() > rowCount()) return false;
  int count = 0; // count pour repérer les cue dans la boucle for d'après
  int row = index.row();
  int col = index.column();

  for (int i = 0; i < v_listCue.size(); i++)
  {
    if (row < count) // c'est bien un send. Au-dessus de count on laisse pour la boucle d'après
    {
      count += getOscCue(i)->oscSendCount() + 1;
      OscSend *tempSend = getOscCue(count)->getOscSend(row - count -1);

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

    }

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
      case 0: return QString("Champ");
      case 1: return QString("P_name");
      case 2: return QString("p_name2");
      case 3: return QString("Uri");
      case 4: return QString("Color");
      case 5: return QString("P_Id");
      case 6: return QString("P_Id2");
      case 7: return QString("Rate");
      case 8: return QString("P_opac");
      case 9: return QString("Vol");
      case 10: return QString("M_name");
      case 11: return QString("M_name2");
      case 12: return QString("M_Id");
      case 13: return QString("M_opac");
      case 14: return QString("Visible");
      case 15: return QString("Solo");
      case 16: return QString("Lock");
      case 17: return QString("Depth");
      case 18: return QString("Fade_In");
      case 19: return QString("Time");
      case 20: return QString("Wait");
      }
    }
    if (orientation == Qt::Vertical)
    {
//      int cueCount = v_listCue.size();
      for (int i = 0; i < v_listCue.size(); i++)
      {
        if (section == 0) return QString("cue 1"); // ?
        // trouver pour rajouter event % à l'intérieur des cue...
//        else return QString("cue %1").arg(section + 1 - v_listCue.at(i)->v_listOscSend.size()); // A voir.... truc dans ce style
      }
      return QString("cue %1").arg(section+1);
    }
  }
  return QVariant();
}

Qt::ItemFlags OscCueList::flags(const QModelIndex &index) const
{

  OscSend *tempSend = v_listCue.at(index.row())->getOscSend(0); // mettre
  int col = index.column();
  champMM champ = tempSend->getChamp();

  if (col == 0 || col == 20) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
//  else if (tempSend->m_iswaiting == false && col == 19) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
  else if (champ == P_NAME) {if (col == 1 || col == 5) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == P_REWIND) {if (col == 5) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == P_REWIND) {if (col == 5) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == P_COLOR) {if (col == 4 || col == 5)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == P_OPACITY) {if (col == 5 || col == 8)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == P_VOLUME) {if (col == 5 || col == 9)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == P_RATE) {if (col == 5 || col == 7)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == P_URI) {if (col == 3 || col == 5)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == M_NAME) {if (col == 10 || col == 12)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == M_OPACITY) {if (col == 12 || col == 13)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == M_VISIBLE) {if (col == 12 || col == 14)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == M_SOLO) {if (col == 12 || col == 15)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == M_LOCK) {if (col == 12 || col == 16)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == M_DEPTH) {if (col == 12 || col == 17)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == P_XFADE) {if (col == 5 || col == 6 || col == 19)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == P_FADE) {if (col == 5 || col == 18 || col == 19)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == R_P_NAME) {if (col == 1 || col == 2)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ == R_P_REWIND) {if (col == 1) return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_P_OPACITY) {if (col == 1 || col == 8)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_P_VOLUME) {if (col == 1 || col == 9)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_P_RATE) {if (col == 1 || col == 7)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_P_URI) {if (col == 1 || col == 3)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_P_COLOR) {if (col == 1 || col == 4)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_M_NAME) {if (col == 10 || col == 11)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_M_OPACITY) {if (col == 10 || col == 13)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_M_VISIBLE) {if (col == 10 || col == 14)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_M_SOLO) {if (col == 10 || col == 15)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_M_LOCK) {if (col == 10 || col == 16)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_M_DEPTH) {if (col ==10 || col == 17)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_P_FADE) {if (col == 1 || col == 18 || col == 19)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}
  else if (champ ==  R_P_XFADE) {if (col == 1 || col == 2 || col == 19)  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;}

  return QAbstractItemModel::flags(index);
}

bool OscCueList::isRowCue(const int row) const
{
  int count = 0; // count pour repérer les cue dans la boucle for d'après
  for (int i = 0; i < v_listCue.size(); i++)
  {
    if (row == count) return true;
    count += getOscCue(i)->oscSendCount() + 1;
  }
  return false;
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
  Q_UNUSED(osccue)
  QModelIndex indexTemp = QModelIndex();
  beginInsertRows(indexTemp, v_listCue.size(), v_listCue.size());
//  v_listCue.append(oscsend);
  endInsertRows();

  qDebug() << "cue added";
}

void OscCueList::insertCue(OscCue *osccue, int row)
{
  Q_UNUSED(osccue)
  QModelIndex indexTemp = QModelIndex();
  beginInsertRows(indexTemp, row + 1, row + 1);
//  v_listCue.insert(row + 1, oscsend);
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
  int rows = rowCount();
  for (int i = 0; i < rows; i++)
  {
    removeCue(0);
  }

  qDebug() << "All cue removed";
}

