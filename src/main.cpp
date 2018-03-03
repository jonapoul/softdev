#include <QApplication>
#include <QFile>
#include <QFontDatabase>
#include "GameWindow.h"
#include "Dialog.h"

int main(int argc, char **argv) {
  QApplication app (argc, argv);
  QCoreApplication::setApplicationName("softdev");
  QCoreApplication::setApplicationVersion(QT_VERSION_STR);

  QFile styleSheetFile("resources/stylesheet.qss");                                                  
  styleSheetFile.open(QFile::ReadOnly);
  QString styleSheetString = QLatin1String(styleSheetFile.readAll());
  app.setStyleSheet(styleSheetString);

  QFontDatabase::addApplicationFont("qrc:///fonts/Roboto.ttf");
  QFontDatabase::addApplicationFont("qrc:///fonts/KronaOne.ttf");

#if 1
  GameWindow * window = new GameWindow;
  window->show();
#else
  Dialog * dialog = new Dialog;
  dialog->show();
#endif

  return app.exec();
}
