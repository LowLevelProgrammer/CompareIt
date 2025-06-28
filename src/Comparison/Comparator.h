#pragma once

#include "Directory.h"
#include "Hasher.h"

#include <functional>
#include <unordered_set>

using RelativeEntrySet =
    std::unordered_set<RelativeEntry, RelativeEntryHasher, RelativeEntryEqual>;

class Comparator {
public:
  using LogCallback = std::function<void(const std::string &)>;
  using ProgressCallback = std::function<void(int)>;

  Comparator();
  ~Comparator();

  bool SetDirectory1(std::filesystem::path directoryPath1);
  bool SetDirectory2(std::filesystem::path directoryPath2);
  void SetLogCallback(LogCallback cb);
  void SetProgressCallback(ProgressCallback cb);

  bool Compare();

private:
  std::unique_ptr<Directory> m_Directory1;
  std::unique_ptr<Directory> m_Directory2;
  LogCallback m_LogCb;
  ProgressCallback m_ProgressCb;

private:
  bool AreFilesIdentical(const File *file1, const File *file2);
  bool CompareEntriesName(RelativeEntrySet dir1Set, RelativeEntrySet dir2Set);
  bool AreDirectoriesIdentical(const RelativeEntrySet &dir1Set,
                               const RelativeEntrySet &dir2Set);
  void Log(const std::string &msg);
  void ReportProgress(int percent);
};
