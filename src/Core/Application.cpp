#include "Application.h"
#include <qapplication.h>

Application::Application(int argc, char *argv[]) : m_App(argc, argv) {
  m_Window.show();
}

Application::~Application() {}

void Application::Init() {}

void Application::Shutdown() {}

void Application::Run() { m_App.exec(); }
