#pragma once

#include "Directory.h"
#include "Hasher.h"

#include <unordered_set>

using RelativeEntrySet =
    std::unordered_set<RelativeEntry, RelativeEntryHasher, RelativeEntryEqual>;

class Comparator {
public:
  Comparator();
  ~Comparator();

  bool SetDirectory1(std::filesystem::path directoryPath1);
  bool SetDirectory2(std::filesystem::path directoryPath2);

  bool Compare();

private:
  bool AreFilesIdentical(const File *file1, const File *file2);
  bool CompareEntriesName(RelativeEntrySet dir1Set, RelativeEntrySet dir2Set);
  bool AreDirectoriesIdentical(RelativeEntrySet dir1Set,
                               RelativeEntrySet dir2Set);

private:
  std::unique_ptr<Directory> m_Directory1;
  std::unique_ptr<Directory> m_Directory2;
};
