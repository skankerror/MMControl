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

  app.setStyleSheet("QSlider::groove:vertical {"
                      "background: red;"
                      "position: absolute;" /* absolutely position 4px from the left and right of the widget. setting margins on the widget should work too... */
                      "left: 6px; right: 6px;"
                  "}"

                  "QSlider::handle:vertical {"
                      "height: 15px;"
                      "background: blue;"
                      "width: 40px;"
                      "margin: 0 -40px;" /* expand outside the groove */
                  "}"

                  "QSlider::add-page:vertical {"
                      "background: black;"
                  "}"

                  "QSlider::sub-page:vertical {"
                      "background: white;"
                  "}");

//  app.setStyleSheet(
//      "Slider::groove:vertical  {"
//      "border:none;"
//      "margin-left: 30px;"
//      "margin-right: 30px;"
//      "width: 10px;"
//      "}"

//      "QSlider::sub-page  {"
//      "background: rgb(164, 192, 2);"
//      "}"

//      "QSlider::add-page {"
//      "background: rgb(70, 70, 70);"
//      "}"

//      "QSlider::handle  {"
//      "background: white;"
//      "border: 3px solid black;"
//      "width: 100px;" // **Change the width here**
//      "margin: -60px 0;"
//      "}");

//  app.setStyleSheet(
//        "QSlider::groove:vertical { background: transparent; width: 32px; } "

//        "QSlider::handle:vertical { "
//        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ddd, stop:0.45 #888, stop:0.50 #000, stop:0.55 #888, stop:1 #999);"
//        "border: 1px solid #5c5c5c;"
//        "border-radius: 4px; margin: 0 -40px; width : 80px; height: 20px; }"

//        "QSlider::handle:vertical:hover {"
//        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #eee, stop:0.45 #999, stop:0.50 #ff0000, stop:0.55 #999, stop:1 #ccc);"
//        "border: 1px solid #000; margin: 0 -40px; width : 80px; }"

//        "QSlider::add-page:vertical { background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #78d, stop: 1 #97CDEC );"
//        "border: 1px solid #5288A7; margin: 0 20px; }"

//        "QSlider::sub-page:vertical { background: QLinearGradient( x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #888, stop: 1 #ddd );"
//        "border: 1px solid #8E8A86; margin: 0 20px; }"

//        "QSlider::handle:vertical:disabled { background: QLinearGradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ddd, stop:0.45 #888, stop:0.50 #444, stop:0.55 #888, stop:1 #999);"
//        "border: 1px solid #666; }"

//        );

//  app.setStyleSheet(" QSlider::groove:vertical {"
////                    "border: 1px solid #999999;"
////                    "height: 2px;"
////                    "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 white);"
//                    "margin: -8px 0;"
//                    "}"
//                    "QSlider::handle:vertical {"
//                    "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b0b0b0, stop:1 white);"
//                    "border: 3px solid #5c5c5c;"
//                    "width: 5px;"
//                    "margin: -20px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */"
//                    "border-radius: 5px;"
//                "}");

  MainWindow win;
  win.show();

  return app.exec();
}
