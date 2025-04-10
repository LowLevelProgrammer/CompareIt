#include "Comparator.h"

#include <fstream>
#include <iostream>
#include <unordered_set>

Comparator::Comparator() {}

Comparator::~Comparator() {}

bool Comparator::SetDirectory1(std::filesystem::path directoryPath1) {
  m_Directory1 = std::make_unique<Directory>(directoryPath1);
  return m_Directory1->IsValid();
}

bool Comparator::SetDirectory2(std::filesystem::path directoryPath2) {
  m_Directory2 = std::make_unique<Directory>(directoryPath2);
  return m_Directory2->IsValid();
}

bool Comparator::Compare() {
  if (!m_Directory1->IsValid()) {
    std::cout << "Directory 1 is not valid" << std::endl;
  };
  if (!m_Directory2->IsValid()) {
    std::cout << "Directory 2 is not valid" << std::endl;
  }

  if (!CompareEntriesName()) {
    return false;
  }
  return true;
}

bool Comparator::CompareEntriesName() {

  std::unordered_set<std::string> directory1Set;
  std::unordered_set<std::string> directory2Set;

  std::vector<File> dir1Files;
  m_Directory1->GetAllFiles(dir1Files);
  std::vector<File> dir2Files;
  m_Directory2->GetAllFiles(dir2Files);

  if (dir1Files.size() != dir2Files.size()) {
    return false;
  }

  std::filesystem::path dir1BasePath = m_Directory1->GetPath();

  for (const auto &file : dir1Files) {
    std::filesystem::path relativeFilePath =
        std::filesystem::relative(file.GetPath(), dir1BasePath);
    directory1Set.insert(relativeFilePath.string());
  }

  std::filesystem::path dir2BasePath = m_Directory2->GetPath();

  for (const auto &file : dir2Files) {
    std::filesystem::path relativeFilePath =
        std::filesystem::relative(file.GetPath(), dir2BasePath);
    directory2Set.insert(relativeFilePath.string());
  }

  for (const auto &path : directory1Set) {
    if (directory2Set.find(path) == directory2Set.end()) {
      return false;
    } else {
      directory2Set.erase(directory2Set.find(path));
    }
  }

  return true;
}

bool Comparator::AreFilesIdentical(const File& file1, const File& file2) {
  std::ifstream fileStream1(file1.GetPath(), std::ios::binary);
  std::ifstream fileStream2(file2.GetPath(), std::ios::binary);

  if (!fileStream1.is_open() || !fileStream2.is_open()) {
    std::cerr << "Error opening files.\n";
    return false;
  }

  constexpr std::size_t bufferSize = 4096;
  char buffer1[bufferSize];
  char buffer2[bufferSize];

  while (!fileStream1.eof() && !fileStream2.eof()) {
    fileStream1.read(buffer1, bufferSize);
    fileStream2.read(buffer2, bufferSize);

    std::streamsize bytesRead1 = fileStream1.gcount();
    std::streamsize bytesRead2 = fileStream2.gcount();

    if (bytesRead1 != bytesRead2 || std::memcmp(buffer1, buffer2, bytesRead1) != 0) {
      return false;
    }
  }

  return true;
}
