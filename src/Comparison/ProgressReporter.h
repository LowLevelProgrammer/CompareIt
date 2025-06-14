#pragma once

#include "ProgressStatus.h"

class ProgressReporter {
public:
  ProgressReporter(ProgressCallback callback);
  ~ProgressReporter();

  void ReportStarted(const std::filesystem::path &dir1,
                     const std::filesystem::path &dir2);

  void ReportNotValidEntry1(const std::filesystem::path &dir);
  void ReportNotValidEntry2(const std::filesystem::path &dir);

  void ReportCountingEntriesStart();
  void ReportDir1EntryCount(size_t count);
  void ReportDir2EntryCount(size_t count);
  void ReportCountMismatch(size_t difference);

  void ReportComparingPathsStart();
  void ReportComparingFilePath(const std::filesystem::path &relPath);
  void ReportPathMismatch(const std::filesystem::path &offendingPath,
                          int dirNumber);

  void ReportComparingContentStart();
  void ReportComparingContent(const std::filesystem::path &relPath);
  // void ReportComparingFileProgress(const std::filesystem::path& relPath,
  // size_t bytesCompared);
  void ReportContentMismatch(const std::filesystem::path &offendingPath);

  void ReportIdentical();
  void ReportError();

private:
  ProgressCallback m_Callback;
  ProgressStatus m_Status;
};
