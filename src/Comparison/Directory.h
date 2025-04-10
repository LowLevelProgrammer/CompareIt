#pragma once

#include "Entry.h"
#include "File.h"

class Directory : public Entry {
public:
  Directory(const std::filesystem::path &path);
  ~Directory() = default;

  bool Refresh() override;
  void PrintDirectory(const std::string &prefix = "", bool isLast = true) const;
  std::uintmax_t ComputeTotalSize();

  const std::vector<File> &GetFiles() const { return m_Files; }
  const std::vector<Directory> &GetDirectories() const {
    return m_SubDirectories;
  }

  void GetAllFiles(std::vector<File>& files) const;

private:
  std::uintmax_t GetDirectoryShallowSize();

  void ShallowScanDirectory();

private:
  std::vector<File> m_Files;
  std::vector<Directory> m_SubDirectories;
};
