#include "config.h"

#ifdef ENABLE_QT_UI
# include <QApplication>
# include <QFile>
# include <QFontDatabase>
# include "UI/GameWindow.h"
#endif

#include "Game/GameObject.h"
#include "Game/GameEngine.h"

int main() {

#ifdef ENABLE_QT_UI

   QApplication app (argc, argv);
   QCoreApplication::setApplicationName("softdev");
   QCoreApplication::setApplicationVersion(QT_VERSION_STR);

   QFile styleSheetFile("resources/stylesheet.qss");
   styleSheetFile.open(QFile::ReadOnly);
   QString styleSheetString = QLatin1String(styleSheetFile.readAll());
   app.setStyleSheet(styleSheetString);

   QFontDatabase::addApplicationFont("qrc:///fonts/Roboto.ttf");
   QFontDatabase::addApplicationFont("qrc:///fonts/KronaOne.ttf");

   GameWindow * window = new GameWindow;
   window->show();

   return app.exec();

#else // ENABLE_QT_UI

   GameEngine * engine = new GameEngine();
   engine->init();
   engine->deallocate();
   printf("Exited game successfully!\n\n");
   printf("Printing all GameObjects that currently exist:\n");
   GameObject::printAllObjects();

   return 0;

#endif // ENABLE_QT_UI
}
