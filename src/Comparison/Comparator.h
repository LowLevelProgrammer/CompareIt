#pragma once

#include "Directory.h"
#include <filesystem>
#include <memory>

enum class Mode { SHA256, ByteStream };

class Comparator {
public:
  Comparator();
  ~Comparator();

  void SetDirectory1(std::filesystem::path directoryPath1);
  void SetDirectory2(std::filesystem::path directoryPath2);
  void SetComparisonMode(Mode mode);

  bool Compare();

private:
  bool CompareEntriesName();

private:
  std::unique_ptr<Directory> m_Directory1;
  std::unique_ptr<Directory> m_Directory2;
  Mode m_ComparisonMode = Mode::SHA256;
};
