#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
//#include <QPixmap>
#include "mainwindow.h"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QString locale = QLocale::system().name().section('_', 0, 0);
  QTranslator translator;
  translator.load(QString("qt_")+ locale,
                  QLibraryInfo::location(QLibraryInfo::TranslationsPath));
  app.installTranslator(&translator);

//  QIcon icon("/:graphics/Icon");
  MainWindow win;
//  win.setWindowIcon(icon);
  win.show();

  return app.exec();
}
