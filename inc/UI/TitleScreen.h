#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "config.h"

#ifdef ENABLE_QT_UI

#include <QWidget>
class GameWindow;
class QPushButton;

class TitleScreen : public QWidget {
   Q_OBJECT

public:
   explicit TitleScreen(GameWindow * p);
   ~TitleScreen();

   void load();

private slots:
   void loadLoginDialog();
   void loadRegisterDialog();
   void loadSettingsDialog();

private:
   GameWindow * parent;
   QPushButton * logInButton;
   QPushButton * registerButton;
   QPushButton * settingsButton;
};

#endif // ENABLE_QT_UI

#endif // TITLESCREEN_H