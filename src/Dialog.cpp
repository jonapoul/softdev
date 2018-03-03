#include <QtWidgets>
#include "Dialog.h"

Dialog::Dialog() {
   createMenu();
   createHorizontalGroupBox();
   createGridGroupBox();
   createFormGroupBox();

   this->bigEditor = new QTextEdit;
   this->bigEditor->setPlainText(tr("This widget takes up all the remaining space in the top-level layout."));

   this->buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

   connect(this->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
   connect(this->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

   QVBoxLayout * layout = new QVBoxLayout;
   layout->setMenuBar(this->menuBar);
   layout->addWidget(this->horizontalGroupBox);
   layout->addWidget(this->gridGroupBox);
   layout->addWidget(this->formGroupBox);
   layout->addWidget(this->bigEditor);
   layout->addWidget(this->buttonBox);
   this->setLayout(layout);

   setWindowTitle(tr("Basic Layouts"));
}

void Dialog::createMenu() {
   this->menuBar = new QMenuBar;

   this->fileMenu = new QMenu(tr("&File"), this);
   this->exitAction = this->fileMenu->addAction(tr("E&xit"));
   this->menuBar->addMenu(this->fileMenu);

   connect(this->exitAction, SIGNAL(triggered()), this, SLOT(accept()));
}

void Dialog::createHorizontalGroupBox() {
   this->horizontalGroupBox = new QGroupBox(tr("Horizontal layout"));
   QHBoxLayout * layout = new QHBoxLayout;

   for (int i = 0; i < NumButtons; ++i) {
      this->buttons[i] = new QPushButton(tr("Button %1").arg(i + 1));
      layout->addWidget(this->buttons[i]);
   }
   this->horizontalGroupBox->setLayout(layout);
}

void Dialog::createGridGroupBox() {
   this->gridGroupBox = new QGroupBox(tr("Grid layout"));
   QGridLayout * layout = new QGridLayout;

   for (int i = 0; i < NumGridRows; ++i) {
      this->labels[i] = new QLabel(tr("Line %1:").arg(i + 1));
      this->lineEdits[i] = new QLineEdit;
      layout->addWidget(this->labels[i],    i, 0);
      layout->addWidget(this->lineEdits[i], i, 1);
   }

   this->smallEditor = new QTextEdit;
   this->smallEditor->setPlainText(tr("This widget takes up about two thirds of the grid layout."));
   layout->addWidget(this->smallEditor, 0, 2, 3, 1);

   layout->setColumnStretch(1, 10);
   layout->setColumnStretch(2, 20);
   this->gridGroupBox->setLayout(layout);
}

void Dialog::createFormGroupBox() {
   this->formGroupBox = new QGroupBox(tr("Form layout"));
   QFormLayout * layout = new QFormLayout;
   layout->addRow(new QLabel(tr("Line 1:")), new QLineEdit);
   layout->addRow(new QLabel(tr("Line 2, long text:")), new QComboBox);
   layout->addRow(new QLabel(tr("Line 3:")), new QSpinBox);
   this->formGroupBox->setLayout(layout);
}