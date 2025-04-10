#pragma once

#include "Directory.h"

class Comparator {
public:
  Comparator();
  ~Comparator();

  bool SetDirectory1(std::filesystem::path directoryPath1);
  bool SetDirectory2(std::filesystem::path directoryPath2);

  bool Compare();
  bool AreFilesIdentical(const File& file1, const File& file2);

private:
  bool CompareEntriesName();

private:
  std::unique_ptr<Directory> m_Directory1;
  std::unique_ptr<Directory> m_Directory2;
};
