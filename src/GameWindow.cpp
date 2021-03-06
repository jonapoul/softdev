#include "config.h"

#ifdef ENABLE_QT_UI

#include <iostream>
#include <QtWidgets>

#include "UI/GameWindow.h"
#include "UI/TitleScreen.h"

#include "Game/GameEngine.h"
#include "Global.h"

/*

   This has been pretty much abandoned, it was taking ages and ages to learn Qt
   with any competence, and I had other project work to do.

   This was the most fleshed-out screen I had made though, which probably says
   a lot.

*/

GameWindow::GameWindow() {
   /* Build and display the title screen UI */
   createActions();
   createMenus();
   loadFonts();
#ifndef QT_NO_CONTEXTMENU
   QString initMessage = tr("A context menu is available by right-clicking");
   statusBar()->showMessage(initMessage);
#endif
   this->titleScreen = new TitleScreen(this);
   this->titleScreen->load();
   setCentralWidget(this->titleScreen);

   /* Limit the size, so we don't have to worry about responsive UI design */
   QSize const ScreenSize(1152, 648);
   setMinimumSize(ScreenSize);
   setMaximumSize(ScreenSize);

   /* Set up the backend game engine, load parameter files etc */
   this->engine = new GameEngine(this);
   engine->init();
}

GameWindow::~GameWindow() {
   this->engine->deallocate();
}

void GameWindow::criticalMessage(char const * const message) {
   QMessageBox::critical(this,
                         tr("Game Engine Critical Message"),
                         tr(message));
   QCoreApplication::quit();
}

void GameWindow::warningMessage(char const * const message) {
   QMessageBox::warning(this,
                        tr("Game Engine Warning Message"),
                        tr(message));
}

void GameWindow::informationMessage(char const * const message) {
   QMessageBox::information(this,
                            tr("Game Engine Information Message"),
                            tr(message));
}

   // QWidget * widget = new QWidget;
   // this->setCentralWidget(widget);

   // QWidget * topMargin = new QWidget;
   // topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

   // QString const label = tr("Choose a menu option, or right-click to invoke a context menu");
   // this->InfoLabel = new QLabel(label);
   // this->InfoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
   // this->InfoLabel->setAlignment(Qt::AlignCenter);
   // QFont roboto = QFont("Roboto", 20, 10);
   // InfoLabel->setFont(roboto);

   // QWidget * bottomFiller = new QWidget;
   // bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

   // QProgressBar * progressBar = new QProgressBar;
   // progressBar->setRange(0, 100);
   // progressBar->setValue(50);
   // progressBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   // progressBar->setAlignment(Qt::AlignCenter);

   // QSlider * slider = new QSlider;
   // slider->setOrientation(Qt::Horizontal);
   // slider->setRange(0, 100);
   // slider->setValue(50);
   // slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   // QObject::connect(slider, SIGNAL(valueChanged(int)),
   //                  progressBar, SLOT(setValue(int)));

   // QVBoxLayout * layout = new QVBoxLayout;
   // layout->setMargin(5);
   // layout->addWidget(topFiller);
   // layout->addWidget(slider);
   // layout->addWidget(this->InfoLabel);
   // layout->addWidget(progressBar);
   // layout->addWidget(bottomFiller);
   // widget->setLayout(layout);

void GameWindow::closeEvent(QCloseEvent * event) {
   if ( this->shouldExit() ) {
      event->accept();
   } else {
      event->ignore();
   }
}

bool GameWindow::shouldExit() {
   auto choice = QMessageBox::warning(this,
                                      QCoreApplication::applicationName(),
                                      tr("Do you want to quit?"),
                                      QMessageBox::Ok | QMessageBox::Cancel);
   return (choice == QMessageBox::Ok);
}

#ifndef QT_NO_CONTEXTMENU
void GameWindow::contextMenuEvent(QContextMenuEvent * event) {
   QMenu menu(this);
   menu.addAction(NewAction);
   menu.addAction(UndoAction);
   menu.addAction(RedoAction);
   menu.exec(event->globalPos());
}
#endif

void GameWindow::NewFile() {
   this->InfoLabel->setText(tr("Invoked <b>File|New</b>"));
   QMessageBox::information(this, tr("HURRR"), tr("DURRRRR"));
}

void GameWindow::Undo() {
   this->InfoLabel->setText(tr("Invoked <b>Edit|Undo</b>"));
}

void GameWindow::Redo() {
   this->InfoLabel->setText(tr("Invoked <b>Edit|Redo</b>"));
}

void GameWindow::Bold() {
   this->InfoLabel->setText(tr("Invoked <b>Edit|Format|Bold</b>"));
}

void GameWindow::Italic() {
   this->InfoLabel->setText(tr("Invoked <b>Edit|Format|Italic</b>"));
}

void GameWindow::LeftAlign() {
   this->InfoLabel->setText(tr("Invoked <b>Edit|Format|Left Align</b>"));
}

void GameWindow::RightAlign() {
   this->InfoLabel->setText(tr("Invoked <b>Edit|Format|Right Align</b>"));
}

void GameWindow::About() {
   this->InfoLabel->setText(tr("Invoked <b>Help|About</b>"));
   QString msg = tr("The <b>Menu</b> example shows how to create menu-bar menus and context menus.");
   QMessageBox::about(this, tr("About Menu"), msg);
}

void GameWindow::AboutQt() {
   this->InfoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
}

void GameWindow::createActions() {
   this->NewAction = new QAction(tr("&New"), this);
   this->NewAction->setShortcut(tr("Ctrl+N"));
   this->NewAction->setStatusTip(tr("Create a new file"));
   QObject::connect(this->NewAction, &QAction::triggered, this, &GameWindow::NewFile);

   this->ExitAction = new QAction(tr("E&xit"), this);
   this->ExitAction->setShortcut(tr("Esc"));
   this->ExitAction->setStatusTip(tr("Exit the application"));
   QObject::connect(this->ExitAction, &QAction::triggered, this, &QWidget::close);

   this->UndoAction = new QAction(tr("&Undo"), this);
   this->UndoAction->setShortcut(tr("Ctrl+Z"));
   this->UndoAction->setStatusTip(tr("Undo the last operation"));
   QObject::connect(this->UndoAction, &QAction::triggered, this, &GameWindow::Undo);

   this->RedoAction = new QAction(tr("&Redo"), this);
   this->RedoAction->setShortcut(tr("Ctrl+Y"));
   this->RedoAction->setStatusTip(tr("Redo the last operation"));
   QObject::connect(this->RedoAction, &QAction::triggered, this, &GameWindow::Redo);

   this->BoldAction = new QAction(tr("&Bold"), this);
   this->BoldAction->setCheckable(true);
   this->BoldAction->setShortcut(tr("Ctrl+B"));
   this->BoldAction->setStatusTip(tr("Make the text bold"));
   QFont boldFont = this->BoldAction->font();
   boldFont.setBold(true);
   this->BoldAction->setFont(boldFont);
   QObject::connect(this->BoldAction, &QAction::triggered, this, &GameWindow::Bold);

   this->ItalicAction = new QAction(tr("&Italic"), this);
   this->ItalicAction->setCheckable(true);
   this->ItalicAction->setShortcut(tr("Ctrl+I"));
   this->ItalicAction->setStatusTip(tr("Make the text italic"));
   QFont italicFont = this->ItalicAction->font();
   italicFont.setItalic(true);
   this->ItalicAction->setFont(italicFont);
   QObject::connect(this->ItalicAction, &QAction::triggered, this, &GameWindow::Italic);

   this->LeftAlignAction = new QAction(tr("&Left Align"), this);
   this->LeftAlignAction->setCheckable(true);
   this->LeftAlignAction->setShortcut(tr("Ctrl+L"));
   this->LeftAlignAction->setStatusTip(tr("Left align the selected text"));
   QObject::connect(this->LeftAlignAction, &QAction::triggered, this, &GameWindow::LeftAlign);

   this->RightAlignAction = new QAction(tr("&Right Align"), this);
   this->RightAlignAction->setCheckable(true);
   this->RightAlignAction->setShortcut(tr("Ctrl+R"));
   this->RightAlignAction->setStatusTip(tr("Right align the selected text"));
   QObject::connect(this->RightAlignAction, &QAction::triggered, this, &GameWindow::RightAlign);

   /* Set up the alignment options, default to left align */
   this->AlignmentGroup = new QActionGroup(this);
   this->AlignmentGroup->addAction(LeftAlignAction);
   this->AlignmentGroup->addAction(RightAlignAction);
   this->LeftAlignAction->setChecked(true);

   this->AboutAction = new QAction(tr("&About"), this);
   this->AboutAction->setShortcut(tr("F1"));
   this->AboutAction->setStatusTip(tr("Show the application's About box"));
   QObject::connect(this->AboutAction, &QAction::triggered, this, &GameWindow::About);

   this->AboutQtAction = new QAction(tr("About &Qt"), this);
   this->AboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
   QObject::connect(this->AboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);
   QObject::connect(this->AboutQtAction, &QAction::triggered, this, &GameWindow::AboutQt);
}

void GameWindow::createMenus() {
   this->FileMenu = menuBar()->addMenu(tr("&File"));
   this->FileMenu->addAction(NewAction);
   this->FileMenu->addSeparator();
   this->FileMenu->addAction(ExitAction);

   this->EditMenu = menuBar()->addMenu(tr("&Edit"));
   this->EditMenu->addAction(UndoAction);
   this->EditMenu->addAction(RedoAction);
   this->EditMenu->addSeparator();

   this->FormatMenu = EditMenu->addMenu(tr("&Format"));
   this->FormatMenu->addAction(BoldAction);
   this->FormatMenu->addAction(ItalicAction);
   this->FormatMenu->addSeparator()->setText(tr("Alignment"));
   this->FormatMenu->addAction(LeftAlignAction);
   this->FormatMenu->addAction(RightAlignAction);

   this->HelpMenu = menuBar()->addMenu(tr("&Help"));
   this->HelpMenu->addAction(AboutAction);
   this->HelpMenu->addAction(AboutQtAction);
}

void GameWindow::loadFonts() {
   this->robotoFont = QFont("Roboto",   15, 40);
   this->kronaFont  = QFont("KronaOne", 20, 10);
}

#endif // ENABLE_QT_UI