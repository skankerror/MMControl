#ifndef MMSTATE_H
#define MMSTATE_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QColor>

class MMState : public QObject
{
  Q_OBJECT
public:
  explicit MMState(QObject *parent = nullptr);

signals:

public slots:

private:
  QVector<QString *> v_uri;
  QVector<int > v_rate;
  QVector <int> v_p_opacity;
  QVector<int> v_m_opacity;
  QVector<bool> v_isSolo;
  QVector<bool> v_isVisible;
  bool pausePlay;
  // bool isRewind;
  QVector<QColor*> v_color;
};

#endif // MMSTATE_H
