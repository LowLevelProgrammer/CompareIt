#include "Directory.h"

#include <iostream>
#include <optional>
#include <string>

Directory::Directory(const std::filesystem::path &path) : Entry(path) {
  Refresh();
}

bool Directory::Refresh() {

  if (!IsValid()) {
    return false;
  }

  m_SubDirectories.clear();
  m_Files.clear();
  m_Size = std::nullopt;

  ShallowScanDirectory();
  return true;
}

std::uintmax_t Directory::ComputeTotalSize() {

  std::uintmax_t totalSize = 0;
  std::uintmax_t currentDirectoryShallowSize = GetDirectoryShallowSize();

  std::uintmax_t totalSubDirectoriesSize = 0;
  if (!m_SubDirectories.empty()) {
    for (auto &subdirectory : m_SubDirectories) {
      totalSubDirectoriesSize += subdirectory.ComputeTotalSize();
    }
  }

  totalSize = currentDirectoryShallowSize + totalSubDirectoriesSize;
  m_Size = totalSize;

  return m_Size.value();
}

void Directory::ShallowScanDirectory() {
  for (const auto &entry : std::filesystem::directory_iterator(m_Path)) {
    if (std::filesystem::is_directory(entry)) {
      m_SubDirectories.emplace_back(entry.path());
    } else if (std::filesystem::is_regular_file(entry)) {
      m_Files.emplace_back(entry.path());
    }
  }
}

void Directory::PrintDirectory(const std::string &prefix, bool isLast) const {
  // Print current directory name
  std::cout << prefix << (isLast ? "└─" : "├─") << "[DIR] " << m_Name << " ("
            << (m_Size.has_value() ? std::to_string(m_Size.value()) : "N/A") << ")" << std::endl;

  // Prepare new prefix for children
  std::string newPrefix = prefix + (isLast ? "    " : "│  ");

  // Print subdirectories first
  for (size_t i = 0; i < m_SubDirectories.size(); ++i) {
    bool lastSubDir = (i == m_SubDirectories.size() - 1) &&
                      m_Files.empty(); // Last entry check
    m_SubDirectories[i].PrintDirectory(newPrefix, lastSubDir);
  }

  // Print files 
  for (size_t i = 0; i < m_Files.size(); ++i) {
    std::cout << newPrefix << (i == m_Files.size() - 1 ? "└─ " : "├─ ");
    std::optional<std::uintmax_t> size = m_Files[i].GetSize();
    std::cout << m_Files[i].GetName() << " (" << (size.has_value() ? std::to_string(size.value()) : "N/A")  << ")"
              << std::endl;
  }
}

std::uintmax_t Directory::GetDirectoryShallowSize() {
  std::uintmax_t directoryShallowSize = 0;

  for (const auto &file : m_Files) {
    directoryShallowSize += file.GetSize().value();
  }

  return directoryShallowSize;
}
