#pragma once

#include "Entry.h"
#include "File.h"
#include <vector>

class Directory : public Entry {
public:
  Directory(const std::filesystem::path &path);
  ~Directory() = default;

  bool Refresh() override;
  void PrintDirectory(std::vector<Entry *> entries,
                      const std::string &prefix = "", bool isLast = true) const;
  void PrintDirectory(const std::string &prefix = "", bool isLast = true) const;
  std::uintmax_t ComputeTotalSize();
  std::uintmax_t ComputeTotalSizeInbuilt();
  bool IsDirectoryEmpty() const;

  const std::vector<File> &GetFiles() const { return m_Files; }
  const std::vector<Directory> &GetDirectories() const {
    return m_SubDirectories;
  }
  std::vector<Entry *> GetDirectoriesEntry() const {
    std::vector<Entry *> dirs;
    for (const auto &dir : m_SubDirectories) {
      dirs.push_back((Entry *)&dir);
    }

    return dirs;
  }
  EntryType GetType() const override { return EntryType::Directory; }

  std::vector<File> GetAllFiles() const;
  void GetAllLeafEntries(std::vector<Entry *> &entries) const;

private:
  void GetAllFiles(std::vector<File> &files) const;
  std::uintmax_t GetDirectoryShallowSize() const;

  void ShallowScanDirectory();

private:
  std::vector<File> m_Files;
  std::vector<Directory> m_SubDirectories;
};
