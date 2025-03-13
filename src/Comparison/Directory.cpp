#include "Directory.h"
#include <filesystem>
#include <iostream>

Directory::Directory(const std::filesystem::path &path) : Entry(path) {
  ScanDirectory();
  ComputeSize();
}

void Directory::ComputeSize() {}

void Directory::ScanDirectory() {
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
  std::cout << prefix << (isLast ? "└──" : "├──") << "[DIR] " << m_Name
            << std::endl;

  // Prepare new prefix for children
  std::string newPrefix = prefix + (isLast ? "    " : "│   ");

  // Print subdirectories first
  for (size_t i = 0; i < m_SubDirectories.size(); ++i) {
    bool lastSubDir =
        (i == m_SubDirectories.size() - 1) && m_Files.empty(); // Last item?
    m_SubDirectories[i].PrintDirectory(newPrefix, lastSubDir);
  }

  // Print files with extra space for alignment
  for (size_t i = 0; i < m_Files.size(); ++i) {
    std::cout << newPrefix << (i == m_Files.size() - 1 ? "└── " : "├── ");
    std::cout << m_Files[i].GetName() << std::endl;
  }
}
