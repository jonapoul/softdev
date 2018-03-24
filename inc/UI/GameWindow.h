#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "config.h"

#ifdef ENABLE_QT_UI

#include <QMainWindow>

class QMenu;
class QActionGroup;
class QAction;
class QLabel;
class QCloseEvent;
class TitleScreen;

class GameEngine;

class GameWindow : public QMainWindow {
  Q_OBJECT

public:
   explicit GameWindow();
   ~GameWindow();

   void criticalMessage(char const * const message);
   void warningMessage(char const * const message);
   void informationMessage(char const * const message);

   QFont robotoFont;
   QFont kronaFont;

protected:
#ifndef QT_NO_CONTEXTMENU
   void contextMenuEvent(QContextMenuEvent * event) override;
#endif
   void closeEvent(QCloseEvent * event) override;

private:
   void createActions();
   void createMenus();
   void loadFonts();
   bool shouldExit();

   TitleScreen * titleScreen;

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

#endif // ENABLE_QT_UI

#endif // GAMEWINDOW_H
