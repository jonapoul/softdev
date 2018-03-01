#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
class QPushButton;
class QMenu;
class QActionGroup;
class QAction;
class QLabel;

class GameWindow : public QMainWindow {
  Q_OBJECT

public:
  GameWindow();

protected:
#ifndef QT_NO_CONTEXTMENU
   void contextMenuEvent(QContextMenuEvent *event) override;
#endif

private:
   QPushButton * TestButton;
   void createActions();
   void createMenus();
   QMenu * FileMenu;
   QMenu * EditMenu;
   QMenu * FormatMenu;
   QMenu * HelpMenu;
   QActionGroup * AlignmentGroup;
   QAction * NewAction;
   QAction * OpenAction;
   QAction * SaveAction;
   QAction * PrintAction;
   QAction * ExitAction;
   QAction * UndoAction;
   QAction * RedoAction;
   QAction * CutAction;
   QAction * CopyAction;
   QAction * PasteAction;
   QAction * BoldAction;
   QAction * ItalicAction;
   QAction * LeftAlignAction;
   QAction * RightAlignAction;
   QAction * JustifyAction;
   QAction * CenterAction;
   QAction * SetLineSpacingAction;
   QAction * SetParagraphSpacingAction;
   QAction * AboutAction;
   QAction * AboutQtAction;
   QLabel * InfoLabel;

signals:

public slots:

private slots:
   void newFile();
   void open();
   void save();
   void print();
   void undo();
   void redo();
   void cut();
   void copy();
   void paste();
   void bold();
   void italic();
   void leftAlign();
   void rightAlign();
   void justify();
   void center();
   void setLineSpacing();
   void setParagraphSpacing();
   void about();
   void aboutQt();

};

#endif // GAMEWINDOW_H
