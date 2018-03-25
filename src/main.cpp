#include "config.h"

#ifdef ENABLE_QT_UI
# include <QApplication>
# include <QFile>
# include <QFontDatabase>
# include "UI/GameWindow.h"
#endif

#include "Game/GameObject.h"
#include "Game/GameEngine.h"
#include "TestSuite.h"

#ifdef ENABLE_QT_UI

int main(int argc, char ** argv) {
   /* Initialise the Qt application */
   QApplication app (argc, argv);
   QCoreApplication::setApplicationName("softdev");
   QCoreApplication::setApplicationVersion(QT_VERSION_STR);

   /* Load the style sheet */
   QFile styleSheetFile("resources/stylesheet.qss");
   styleSheetFile.open(QFile::ReadOnly);
   QString styleSheetString = QLatin1String(styleSheetFile.readAll());
   app.setStyleSheet(styleSheetString);

   /* Plus a couple of fonts */
   QFontDatabase::addApplicationFont("qrc:///fonts/Roboto.ttf");
   QFontDatabase::addApplicationFont("qrc:///fonts/KronaOne.ttf");

   /* Launch the window and quit when it's closed*/
   GameWindow * window = new GameWindow;
   window->show();
   return app.exec();
}

#else // ENABLE_QT_UI

int main() {
   /* Build the game's backend */
   GameEngine * engine = new GameEngine();
   engine->init();
   printf("Finished loading players/squads/skill trees from file!\n");
   printf("Beginning the tests...\n");

   /* Offer a bunch of common actions */
   TestSuite tests(engine);
   tests.run();

   /* Delete all game objects */
   engine->deallocate();
   printf("Exited game successfully!\n");
   printf("Printing all GameObjects that still exist (should be none):\n");
   GameObject::printAllObjects();

   return 0;
}

#endif // ENABLE_QT_UI
