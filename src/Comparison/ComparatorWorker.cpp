#include "ComparatorWorker.h"

#include "Comparator.h"

#include <utility>

ComparatorWorker::ComparatorWorker(std::string dir1, std::string dir2,
                                   QObject *parent)
    : QObject(parent), m_Path1(std::move(dir1)), m_Path2(std::move(dir2)) {}

ComparatorWorker::~ComparatorWorker() {}

void ComparatorWorker::Run() {
  Comparator comparator;
  comparator.SetDirectory1(m_Path1);
  comparator.SetDirectory2(m_Path2);

  comparator.SetLogCallback([this](const std::string &msg) {
    emit LogMessage(QString::fromStdString(msg));
  });

  comparator.SetProgressCallback(
      [this](int percent) { emit ProgressChanged(percent); });

  bool result = comparator.Compare();

  emit Finished(result);
}
