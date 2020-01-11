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

#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "mainwindow.h"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

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

  MainWindow win;
  win.show();

  return app.exec();
}
