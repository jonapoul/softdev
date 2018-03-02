#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include "GameWindow.h"

int main(int argc, char **argv) {
  QApplication app (argc, argv);
  QCoreApplication::setApplicationName("softdev");
  QCoreApplication::setApplicationVersion(QT_VERSION_STR);

  QFile qssFile("resources/stylesheet.qss");                                                  
  qssFile.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(qssFile.readAll());
  app.setStyleSheet(styleSheet);

  QFontDatabase::addApplicationFont("qrc:///fonts/Roboto.ttf");
  QFontDatabase::addApplicationFont("qrc:///fonts/KronaOne.ttf");

  GameWindow * window = new GameWindow;
  window->show();

  return app.exec();
}
