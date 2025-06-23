#pragma once

#include <qlineedit.h>
#include <qmainwindow.h>
#include <qprogressbar.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qwidget.h>

class Window : public QMainWindow {
  Q_OBJECT
public:
  Window(QWidget *parent = nullptr);
  ~Window();

  void HandleOpenEntry1();
  void HandleOpenEntry2();
  void HandleEntry1TextChange();
  void HandleEntry2TextChange();
  void HandleCompare();

private:
  QLineEdit *m_Entry1Field;
  QLineEdit *m_Entry2Field;
  QPushButton *m_Entry1Picker;
  QPushButton *m_Entry2Picker;
  QPushButton *m_CompareButton;
  QProgressBar *m_ProgressBar;
  QTextEdit *m_LogArea;
  QPushButton *m_CancelButton;
};
