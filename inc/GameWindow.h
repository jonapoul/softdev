#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

class QMenu;
class QActionGroup;
class QAction;
class QLabel;
class QCloseEvent;

class GameEngine;

class GameWindow : public QMainWindow {
  Q_OBJECT

public:
   explicit GameWindow();
   ~GameWindow();

protected:
#ifndef QT_NO_CONTEXTMENU
   void contextMenuEvent(QContextMenuEvent * event) override;
#endif
   void closeEvent(QCloseEvent * event) override;

private:
   void createActions();
   void createMenus();
   bool shouldExit();

   void loadTitleScreen();
   void loadLoginScreen();
   void loadRegisterScreen();
   void looadSettingsScreen();

   QMenu * FileMenu;
   QMenu * EditMenu;
   QMenu * FormatMenu;
   QMenu * HelpMenu;
   QActionGroup * AlignmentGroup;
   QAction * NewAction;
   QAction * ExitAction;
   QAction * UndoAction;
   QAction * RedoAction;
   QAction * BoldAction;
   QAction * ItalicAction;
   QAction * LeftAlignAction;
   QAction * RightAlignAction;
   QAction * AboutAction;
   QAction * AboutQtAction;
   QLabel * InfoLabel;

   GameEngine * engine;

private slots:
   void NewFile();
   void Undo();
   void Redo();
   void Bold();
   void Italic();
   void LeftAlign();
   void RightAlign();
   void About();
   void AboutQt();

};

#endif // GAMEWINDOW_H
