#pragma once

#include <qlineedit.h>
#include <qmainwindow.h>
#include <qwidget.h>

class Window : public QMainWindow {
  Q_OBJECT
public:
  Window(QWidget *parent = nullptr);
  ~Window();

  void HandleOpenEntry1();
  void HandleOpenEntry2();
  void HandleCompare();

private:
  QLineEdit *m_Entry1;
  QLineEdit *m_Entry2;
};
