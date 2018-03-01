#include "GameWindow.h"
#include <QWidget>
#include <QPushButton>
#include <QMenu>
#include <QActionGroup>
#include <QAction>
#include <QLabel>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QContextMenuEvent>
#include <QMenuBar>

GameWindow::GameWindow() {
   /* Fix window size */
   // this->setFixedSize(1000, 500);
   // this->m_button = new QPushButton("Hello World!", this);
   // this->m_button->setGeometry(10, 10, 100, 50);

   QWidget * widget = new QWidget;
   this->setCentralWidget(widget);

   QWidget * topFiller = new QWidget;
   topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

   this->InfoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to invoke a context menu</i>"));
   this->InfoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
   this->InfoLabel->setAlignment(Qt::AlignCenter);

   QWidget * bottomFiller = new QWidget;
   bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

   QVBoxLayout * layout = new QVBoxLayout;
   layout->setMargin(5);
   layout->addWidget(topFiller);
   layout->addWidget(this->InfoLabel);
   layout->addWidget(bottomFiller);
   widget->setLayout(layout);

   this->createActions();
   this->createMenus();

   QString const message = tr("A context menu is available by right-clicking");
   this->statusBar()->showMessage(message);

   this->setWindowTitle(tr("Menus"));
   this->setMinimumSize(160, 160);
   this->resize(480, 320);
}

void GameWindow::createActions() {
   this->NewAction = new QAction(tr("&New"), this);
   /* Set Ctrl+N as shortcut */
   this->NewAction->setShortcuts(QKeySequence::New);
   this->NewAction->setStatusTip(tr("Create a new file"));
   connect(NewAction, &QAction::triggered, this, &GameWindow::newFile);
   
   /* Set up the alignment options, default to left align */
   this->AlignmentGroup = new QActionGroup(this);
   this->AlignmentGroup->addAction(LeftAlignAction);
   this->AlignmentGroup->addAction(RightAlignAction);
   this->AlignmentGroup->addAction(JustifyAction);
   this->AlignmentGroup->addAction(CenterAction);
   this->LeftAlignAction->setChecked(true);
}

void GameWindow::createMenus() {
   this->FileMenu = menuBar()->addMenu(tr("&File"));
   this->FileMenu->addAction(NewAction);
   this->FileMenu->addAction(OpenAction);
   this->FileMenu->addAction(SaveAction);
   this->FileMenu->addAction(PrintAction);
   this->FileMenu->addSeparator();
   this->FileMenu->addAction(ExitAction);

   this->EditMenu = menuBar()->addMenu(tr("&Edit"));
   this->EditMenu->addAction(UndoAction);
   this->EditMenu->addAction(RedoAction);
   this->EditMenu->addSeparator();
   this->EditMenu->addAction(CutAction);
   this->EditMenu->addAction(CopyAction);
   this->EditMenu->addAction(PasteAction);
   this->EditMenu->addSeparator();

   this->HelpMenu = menuBar()->addMenu(tr("&Help"));
   this->HelpMenu->addAction(AboutAction);
   this->HelpMenu->addAction(AboutQtAction);

   this->FormatMenu = EditMenu->addMenu(tr("&Format"));
   this->FormatMenu->addAction(BoldAction);
   this->FormatMenu->addAction(ItalicAction);
   this->FormatMenu->addSeparator()->setText(tr("Alignment"));
   this->FormatMenu->addAction(LeftAlignAction);
   this->FormatMenu->addAction(RightAlignAction);
   this->FormatMenu->addAction(JustifyAction);
   this->FormatMenu->addAction(CenterAction);
   this->FormatMenu->addSeparator();
   this->FormatMenu->addAction(SetLineSpacingAction);
   this->FormatMenu->addAction(SetParagraphSpacingAction);
}

#ifndef QT_NO_CONTEXTMENU
void GameWindow::contextMenuEvent(QContextMenuEvent * event) {
   QMenu menu(this);
   menu.addAction(CutAction);
   menu.addAction(CopyAction);
   menu.addAction(PasteAction);
   menu.exec(event->globalPos());
}
#endif