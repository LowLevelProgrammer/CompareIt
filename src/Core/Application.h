#pragma once

#include "Window.h"
#include <QApplication>

class Application {
public:
  Application(int argc, char *argv[]);
  ~Application();

  void Init();
  void Shutdown();
  void Run();

private:
  QApplication m_App;
  Window m_Window;
  bool m_IsRunning = true;
};
