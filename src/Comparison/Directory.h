#pragma once

#include "File.h"
#include <vector>

class Directory : public Entry {
public:
  Directory(const std::filesystem::path &path);
  ~Directory() = default;

  virtual void ComputeSize() override;

  void ScanDirectory();

  void PrintDirectory(const std::string &prefix = "", bool isLast = true) const;

public:
  std::vector<File> m_Files;
  std::vector<Directory> m_SubDirectories;
};
