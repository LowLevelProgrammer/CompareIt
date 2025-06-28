#pragma once

#include <qobject.h>
#include <qtmetamacros.h>
#include <string>

class ComparatorWorker : public QObject {
  Q_OBJECT
public:
  ComparatorWorker(std::string dir1, std::string dir2,
                   QObject *parent = nullptr);
  ~ComparatorWorker();

  void Run();

signals:
  void ProgressChanged(int percent);
  void LogMessage(const QString &msg);
  void Finished(bool success);

private:
  std::string m_Path1, m_Path2;
};
