#pragma once

#include "Directory.h"
#include "Hasher.h"
#include "ProgressReporter.h"

#include <unordered_set>

using RelativeEntrySet =
    std::unordered_set<RelativeEntry, RelativeEntryHasher, RelativeEntryEqual>;

class Comparator {
public:
  Comparator(ProgressCallback callback);
  ~Comparator();

  bool SetDirectory1(std::filesystem::path directoryPath1);
  bool SetDirectory2(std::filesystem::path directoryPath2);

  bool Compare();

  void SetProgressCallback(ProgressCallback cb) {
    m_ProgressCallback = std::move(cb);
  }

private:
  bool AreFilesIdentical(const File *file1, const File *file2);
  bool CompareEntriesName(RelativeEntrySet dir1Set, RelativeEntrySet dir2Set);
  bool AreDirectoriesIdentical(const RelativeEntrySet &dir1Set,
                               const RelativeEntrySet &dir2Set);

private:
  std::unique_ptr<Directory> m_Directory1;
  std::unique_ptr<Directory> m_Directory2;

  ProgressCallback m_ProgressCallback;
  ProgressReporter m_ProgressReporter;
};
