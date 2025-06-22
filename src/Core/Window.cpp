#include "Window.h"

#include <qboxlayout.h>
#include <qfiledialog.h>
#include <qmainwindow.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qwidget.h>

Window::Window(QWidget *parent) : QMainWindow(parent) {
  QWidget *central = new QWidget(this);
  QVBoxLayout *mainLayout = new QVBoxLayout(central);

  // Inputs
  QHBoxLayout *entriesHorizontalLayout = new QHBoxLayout;

  m_Entry1 = new QLineEdit();
  m_Entry1->setPlaceholderText("Enter entry 1 location");
  entriesHorizontalLayout->addWidget(m_Entry1);

  m_Entry2 = new QLineEdit();
  m_Entry2->setPlaceholderText("Enter entry 2 location");
  entriesHorizontalLayout->addWidget(m_Entry2);

  mainLayout->addLayout(entriesHorizontalLayout);

  // Entry pickers
  QHBoxLayout *entryPickersLayout = new QHBoxLayout;

  QPushButton *entry1Picker = new QPushButton("Open 1st Entry");
  entryPickersLayout->addWidget(entry1Picker);
  QPushButton *entry2Picker = new QPushButton("Open 2nd Entry");
  entryPickersLayout->addWidget(entry2Picker);

  mainLayout->addLayout(entryPickersLayout);

  QPushButton *compareButton = new QPushButton("Compare");
  compareButton->setEnabled(false);
  mainLayout->addWidget(compareButton);

  // Set central widget
  setCentralWidget(central);

  connect(entry1Picker, &QPushButton::clicked, this, &Window::HandleOpenEntry1);
  connect(entry2Picker, &QPushButton::clicked, this, &Window::HandleOpenEntry2);
  connect(compareButton, &QPushButton::clicked, this, &Window::HandleCompare);

  setWindowTitle("Compare It");
  resize(800, 400);
}

Window::~Window() {}

void Window::HandleOpenEntry1() {
  QString entry1 = QFileDialog::getOpenFileName(this, "Select a File/Folder");
  if (!entry1.isEmpty()) {
    m_Entry1->setText(entry1);
  }
}
void Window::HandleOpenEntry2() {
  QString entry2 = QFileDialog::getOpenFileName(this, "Select a File/Folder");
  if (!entry2.isEmpty()) {
    m_Entry2->setText(entry2);
  }
}
void Window::HandleCompare() {
  // TODO: Call compare function
}
