#include <QApplication>
#include <QPushButton>
#include "GameWindow.h"

int main(int argc, char **argv) {
  QApplication app (argc, argv);

  GameWindow window;
//  window.setFixedSize(100, 50);
//  QPushButton * button = new QPushButton("Button text!", &window);
//  button->setToolTip("This is a tooltip");
//  button->setGeometry(10, 10, 200, 150);
//  button->setIcon(QIcon::fromTheme("face-smile"));

//  window.showMaximized();
  window.show();

  return app.exec();
}
