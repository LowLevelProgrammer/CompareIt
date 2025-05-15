#pragma once

#include "Directory.h"
#include "Hasher.h"
#include <unordered_set>
#include <vector>

class Comparator {
public:
  Comparator();
  ~Comparator();

  bool SetDirectory1(std::filesystem::path directoryPath1);
  bool SetDirectory2(std::filesystem::path directoryPath2);

  bool Compare();
  bool AreFilesIdentical(const File &file1, const File &file2);

private:
  bool CompareEntriesName(
      std::unordered_set<RelativeEntry, RelativeEntryHasher, RelativeEntryEqual>
          dir1Set,
      std::unordered_set<RelativeEntry, RelativeEntryHasher, RelativeEntryEqual>
          dir2Set);
  bool AreDirectoriesIdentical(const std::vector<File> &dir1Files,
                               const std::vector<File> &dir2Files);

private:
  std::unique_ptr<Directory> m_Directory1;
  std::unique_ptr<Directory> m_Directory2;
};
