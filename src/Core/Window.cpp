#include "Window.h"

#include "ComparatorWorker.h"

#include <qboxlayout.h>
#include <qdir.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qobject.h>
#include <qthread.h>

Window::Window(QWidget *parent) : QMainWindow(parent) {
  QWidget *central = new QWidget(this);
  QVBoxLayout *mainLayout = new QVBoxLayout(central);

  // Inputs
  QHBoxLayout *entriesHorizontalLayout = new QHBoxLayout;

  m_Entry1Field = new QLineEdit();
  m_Entry1Field->setPlaceholderText("Enter entry 1 location");
  entriesHorizontalLayout->addWidget(m_Entry1Field);

  m_Entry2Field = new QLineEdit();
  m_Entry2Field->setPlaceholderText("Enter entry 2 location");
  entriesHorizontalLayout->addWidget(m_Entry2Field);

  mainLayout->addLayout(entriesHorizontalLayout);

  // Entry pickers
  QHBoxLayout *entryPickersLayout = new QHBoxLayout;

  m_Entry1Picker = new QPushButton("Open 1st Entry");
  entryPickersLayout->addWidget(m_Entry1Picker);
  m_Entry2Picker = new QPushButton("Open 2nd Entry");
  entryPickersLayout->addWidget(m_Entry2Picker);

  mainLayout->addLayout(entryPickersLayout);

  m_CompareButton = new QPushButton("Compare");
  m_CompareButton->setEnabled(false);
  mainLayout->addWidget(m_CompareButton);

  // Progress bar
  m_ProgressBar = new QProgressBar;
  m_ProgressBar->setVisible(false); // initially hidden
  mainLayout->addWidget(m_ProgressBar);

  // Info/Log area
  m_LogArea = new QTextEdit;
  m_LogArea->setReadOnly(true);
  m_LogArea->setVisible(false);
  mainLayout->addWidget(m_LogArea);

  // Cancel button
  m_CancelButton = new QPushButton("Cancel");
  m_CancelButton->setVisible(false);
  mainLayout->addWidget(m_CancelButton);

  // Set central widget
  setCentralWidget(central);

  connect(m_Entry1Field, &QLineEdit::textChanged, this,
          &Window::HandleEntry1TextChange);
  connect(m_Entry2Field, &QLineEdit::textChanged, this,
          &Window::HandleEntry2TextChange);
  connect(m_Entry1Picker, &QPushButton::clicked, this,
          &Window::HandleOpenEntry1);
  connect(m_Entry2Picker, &QPushButton::clicked, this,
          &Window::HandleOpenEntry2);
  connect(m_CompareButton, &QPushButton::clicked, this, &Window::HandleCompare);

  setWindowTitle("Compare It");
  resize(800, 400);
}

Window::~Window() {}

void Window::HandleOpenEntry1() {
  QString entry1 = QFileDialog::getExistingDirectory(
      this, "Select Directory", QDir::homePath(),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  if (!entry1.isEmpty()) {
    m_Entry1Field->setText(entry1);
  }
}
void Window::HandleOpenEntry2() {
  QString entry2 = QFileDialog::getExistingDirectory(
      this, "Select Directory", QDir::homePath(),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  if (!entry2.isEmpty()) {
    m_Entry2Field->setText(entry2);
  }
}

void Window::HandleEntry1TextChange() {
  m_CompareButton->setEnabled(!m_Entry1Field->text().isEmpty() &&
                              !m_Entry2Field->text().isEmpty());
}

void Window::HandleEntry2TextChange() {
  m_CompareButton->setEnabled(!m_Entry1Field->text().isEmpty() &&
                              !m_Entry2Field->text().isEmpty());
}

void Window::HandleCompare() {
  m_Entry1Field->setEnabled(false);
  m_Entry2Field->setEnabled(false);
  m_Entry1Picker->setEnabled(false);
  m_Entry2Picker->setEnabled(false);
  m_CompareButton->setEnabled(false);

  m_ProgressBar->setVisible(true);
  m_LogArea->setVisible(true);
  m_CancelButton->setVisible(true);

  m_LogArea->clear();
  m_LogArea->append("Starting comparison...");

  QString path1 = m_Entry1Field->text();
  QString path2 = m_Entry2Field->text();
  // TODO: Call compare function
  auto *worker = new ComparatorWorker(path1.toStdString(), path2.toStdString());

  connect(worker, &ComparatorWorker::LogMessage, this, &Window::OnLogMessage);
  connect(worker, &ComparatorWorker::ProgressChanged, this,
          &Window::OnProgressChanged);

  QThread *thread = new QThread;
  worker->moveToThread(thread);

  connect(thread, &QThread::started, worker, &ComparatorWorker::Run);
  connect(worker, &ComparatorWorker::Finished, thread, &QThread::quit);
  connect(worker, &ComparatorWorker::Finished, this,
          &Window::OnCompareFinished);
  connect(thread, &QThread::finished, thread, &QObject::deleteLater);

  thread->start();
}
void Window::OnLogMessage(const QString &msg) { m_LogArea->append(msg); }

void Window::OnProgressChanged(int percent) {
  m_ProgressBar->setValue(percent);
}

void Window::OnCompareFinished(bool success) {
  m_CompareButton->setEnabled(true);
  m_CancelButton->setEnabled(false);
  m_Entry1Field->setEnabled(true);
  m_Entry2Field->setEnabled(true);
  m_Entry1Picker->setEnabled(true);
  m_Entry2Picker->setEnabled(true);
  m_ProgressBar->setValue(100);

  if (success) {
    m_LogArea->append("Directories are identical!");
    QMessageBox::information(this, "Comparison Result",
                             "✅ The directories are identical.");
  } else {
    m_LogArea->append("Directories are NOT identical");
    QMessageBox::information(this, "Comparison Result",
                             "❌The directories are NOT identical.");
  }
}
