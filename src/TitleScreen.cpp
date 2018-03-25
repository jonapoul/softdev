#include "config.h"

#ifdef ENABLE_QT_UI

#include <QtWidgets>

#include "UI/TitleScreen.h"
#include "UI/GameWindow.h"
#include "Global.h"

/*

   This has been pretty much abandoned, it was taking ages and ages to learn Qt
   with any competence, and I had other project work to do.

*/

TitleScreen::TitleScreen(GameWindow * p = Q_NULLPTR)
      : parent(p) { }

TitleScreen::~TitleScreen() { }

void TitleScreen::load() {
   /* Loading the game's logo front and centre */
   QGroupBox * logoBox = new QGroupBox;
   logoBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   QPixmap pixmap = QPixmap::fromImage( QImage(tr(":/logo.jpg")) );
   QLabel * logoLabel = new QLabel;
   logoLabel->setPixmap(pixmap);
   float const factor_w = (float)pixmap.size().width()  / (float)logoBox->size().width();
   float const factor_h = (float)pixmap.size().height() / (float)logoBox->size().height();
   float const factor = MIN(factor_w, factor_h) * 1.6; /* 1.6 = fudge factor */
   int const w = (int)((float)pixmap.size().width()  / factor);
   int const h = (int)((float)pixmap.size().height() / factor);
   logoLabel->setScaledContents(true);
   logoLabel->setFixedSize( QSize(w, h) );
   QHBoxLayout * logoLayout = new QHBoxLayout;
   logoLayout->addWidget(logoLabel);
   logoBox->setLayout(logoLayout);

   /* Three buttons */
   QGroupBox * buttonsBox = new QGroupBox;
   buttonsBox->setAlignment(Qt::AlignHCenter);
   buttonsBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   this->logInButton = new QPushButton(tr("Log In"));
   this->logInButton->setStyleSheet(" QPushButton { height: 80%; } ");
   this->logInButton->setFont(parent->robotoFont);
   connect(this->logInButton, SIGNAL(clicked()), this, SLOT(loadLoginDialog()));
   this->registerButton = new QPushButton(tr("Register Account"));
   this->registerButton->setStyleSheet(" QPushButton { height: 80%; } ");
   this->registerButton->setFont(parent->robotoFont);
   connect(this->registerButton, SIGNAL(clicked()), this, SLOT(loadRegisterDialog()));
   this->settingsButton = new QPushButton(tr("Settings"));
   this->settingsButton->setStyleSheet(" QPushButton { height: 80%; } ");
   this->settingsButton->setFont(parent->robotoFont);
   connect(this->settingsButton, SIGNAL(clicked()), this, SLOT(loadSettingsDialog()));

   QHBoxLayout * buttonsLayout = new QHBoxLayout;
   buttonsLayout->addWidget(new QWidget,    2); /* spacing */
   buttonsLayout->addWidget(logInButton,    2);
   buttonsLayout->addWidget(new QWidget,    1); /* spacing */
   buttonsLayout->addWidget(registerButton, 2);
   buttonsLayout->addWidget(new QWidget,    1); /* spacing */
   buttonsLayout->addWidget(settingsButton, 2);
   buttonsLayout->addWidget(new QWidget,    2); /* spacing */
   buttonsBox->setLayout(buttonsLayout);

   /* Apply it all to the page layout */
   QVBoxLayout * layout = new QVBoxLayout;
   layout->addWidget(logoBox,    4);
   layout->addWidget(buttonsBox, 2);
   this->setLayout(layout);

   parent->setWindowTitle(tr("Title Screen"));
}

void TitleScreen::loadLoginDialog() {
   QMessageBox::information(this, tr("LOG IN"), tr("LOG IN"));
}

void TitleScreen::loadRegisterDialog() {
   QMessageBox::information(this, tr("REGISTER"), tr("REGISTER"));
}

void TitleScreen::loadSettingsDialog() {
   QMessageBox::information(this, tr("SETTINGS"), tr("SETTINGS"));
}

#endif // ENABLE_QT_UI